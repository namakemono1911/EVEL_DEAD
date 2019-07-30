/*****************************************************************************
scene3D.cpp
Aythor	: 上野　匠
Data	: 2017_04_20
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//ファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "scene.h"
#include "scene3DState.h"
#include "scene3D.h"
#include "renderer.h"
#include "camera.h"
#include "scene3DTextureAnimation.h"
#include "scene3DBillboard.h"

//////////////////////////////////////////////////////////////////////////////
//グローバル変数
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//関数名	: Scene3D::init
//返り値	: 
//説明		: 初期化
//////////////////////////////////////////////////////////////////////////////
HRESULT	Scene3D::init	(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9	device = Renderer::getDevice();

	//変数初期化
	mMyName = "3Dpolygon";
	mAngle = atan2f(mTransform.size.y, mTransform.size.x);
	mRot = 0.f;
	mLen = 5.f;
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

	//頂点情報登録
	setVertexBuffer();

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Scene3D::uninit
//返り値	: 
//説明		: 終了
//////////////////////////////////////////////////////////////////////////////
void	Scene3D::uninit	( void )
{
	//頂点バッファ解放
	if(mVtx != NULL)
	{
		mVtx->Release();
		mVtx = NULL;
	}

	for (auto& state : mStateList)
		delete state;

	//リリース
	release();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Scene3D::update
//返り値	: 
//説明		: 更新
//////////////////////////////////////////////////////////////////////////////
void	Scene3D::update	( void )
{
	for (auto& state : mStateList)
		state->update();

	//頂点情報登録
	setVertexBuffer();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Scene3D::draw
//返り値	: 
//説明		: 描画
//////////////////////////////////////////////////////////////////////////////
void	Scene3D::draw	( void )
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
	device->SetTexture(0, mTex);

	//行列設定
	device->SetTransform(D3DTS_WORLD, &mMatrix);

	//ポリゴンの描画
	device->DrawPrimitive
	(
		D3DPT_TRIANGLESTRIP,	//ポリゴンの種類
		0,						//オフセット(頂点数)
		NUM_POLYGON				//ポリゴンの数
	);

	//ライトの影響on
	device->SetRenderState(D3DRS_LIGHTING, true);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: create
//返り値	: 
//説明		: 生成
//////////////////////////////////////////////////////////////////////////////
Scene3D * Scene3D::create(Dvec3 pos, Dvec3 rot, Dvec3 size, LPDIRECT3DTEXTURE9 texture, Dvec2 texPos, Dvec2 texSize, Dcolor color)
{
	auto polygon = new Scene3D;
	polygon->mTransform = Transform(pos, rot, Dvec3(1, 1, 1));
	polygon->mTexPos = texPos;
	polygon->mTexSize = texSize;
	polygon->mTex = texture;
	polygon->setRect(size);
	polygon->init();

	return polygon;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: create
//返り値	: 
//説明		: 生成
//////////////////////////////////////////////////////////////////////////////
Scene3D * Scene3D::create(Dvec3 topLeft, Dvec3 topRight, Dvec3 bottomLeft, Dvec3 bottomRight, Dvec3 pos, Dvec3 rot, Dvec3 size, LPDIRECT3DTEXTURE9 texture, Dvec2 texPos, Dvec2 texSize, Dcolor color)
{
	auto polygon = new Scene3D;
	polygon->mRectPos[0] = topLeft;
	polygon->mRectPos[1] = topRight;
	polygon->mRectPos[2] = bottomLeft;
	polygon->mRectPos[3] = bottomRight;
	polygon->mTexPos = texPos;
	polygon->mTexSize = texSize;
	polygon->mTex = texture;
	polygon->init();

	return polygon;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: setRect
//返り値	: 
//説明		: 矩形設定
//////////////////////////////////////////////////////////////////////////////
void Scene3D::setRect(Dvec3 size)
{
	Dvec3 line = size * 0.5f;
	mRectPos[0] = Dvec3(-line.x, line.y, 0.f);
	mRectPos[1] = Dvec3(line.x, line.y, 0.f);
	mRectPos[2] = Dvec3(-line.x, -line.y, 0.f);
	mRectPos[3] = Dvec3(line.x, -line.y, 0.f);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: setTextureAnimation
//返り値	: 
//説明		: テクスチャアニメーション設定
//////////////////////////////////////////////////////////////////////////////
void Scene3D::setTextureAnimation(int numVertical, int numHorizonal, int interval)
{
	mStateList.push_back(Scene3DTextureAnimation::create(this, numVertical, numHorizonal, interval));
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: setBillboard
//返り値	: 
//説明		: ビルボード設定
//////////////////////////////////////////////////////////////////////////////
void Scene3D::setBillboard()
{
	mStateList.push_back(Scene3DBillboard::create(this));
}

void Scene3D::setVertexBuffer()
{
	VERTEX3D	*vtx;
	mVtx->Lock(0, 0, (void**)&vtx, 0);

	//座標設定
	vtx[0].pos = mRectPos[0];
	vtx[1].pos = mRectPos[1];
	vtx[2].pos = mRectPos[2];
	vtx[3].pos = mRectPos[3];

	//テクスチャ設定
	vtx[0].tex = mTexPos;
	vtx[1].tex = D3DXVECTOR2(mTexPos.x + mTexSize.x, mTexPos.y);
	vtx[2].tex = D3DXVECTOR2(mTexPos.x, mTexPos.y + mTexSize.y);
	vtx[3].tex = mTexPos + mTexSize;

	//頂点色設定
	vtx[0].color =
		vtx[1].color =
		vtx[2].color =
		vtx[3].color = D3DCOLOR_RGBA(255, 255, 255, 255);

	//法線ベクトル設定
	vtx[0].nor =
		vtx[1].nor =
		vtx[2].nor =
		vtx[3].nor = vec3::DcrossProduct(mRectPos[1], mRectPos[2], mRectPos[0]);

	mVtx->Unlock();
}
