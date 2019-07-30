/*****************************************************************************
meshField.cpp
Aythor	: 上野　匠
Data	: 2017_04_27
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//ヘッダーインクルード
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "meshField.h"
#include "renderer.h"
#include "convenient.h"

//////////////////////////////////////////////////////////////////////////////
//静的メンバ変数初期化
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9	*MeshField::mTex = NULL;
map<string, UINT>	MeshField::mNameList;
list<MeshField*>	MeshField::mFieldList;
vector<string>		MeshField::mTexNameList;

//////////////////////////////////////////////////////////////////////////////
//関数名	: MeshField()
//返り値	: 
//説明		: コンストラクタ
//////////////////////////////////////////////////////////////////////////////
MeshField::MeshField(UINT priolity) :Mesh(priolity)
{
	//自分のポインタをリストに追加
	mFieldList.push_back(this);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: MeshField::init
//返り値	: 
//説明		: 初期化
//////////////////////////////////////////////////////////////////////////////
HRESULT MeshField::init(void)
{
	//変数宣言
	mDelete = false;

	// Set the RGBA for diffuse reflection.
	mMat.Diffuse.r = 1.0f;
	mMat.Diffuse.g = 1.0f;
	mMat.Diffuse.b = 1.0f;
	mMat.Diffuse.a = 1.0f;

	// Set the RGBA for ambient reflection.
	mMat.Ambient.r = 1.0f;
	mMat.Ambient.g = 1.0f;
	mMat.Ambient.b = 1.0f;
	mMat.Ambient.a = 1.0f;

	// Set the color and sharpness of specular highlights.
	mMat.Specular.r = 1.0f;
	mMat.Specular.g = 1.0f;
	mMat.Specular.b = 1.0f;
	mMat.Specular.a = 1.0f;
	mMat.Power = 50.0f;

	// Set the RGBA for emissive color.
	mMat.Emissive.r = 0.0f;
	mMat.Emissive.g = 0.0f;
	mMat.Emissive.b = 0.0f;
	mMat.Emissive.a = 0.0f;

	mMyName = "meshField";

	return	S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: MeshField::uninit
//返り値	: 
//説明		: 終了
//////////////////////////////////////////////////////////////////////////////
void	MeshField::uninit(void)
{
	//リスト全削除
	for (auto it = mFieldList.begin(); it != mFieldList.end();)
		it = mFieldList.erase(it);

	Mesh::uninit();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: MeshField::update
//返り値	: 
//説明		: 更新
//////////////////////////////////////////////////////////////////////////////
void	MeshField::update(void)
{
	//変数宣言
	VERTEX3D	*pVtx;		//頂点情報ポインタ
	int			x, z;		//xとzのループ
	int			num;		//必要な頂点数
	Dvec3	fullSize;	//フィールド全体のサイズ

	//=============================
	// 何頂点必要か
	//=============================
	num = (int)((mNumTyle.x + 1) * (mNumTyle.y + 1));

	//=============================
	// テクスチャアニメ
	//=============================
	bindTexBuf(mTex[mNumTexture]);
	setTexPos(D3DXVECTOR2(
		getTexPos().x + getTexMove().x,
		getTexPos().y + getTexMove().y));

	//=============================
	// 頂点バッファ数変更
	//=============================
	if (mNumTyle.x != mSaveNumTyle.x || mNumTyle.y != mSaveNumTyle.y)
	{
		makeVtx(mNumTyle, mColor);
		mSaveNumTyle = mNumTyle;
	}

	//=============================
	// 頂点バッファ登録
	//=============================
	getVtxBuf()->Lock(0, 0, (void**)&pVtx, 0);

	//全体のサイズ計算
	fullSize = Dvec3(
		mNumTyle.x * mTyleSize.x,
		0.f,
		mNumTyle.y * mTyleSize.y);

	for (z = 0; z < mNumTyle.y + 1; z++)
	{
		for (x = 0; x < mNumTyle.x + 1; x++)
		{
			//頂点
			pVtx[0].pos = Dvec3(
				(mTyleSize.x * x) - (fullSize.x * 0.5f),
				0.f,
				-(mTyleSize.y * z) + (fullSize.z * 0.5f));

			//テクスチャ座標
			pVtx[0].tex = D3DXVECTOR2(getTexPos().x + (float)x, getTexPos().y + (float)z);

			//頂点色
			pVtx->color = mColor;

			//法線ベクトル
			//if (x == 0 || x >= (int)mNumTyle.x ||
			//	z == 0 || z >= (int)mNumTyle.y)
			//{
			//	pVtx[0].nor = Dvec3(0.f, 1.f, 0.f);
			//}
			//else
			//{
			//	if ((int)mNumTyle.x * z + x == 10)
			//	{
			//		int i = 0;
			//		i++;
			//	}

			//	vec3 normal;	//法線

			//	normal = vec3::crossProduct(pVtx[-((int)mNumTyle.x + 1)].pos, pVtx[(int)mNumTyle.x + 1].pos);
			//	normal = vec3::normalize(normal);
			//	normal.y = (float)fabs(normal.y);
			//	pVtx[0].nor = Dvec3(normal.x, normal.y, normal.z);
			//}

			//ポインタ移動
			pVtx++;
		}
	}

	getVtxBuf()->Unlock();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: MeshField::draw
//返り値	: 
//説明		: 更新
//////////////////////////////////////////////////////////////////////////////
void	MeshField::draw(void)
{
	Renderer::getDevice()->SetMaterial(&mMat);
	Mesh::draw();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: MeshField::release
//返り値	: 
//説明		: リスト削除
//////////////////////////////////////////////////////////////////////////////
void MeshField::release(MeshField * point)
{
	for (auto it = mFieldList.begin(); it != mFieldList.end();)
	{
		if (*it == point)
		{
			auto work = *it;
			work->Mesh::release();
			it = mFieldList.erase(it);
			break;
		}
		else
			++it;
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: MeshField::create
//返り値	: 
//説明		: フィールド設定
//////////////////////////////////////////////////////////////////////////////
MeshField	*MeshField::create(Dvec3 pos, D3DXVECTOR2 size, Tyle numTyle, Dvec3 rot, D3DXCOLOR color, D3DXVECTOR2 texMove, int textureID)
{
	//変数宣言

	//MeshField生成
	MeshField *field = new MeshField;

	//変数代入
	field->setVal(size, numTyle, textureID, color);
	field->setAll(pos, rot, color, D3DXVECTOR2(0.f, 0.f), texMove);
	field->mNumTyle = numTyle;
	field->mSaveNumTyle = numTyle;

	//初期化
	field->init();

	//テクスチャバインド
	field->bindTexBuf(mTex[textureID]);

	//頂点バッファ作成
	field->makeVtx(numTyle, color);

	return field;
}

MeshField * MeshField::create(MeshField field)
{
	auto	meshField = new MeshField;
	*meshField = field;

	return meshField;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: MeshField::setVal
//返り値	: 
//説明		: 変数代入
//////////////////////////////////////////////////////////////////////////////
void	MeshField::setVal(D3DXVECTOR2 size, Tyle numTyle, int textureID, Dcolor color)
{
	mTyleSize = size;
	mNumTyle = numTyle;
	mNumTexture = textureID;
	mColor = color;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: loadTex
//返り値	: 
//説明		: テクスチャ読み込み
//////////////////////////////////////////////////////////////////////////////
void	MeshField::loadTex(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9	device = Renderer::getDevice();

	//名前リスト作成
	list<string> textureList = Conveni::getDirFile("data/texture/field", "*");

	mTex = new LPDIRECT3DTEXTURE9[textureList.size()];

	int i = 0;
	for (auto it = textureList.begin(); it != textureList.end(); ++it, i++)
	{
		string	textureDir = "data/texture/field/" + *it;
		mTexNameList.push_back(textureDir);
		mNameList[textureDir] = i;

		//テクスチャの読み込み
		if (FAILED(D3DXCreateTextureFromFile(device, textureDir.c_str(), &mTex[i])))
		{
			MessageBox(NULL, "エラー", "fieldエラー", MB_OK);
		}
	}

}

//////////////////////////////////////////////////////////////////////////////
//関数名	: makeVtx
//返り値	: 
//説明		: ポリゴン描画位置設定
//////////////////////////////////////////////////////////////////////////////
HRESULT	MeshField::makeVtx(Tyle numTyle, D3DXCOLOR color)
{
	//変数宣言
	VERTEX3D	*pVtx;		//仮想アドレス用ポインタ
	Dvec3		pos;		//描画位置
	int			x, z;		//xとzのループ
	int			num;		//必要な頂点数
	Dvec3		fullSize;	//フィールド全体のサイズ
	LPDIRECT3DVERTEXBUFFER9	vtx = NULL;	//頂点バッファ

										//=============================
										// 何頂点必要か
										//=============================
	num = (int)((mNumTyle.x + 1) * (mNumTyle.y + 1));

	//必要なプリミティブ数
	UINT	numPtv;
	numPtv = (int)(mNumTyle.x * mNumTyle.y * 2 + (mNumTyle.y - 1) * 4);

	//プリミティブ数セット
	setNumPrim(numPtv);

	//頂点数分位置情報生成
	mVtxPos = new Dvec3[num];

	//=============================
	// 頂点バッファ作成
	//=============================
	if ((vtx = makeVtxBuf(num)) == NULL)
	{
		return E_FAIL;
	}

	//全体のサイズ計算
	fullSize = Dvec3(
		mNumTyle.x * mTyleSize.x,
		0.f,
		mNumTyle.y * mTyleSize.y);

	//=============================
	// 頂点情報登録
	//=============================
	vtx->Lock(0, 0, (void**)&pVtx, 0);

	for (z = 0; z < mNumTyle.y + 1; z++)
	{
		for (x = 0; x < mNumTyle.x + 1; x++)
		{
			//頂点
			mVtxPos[((int)mNumTyle.x + 1) * z + x] =
				pVtx[0].pos = Dvec3(
				(mTyleSize.x * x) - (fullSize.x * 0.5f),
					0.f,
					-(mTyleSize.y * z) + (fullSize.z * 0.5f));

			//頂点色
			pVtx[0].color = color;

			//法線ベクトル
			pVtx[0].nor = Dvec3(0, 1, 0);
			//if (x == 0 || x == (int)mNumTyle.x - 1 ||
			//	z == 0 || z == (int)mNumTyle.y - 1)
			//{
			//	pVtx[0].nor = Dvec3(0.f, 1.f, 0.f);
			//}
			//else
			//{
			//	vec3 normal;	//法線

			//	normal = vec3::crossProduct(pVtx[-((int)mNumTyle.x + 1)].pos, pVtx[(int)mNumTyle.x + 1].pos);
			//	normal = vec3::normalize(normal);
			//	pVtx[0].nor = Dvec3(normal.x, normal.y, normal.z);
			//}

			//テクスチャ座標
			pVtx[0].tex = D3DXVECTOR2((float)x, (float)z);

			//ポインタ移動
			pVtx++;
		}
	}

	vtx->Unlock();

	//頂点バッファバインド
	bindVtxBuf(vtx);

	//=============================
	// インデックス作成
	//=============================
	makeIdx(numTyle);

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: makeIdx
//返り値	: 
//説明		: ポリゴン描画位置設定
//////////////////////////////////////////////////////////////////////////////
HRESULT	MeshField::makeIdx(Tyle numTyle)
{
	//変数宣言
	WORD		*pIdx;	//インデックス番号
	int			x, z;	//xとzのloop
	int			num;	//必要なインデックス数
	LPDIRECT3DINDEXBUFFER9	idx = NULL; //インデックスバッファ

										//=============================
										// 何頂点必要か
										//=============================
	num = (int)((numTyle.x + 1) * (numTyle.y * 2));
	num += (int)((numTyle.y - 1) * 2);

	//=============================
	// インデックス作成
	//=============================
	if ((idx = makeIdxBuf(num)) == NULL)
	{
		return E_FAIL;
	}

	//=============================
	// インデックス登録
	//=============================
	idx->Lock(0, 0, (void**)&pIdx, 0);

	for (z = 0; z < (int)mNumTyle.y; z++)
	{
		for (x = 0; x < (int)mNumTyle.x + 1; x++)
		{
			//インデックス登録
			pIdx[0] = (WORD)((mNumTyle.x + 1) * (z + 1) + x);
			pIdx[1] = (WORD)((mNumTyle.x + 1) * z + x);

			//ポインタ移動
			pIdx += 2;
		}

		//縮退ポリゴン
		if (z < mNumTyle.y - 1)
		{
			//インデックス登録
			x--;
			pIdx[0] = ((WORD)mNumTyle.x + 1) * (WORD)z + (WORD)x;
			pIdx[1] = pIdx[0] + (WORD)mNumTyle.x + 2;

			//ポインタ移動
			pIdx += 2;
		}
	}

	idx->Unlock();

	//インデックスバッファバインド
	bindIdxBuf(idx);

	return	S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: MeshField::getHeight
//返り値	: 
//説明		: フィールドの高さ取得
//////////////////////////////////////////////////////////////////////////////
float	MeshField::getHeight(const Dvec3 pos)
{
	//変数宣言
	vec3		work(pos);		//対象の位置
	vec3		vtx[4];			//頂点座標

	for (auto it = mFieldList.begin(); it != mFieldList.end(); ++it)
	{
		auto ptr = *it;

		if (ptr->mNumTyle.x <= 1)
			break;

		for (int y = 0; y < (int)ptr->mNumTyle.x; y++)
		{
			for (int x = 0; x < (int)ptr->mNumTyle.y; x++)
			{
				vtx[0] = vec3(ptr->mVtxPos[((int)ptr->mNumTyle.x + 1) * y + x]);
				vtx[1] = vec3(ptr->mVtxPos[((int)ptr->mNumTyle.x + 1) * y + x + 1]);
				vtx[2] = vec3(ptr->mVtxPos[((int)ptr->mNumTyle.x + 1) * y + x + (int)ptr->mNumTyle.x + 2]);
				vtx[3] = vec3(ptr->mVtxPos[((int)ptr->mNumTyle.x + 1) * y + x + (int)ptr->mNumTyle.x + 1]);

				for (int face = 0; face < 2; face++)
				{
					if (face % 2 == 0 &&
						vec3::crossProduct(vtx[1], work, vtx[0]).y >= 0 &&
						vec3::crossProduct(vtx[2], work, vtx[1]).y >= 0 &&
						vec3::crossProduct(vtx[0], work, vtx[2]).y >= 0)
					{
						vec3 normal;	//面の法線ベクトル
						float test;

						normal = vec3::normalVec(vtx[0], vtx[1], vtx[2]);
						test = vtx[0].y - ((work.x - vtx[0].x) * normal.x + (work.z - vtx[0].z) * normal.z) / normal.y;
						return test;
					}

					if (face % 2 == 1 &&
						vec3::crossProduct(vtx[0], work, vtx[3]).y >= 0 &&
						vec3::crossProduct(vtx[2], work, vtx[0]).y >= 0 &&
						vec3::crossProduct(vtx[3], work, vtx[2]).y >= 0)
					{
						vec3 normal;	//面の法線ベクトル
						float check[3];
						float test;
						check[0] = vec3::normalVec(vtx[3], vtx[0], work).y;
						check[1] = vec3::normalVec(vtx[0], vtx[2], work).y;
						check[2] = vec3::normalVec(vtx[2], vtx[3], work).y;

						normal = vec3::normalVec(vtx[0], vtx[2], vtx[3]);
						test = vtx[0].y - ((work.x - vtx[0].x) * normal.x + (work.z - vtx[0].z) * normal.z) / normal.y;
						return test;
					}
				}
			}
		}
	}

	return 0;
}