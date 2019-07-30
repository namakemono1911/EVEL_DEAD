/*****************************************************************************
sceneGrid.cpp
Aythor	: 上野　匠
Data	: 2017_07_26
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//ファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "manager.h"
#include "sceneGrid.h"

//////////////////////////////////////////////////////////////////////////////
//定数定義
//////////////////////////////////////////////////////////////////////////////
#define NUM_GRIT	(11)		//グリット数

//////////////////////////////////////////////////////////////////////////////
//関数名	: SceneGrid::init
//返り値	: 
//説明		: 初期化
//////////////////////////////////////////////////////////////////////////////
HRESULT SceneGrid::init(void)
{

	//変数宣言
	LPDIRECT3DDEVICE9	device = Renderer::getDevice();

	//変数初期化
	mMyName = "grid";
	setObjType(NONE);

	//=============================
	// 頂点バッファ作成
	//=============================
	if (FAILED(device->CreateVertexBuffer
	(sizeof(VERTEX3D) * NUM_VERTEX,			//頂点バッファサイズ
		D3DUSAGE_WRITEONLY,						//頂点バッファの使用方法
		FVF_VERTEX_3D,							//なんか設定
		D3DPOOL_MANAGED,						//メモリ管理方法
		&mVtx,									//頂点バッファ管理インターフェイス
		NULL)))
		return E_FAIL;

	VERTEX3D	*vtx;
	Dvec3	center = mTransform.size * 0.5f;
	mVtx->Lock(0, 0, (void**)&vtx, 0);

	//座標設定
	vtx[0].pos = mStartPos;
	vtx[1].pos = mEndPos;

	//テクスチャ設定
	vtx[0].tex = Dvec2(0, 0);
	vtx[1].tex = Dvec2(0, 0);

	//頂点色設定
	vtx[0].color =
	vtx[1].color = D3DCOLOR_RGBA(255, 255, 255, 255);

	//法線ベクトル設定
	vtx[0].nor =
	vtx[1].nor = Dvec3(-1, 0, 0);

	mVtx->Unlock();

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: SceneGrid::uninit
//返り値	: 
//説明		: 初期化
//////////////////////////////////////////////////////////////////////////////
void SceneGrid::uninit(void)
{
	if (mVtx != NULL)
	{
		mVtx->Release();
		mVtx = NULL;
	}

	release();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: SceneGrid::update
//返り値	: 
//説明		: 初期化
//////////////////////////////////////////////////////////////////////////////
void SceneGrid::update(void)
{
	VERTEX3D	*vtx;
	mVtx->Lock(0, 0, (void**)&vtx, 0);
	
	vtx[0].pos = mStartPos;
	vtx[1].pos = mEndPos;

	mVtx->Unlock();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: SceneGrid::draw
//返り値	: 
//説明		: 初期化
//////////////////////////////////////////////////////////////////////////////
void SceneGrid::draw(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9	device = Renderer::getDevice();

	//ストリーム作成
	device->SetStreamSource(0, mVtx, 0, sizeof(VERTEX3D));

	//ライトの影響off
	device->SetRenderState(D3DRS_LIGHTING, false);

	//頂点フォーマットの設定
	device->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	device->SetTexture(0, NULL);

	//行列設定
	device->SetTransform(D3DTS_WORLD, &mMatrix);

	//ポリゴンの描画
	device->DrawPrimitive
	(
		D3DPT_LINELIST,	//ポリゴンの種類
		0,						//オフセット(頂点数)
		1				//ポリゴンの数
	);

	//ライトの影響on
	device->SetRenderState(D3DRS_LIGHTING, true);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: SceneGrid::create
//返り値	: 
//説明		: 生成
//////////////////////////////////////////////////////////////////////////////
SceneGrid * SceneGrid::create(Dvec3 startPos, Dvec3 endPos)
{
	SceneGrid *grit = new SceneGrid;
	grit->mStartPos = startPos;
	grit->mEndPos = endPos;
	grit->init();

	return grit;
}
