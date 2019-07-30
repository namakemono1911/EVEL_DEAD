/*****************************************************************************
outlaw2D.cpp
Aythor	: 上野　匠
Data	: 2017_07_05
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//ファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "scene.h"
#include "outlaw2D.h"
#include "renderer.h"

//////////////////////////////////////////////////////////////////////////////
//定数定義
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//静的メンバ変数初期化
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//関数名	: Outlaw2D::init
//返り値	: 
//説明		: 初期化
//////////////////////////////////////////////////////////////////////////////
HRESULT	Outlaw2D::init	( void )
{
	//変数宣言
	LPDIRECT3DDEVICE9	device;	//デバイス情報
	VERTEX2D	*pVtx = NULL;	//仮想アドレス用ポインタ

	//デバイス情報取得
	device = Renderer::getDevice();

	//頂点バッファの設定
	if (FAILED(device->CreateVertexBuffer
	(
		sizeof(VERTEX2D) * NUM_VERTEX,	//頂点バッファサイズ
		D3DUSAGE_WRITEONLY,				//頂点バッファの使用方法
		FVF_VERTEX_2D,					//登録設定
		D3DPOOL_MANAGED,				//メモリ管理方法
		&mVtx,							//頂点バッファ管理インターフェイス
		NULL
	)
	))
	{
		return E_FAIL;
	}

	//バッファ登録開始
	mVtx->Lock(0, 0, (void**)&pVtx, 0);

	//座標設定
	pVtx[0].pos = D3DXVECTOR3(mLen * -cosf(mAngle + mRot) + mPos.x,
		mLen * -sinf(mAngle + mRot) + mPos.y,
		0.f);

	pVtx[1].pos = D3DXVECTOR3(mLen * cosf(mAngle + mRot) + mPos.x,
		mLen * -sinf(mAngle + mRot) + mPos.y,
		0.f);

	pVtx[2].pos = D3DXVECTOR3(mLen * -cosf(mAngle + mRot) + mPos.x,
		mLen * sinf(mAngle + mRot) + mPos.y,
		0.f);

	pVtx[3].pos = D3DXVECTOR3(mLen * cosf(mAngle + mRot) + mPos.x,
		mLen * sinf(mAngle + mRot) + mPos.y,
		0.f);

	//テクスチャ設定
	pVtx[0].tex = D3DXVECTOR2(0.f, 0.f);
	pVtx[1].tex = D3DXVECTOR2(1.f, 0.f);
	pVtx[2].tex = D3DXVECTOR2(0.f, 1.f);
	pVtx[3].tex = D3DXVECTOR2(1.f, 1.f);

	//頂点色設定
	pVtx[0].color =
	pVtx[1].color =
	pVtx[2].color =
	pVtx[3].color = mColor;

	//rhw設定
	pVtx[0].rhw =
	pVtx[1].rhw =
	pVtx[2].rhw =
	pVtx[3].rhw = 1.f;

	//登録終了
	mVtx->Unlock();

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Outlaw2D::uninit
//返り値	: 
//説明		: 終了
//////////////////////////////////////////////////////////////////////////////
void	Outlaw2D::uninit	( void )
{
	//テクスチャバッファ解放
	if(mTex != NULL)
	{
		mTex->Release();
		mTex = NULL;
	}

	//頂点バッファ解放
	if(mVtx != NULL)
	{
		mVtx->Release();
		mVtx = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Outlaw2D::update
//返り値	: 
//説明		: 更新
//////////////////////////////////////////////////////////////////////////////
void	Outlaw2D::update	( void )
{
	//変数宣言
	VERTEX2D	*pVtx;

	//バッファ登録開始
	mVtx->Lock(0, 0, (void**)&pVtx, 0);

	//座標設定
	pVtx[0].pos = D3DXVECTOR3(
		mLen * -cosf(mAngle + mRot) + mPos.x,
		mLen * -sinf(mAngle + mRot) + mPos.y,
		0.f);

	pVtx[1].pos = D3DXVECTOR3(
		mLen * cosf(mAngle - mRot) + mPos.x,
		mLen * -sinf(mAngle - mRot) + mPos.y,
		0.f);

	pVtx[2].pos = D3DXVECTOR3(
		mLen * -cosf(mAngle - mRot) + mPos.x,
		mLen * sinf(mAngle - mRot) + mPos.y,
		0.f);

	pVtx[3].pos = D3DXVECTOR3(
		mLen * cosf(mAngle + mRot) + mPos.x,
		mLen * sinf(mAngle + mRot) + mPos.y,
		0.f);

	//頂点色設定
	pVtx[0].color =
		pVtx[1].color =
		pVtx[2].color =
		pVtx[3].color = mColor;

	//登録終了
	mVtx->Unlock();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Outlaw2D::draw
//返り値	: 
//説明		: 描画
//////////////////////////////////////////////////////////////////////////////
void Outlaw2D::draw	( void )
{
	//変数宣言
	LPDIRECT3DDEVICE9	device;		//デバイス情報

	//デバイス情報取得
	device = Renderer::getDevice();

	//ストリーム作成
	device->SetStreamSource(0, mVtx, 0, sizeof(VERTEX2D));

	//頂点フォーマットの設定
	device->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	device->SetTexture(0, mTex);

	//ポリゴンの描画
	device->DrawPrimitive
	(
		D3DPT_TRIANGLESTRIP,	//ポリゴンの種類
		0,						//オフセット(頂点数)
		NUM_POLYGON				//ポリゴンの数
	);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Outlaw2D::setAll
//返り値	: 
//説明		: 全部設定
//////////////////////////////////////////////////////////////////////////////
void	Outlaw2D::setAll(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR2 texPos, D3DXVECTOR2 texSize, D3DXCOLOR color)
{
	mPos = pos;
	mSize = size;
	mTexPos = texPos;
	mTexSize = texSize;
	mColor = color;

	mLen = sqrtf(size.x * size.x + size.y * size.y);
	mAngle = atan2f(size.y, size.x);
	mRot = 0.f;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Outlaw2D::loadTex
//返り値	: 
//説明		: テクスチャ読み込み
//////////////////////////////////////////////////////////////////////////////
void	Outlaw2D::loadTex	( const char *fileName )
{
	//変巣宣言
	LPDIRECT3DDEVICE9 device = Renderer::getDevice();

	//テクスチャの読み込み
	if (FAILED(D3DXCreateTextureFromFile(device, fileName, &mTex)))
	{
		char message[256];
		sprintf(message, "%sが読み込めませんでした", fileName);

		MessageBox(NULL, message, "テクスチャ読み込みエラー", MB_OK);
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Outlaw2D::bindTex
//返り値	: 
//説明		: テクスチャコピー
//////////////////////////////////////////////////////////////////////////////
void	Outlaw2D::bindTex	( LPDIRECT3DTEXTURE9 texBuf )
{
	mTex = texBuf;
}