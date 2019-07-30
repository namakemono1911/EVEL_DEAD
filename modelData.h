/*****************************************************************************
modelData.h
Aythor	: 上野　匠
Data	: 2017_07_07
=============================================================================
Updata

*****************************************************************************/
#ifndef MODEL_DATA_H
#define MODEL_DATA_H
//////////////////////////////////////////////////////////////////////////////
//インクルード
//////////////////////////////////////////////////////////////////////////////
#include <filesystem>
#include <map>
#include "renderer.h"
#include "scene.h"

//////////////////////////////////////////////////////////////////////////////
//ネームスペース
//////////////////////////////////////////////////////////////////////////////
namespace sys = std::tr2::sys;

//////////////////////////////////////////////////////////////////////////////
//前方宣言
//////////////////////////////////////////////////////////////////////////////
class Renderer;

//////////////////////////////////////////////////////////////////////////////
//構造体定義
//////////////////////////////////////////////////////////////////////////////
typedef struct
{
	LPD3DXMESH			mesh;		//メッシュ情報インターフェース
	DWORD				numMat;		//マテリアル情報数
	D3DMATERIAL9		*mat;		//マテリアル情報
	LPDIRECT3DTEXTURE9	*tex;		//テクスチャ情報インターフェース
}XMODEL_DATA;

//////////////////////////////////////////////////////////////////////////////
//ModelDataクラス宣言
//////////////////////////////////////////////////////////////////////////////
class ModelData
{
public:
	ModelData(){}
	~ModelData(){}

	virtual HRESULT	init(void) = 0;
	virtual void	uninit(void) = 0;
	virtual void	draw(const Dmtx matrix) = 0;
	static	void	loadAllModel(void); 
	static	void	modelDataAllClear(void);

	//ゲッター
	string		getModelName(void){return mName;}

	//セッター
	static ModelData	*createModelData(string fileName);

protected:
	static ModelData	*create(ModelData *ModelType, string fileName);
	static void			readModelFile(sys::path path);
	LPDIRECT3DTEXTURE9	*mTex;			//テクスチャ情報インターフェース
	string				mName;			//モデルの名前
};
//////////////////////////////////////////////////////////////////////////////
//Xmodelクラス宣言
//////////////////////////////////////////////////////////////////////////////
class NullModel : public ModelData
{
public:
	HRESULT	init(void){return E_FAIL;}
	void	uninit(void){}
	void	draw(const Dmtx matrix){Renderer::getDevice()->SetTransform(D3DTS_WORLD, &matrix);}
	void	allClear(void) {}
};

//////////////////////////////////////////////////////////////////////////////
//Xmodelクラス宣言
//////////////////////////////////////////////////////////////////////////////
class Xmodel : public ModelData
{
public:
	Xmodel(){}
	~Xmodel(){}

	HRESULT	init(void);
	void	uninit(void);
	void	draw(const Dmtx matrix);
	static void	allClear(void);

	static void	setModelData(sys::path path);
	HRESULT getMesh(LPD3DXMESH *cloneMehs)
	{
		return mModelData.mesh->CloneMeshFVF(mModelData.mesh->GetOptions(), FVF_VERTEX_3D, Renderer::getDevice(), cloneMehs);
	}

private:
	//プロトタイプ宣言
	static map<string, XMODEL_DATA>		meshDataMap;
	HRESULT loadModel(void);

	//変数宣言
	XMODEL_DATA		mModelData;
};

#endif // !MODEL_DATA_H
