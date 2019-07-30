/*****************************************************************************
modelData.h
Aythor	: 上野　匠
Data	: 2017_07_07
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//ヘッダーインクルード
//////////////////////////////////////////////////////////////////////////////
#include <string>
#include "main.h"
#include "modelData.h"
#include "directory.h"
#include "load.h"
#include "convenient.h"

/*
#####################################################################################################################
ModelData class
#####################################################################################################################
*/

//////////////////////////////////////////////////////////////////////////////
//関数名	: ModelData::create
//返り値	: 
//説明		: 生成
//////////////////////////////////////////////////////////////////////////////
ModelData * ModelData::create(ModelData *modelType, string fileName)
{
	modelType->mName = fileName;
	modelType->init();

	return modelType;
}


//////////////////////////////////////////////////////////////////////////////
//関数名	: ModelData::readModelFile
//返り値	: 
//説明		: モデルファイルを読み込み
//////////////////////////////////////////////////////////////////////////////
void ModelData::readModelFile(sys::path path)
{
	if (path.extension().string() == ".x")
		Xmodel::setModelData(path);

	if (path.extension().string() == ".fbx")
	{

	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: ModelData::loadAllModel
//返り値	: 
//説明		: ディレクトリ内の全てのモデル読み込み
//////////////////////////////////////////////////////////////////////////////
void ModelData::loadAllModel(void)
{
	string currendDir = Directory::getCurrentDir("\\data\\model");
	auto pathList = Directory::fileAllReferenceInDirectory(currendDir, ".*");

#pragma omp parallel for
	for (auto it = pathList.begin(); it != pathList.end(); ++it)
		readModelFile(*it);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: ModelData::modelDataAllClear
//返り値	: 
//説明		: モデルデータ全削除
//////////////////////////////////////////////////////////////////////////////
void ModelData::modelDataAllClear(void)
{
	Xmodel::allClear();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: ModelData::createModelData
//返り値	: 
//説明		: ディレクトリ内の全てのモデル読み込み
//////////////////////////////////////////////////////////////////////////////
ModelData *ModelData::createModelData(string fileName)
{
	if (fileName.find(".x") != UINT_MAX)
		return ModelData::create(new Xmodel, fileName);

	return new NullModel;
}

/*
#####################################################################################################################
Xmodel class
#####################################################################################################################
*/
map<string, XMODEL_DATA>		Xmodel::meshDataMap;

//////////////////////////////////////////////////////////////////////////////
//関数名	: Xmodel::init
//返り値	: 
//説明		: 初期化
//////////////////////////////////////////////////////////////////////////////
HRESULT Xmodel::init(void)
{
	if (meshDataMap.find(mName) == meshDataMap.end())
	{
		string text = "存在しないモデルデータ：" + mName;
		MessageBox(NULL, text.c_str(), "error", MB_OK);
		return E_FAIL;
	}

	mModelData = meshDataMap[mName.c_str()];
	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Xmodel::uninit
//返り値	: 
//説明		: 終了
//////////////////////////////////////////////////////////////////////////////
void Xmodel::uninit(void)
{
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Xmodel::draw
//返り値	: 
//説明		: 描画
//////////////////////////////////////////////////////////////////////////////
void Xmodel::draw(Dmtx matrix)
{
	//変数宣言
	LPDIRECT3DDEVICE9	device = Renderer::getDevice();

#pragma omp parallel for
	for (int i = 0; i < (int)mModelData.numMat; i++)
	{
		//行列設定
		device->SetTransform(D3DTS_WORLD, &matrix);

		//マテリアル設定
		device->SetMaterial(&mModelData.mat[i]);

		//テクスチャ読み込み
		device->SetTexture(0, mModelData.tex[i]);

		//メッシュ描画
		mModelData.mesh->DrawSubset(i);
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Xmodel::allClear
//返り値	: 
//説明		: モデルデータ全削除
//////////////////////////////////////////////////////////////////////////////
void Xmodel::allClear(void)
{
	for (auto it = meshDataMap.begin(); it != meshDataMap.end(); ++it)
	{
		auto a = *it;
		if (meshDataMap[a.first].mesh != NULL)
		{
			meshDataMap[a.first].mesh->Release();
			meshDataMap[a.first].mesh = NULL;
		}
		
		//テクスチャ解放
		for (DWORD i = 0; i < meshDataMap[a.first].numMat; i++)
		{
			if (meshDataMap[a.first].tex[i] != NULL)
			{
				meshDataMap[a.first].tex[i]->Release();
				meshDataMap[a.first].tex[i] = NULL;
			}
		}

		//テクスチャポインタ解放
		delete[] meshDataMap[a.first].tex;
		delete[] meshDataMap[a.first].mat;
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Xmodel::setModelData
//返り値	: 
//説明		: マップにモデル情報登録
//////////////////////////////////////////////////////////////////////////////
void Xmodel::setModelData(sys::path path)
{
	XMODEL_DATA			data; 
	LPD3DXBUFFER		buffer = NULL;		//マテリアル情報
	HRESULT				hr;
	D3DMATERIAL9		matDef;
	D3DXMATERIAL		*mat;
	LPDIRECT3DDEVICE9	device = Renderer::getDevice();
	string				relativePath;

	//相対パスに変換
	relativePath = path.generic_string();
	relativePath.erase(0, relativePath.find("data"));
	
	//モデル読み込み
	hr = D3DXLoadMeshFromX(relativePath.c_str(),
		D3DXMESH_MANAGED,
		device,
		NULL,
		&buffer,
		NULL,
		&data.numMat,
		&data.mesh);

	if (FAILED(hr))
	{
		char message[192];
		sprintf(message, "%s読み込みエラー", path.filename().string().c_str());

		MessageBox(NULL, message, "error", MB_OK);
	}

	device->GetMaterial(&matDef);
	mat = (D3DXMATERIAL*)buffer->GetBufferPointer();

	//マテリアルとテクスチャ動的確保
	data.mat = new D3DMATERIAL9[data.numMat];
	data.tex = new LPDIRECT3DTEXTURE9[data.numMat];

#pragma omp paralell for
	for (int i = 0; i < (int)data.numMat; i++)
	{
		data.mat[i] = mat[i].MatD3D;			//マテリアル情報セット
		data.mat[i].Ambient = data.mat[i].Diffuse;	//環境光初期化
		data.tex[i] = NULL;						//テクスチャ初期化

#pragma omp paralell
		{
			//テクスチャの読み込み
			if (mat[i].pTextureFilename != NULL && lstrlen(mat[i].pTextureFilename) > 0)
			{
				if (FAILED(D3DXCreateTextureFromFile(device, mat[i].pTextureFilename, &data.tex[i])))
				{
					string text = *mat[i].pTextureFilename + "が読み込めませんでした";
					MessageBox(NULL, text.c_str(), "モデルテクスチャエラー", MB_OK);
				}
			}
		}
	}

	//マテリアル情報解放
	buffer->Release();
	buffer = NULL;

	meshDataMap[path.filename().string().c_str()] = data;
}