/*****************************************************************************
メッシュドーム描画
Aythor	: 上野　匠
Data	: 2016_12_23
=============================================================================
Updata

*****************************************************************************/
#include "main.h"
#include "scene.h"
#include "sky.h"
#include "renderer.h"
#include "manager.h"

//////////////////////////////////////////////////////////////////////////////
//定数定義
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//構造体定義
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//静的メンバ変数初期化
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9	Sky::mTexBuf[SKY_TEX_MAX] = {NULL};
const char	*Sky::mTexName[SKY_TEX_MAX] =
{
	"data/texture/sky001.jpg",

};

//////////////////////////////////////////////////////////////////////////////
//関数名	: initMeshDome
//返り値	: 
//説明		: ポリゴン初期化
//////////////////////////////////////////////////////////////////////////////
HRESULT Sky::init( void )
{
	//変数宣言
	UINT	numPtv;	//必要な面の数

	//必要な面の数計算
	numPtv = (int)mNumTyle.y + ((int)mNumTyle.y - 1) * 4;
	numPtv += ((int)mNumTyle.x - 1) * ((int)mNumTyle.y + 1) * 2;

	//セット
	setNumPrim(numPtv);

	//親クラスに各種設定
	setAll(mPos, mRot, mColor, D3DXVECTOR2(0.f, 0.f), D3DXVECTOR2(0.f, 0.f));

	return	S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: uninitMeshDome
//返り値	: 
//説明		: ポリゴン終了
//////////////////////////////////////////////////////////////////////////////
void	Sky::uninit( void )
{
	//テクスチャバッファの解放
	for(int i = 0; i < SKY_TEX_MAX; i++)
	{
		if(mTexBuf[i]	!=	NULL)
		{
			mTexBuf[i]->Release();
			mTexBuf[i]	=	NULL;
		}
	}

	Mesh::uninit();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: updateMeshDome
//返り値	: 
//説明		: ポリゴン更新
//////////////////////////////////////////////////////////////////////////////
void	Sky::update( void )
{
	setRot(getRot() + mRot);

	Mesh::update();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: drawMeshDome
//返り値	: 
//説明		: ポリゴン描写
//////////////////////////////////////////////////////////////////////////////
void Sky::draw( void )
{
	//ライトの影響off
	Manager::getRenderer()->getDevice()->SetRenderState(D3DRS_LIGHTING, false);

	Mesh::draw();

	//ライトの影響on
	Manager::getRenderer()->getDevice()->SetRenderState(D3DRS_LIGHTING, true);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: setMeshDome
//返り値	: 
//説明		: フィールド設定
//////////////////////////////////////////////////////////////////////////////
Sky	*Sky::create (D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR2 numTyle, D3DXCOLOR color, float len, SKY_TEX tex)
{
	//変数宣言
	Sky	*sky;

	//生成
	sky = new Sky;

	//初期化
	sky->setVal(pos, numTyle, color, rot, len, tex);
	sky->bindTexBuf(mTexBuf[tex]);
	sky->makeVtx(numTyle);
	sky->init();

	return sky;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Sky::setVal
//返り値	: 
//説明		: 変数設定
//////////////////////////////////////////////////////////////////////////////
void	Sky::setVal(D3DXVECTOR3 pos, D3DXVECTOR2 numTyle, D3DXCOLOR color, D3DXVECTOR3 rot, float len, SKY_TEX tex)
{
	//変数代入
	mPos = pos;
	mNumTyle = numTyle;
	mColor = color;
	mRot = rot;
	mLen = len;
	mTex = tex;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: makeVertexMeshDome
//返り値	: 
//説明		: ポリゴン描画位置設定
//////////////////////////////////////////////////////////////////////////////
HRESULT	Sky::makeVtx(D3DXVECTOR2 numTyle)
{
	//変数宣言
	VERTEX3D	*pVtx;		//仮想アドレス用ポインタ
	float		posY;		//描画位置
	float		len;		//半径
	float		rot;		//角度
	int			x, y;		//xとyのループ
	int			num;		//必要な頂点数
	D3DXVECTOR3	fullSize;	//フィールド全体のサイズ
	LPDIRECT3DVERTEXBUFFER9 vtx;	//頂点バッファ

	//=============================
	// 何頂点必要か
	//=============================
	num	=	(int)numTyle.x * ((int)numTyle.y + 1) + 1;

	//=============================
	// 頂点バッファ作成
	//=============================
	if((vtx = makeVtxBuf(num)) == NULL)
	{
		return E_FAIL;
	}

	//=============================
	// 頂点情報登録
	//=============================
	vtx->Lock(0, 0, (void**)&pVtx, 0);

	//ドームの頂点
	pVtx[0].pos		=	D3DXVECTOR3(
		0.f,
		mLen,
		0.f);

	//頂点色
	pVtx[0].color	= mColor;

	//テクスチャ座標
	pVtx[0].tex		= D3DXVECTOR2(0.f, 0.f);

	//ポインタ移動
	pVtx++;

	for(y = 0; y < mNumTyle.x; y++)
	{
		//角度算出
		rot	=	90 * ((mNumTyle.x - (y + 1)) / mNumTyle.x);

		//Y座標確定
		posY	= mLen * sin(rot * (PI / 180));
		len		= mLen * cos(rot * (PI / 180));

		for(x = 0; x < mNumTyle.y + 1; x++)
		{
			//x,zの角度
			rot	=	360 * (x / mNumTyle.y);

			//座標
			pVtx[0].pos	=	D3DXVECTOR3(
				len * cos(rot * (PI / 180)),
				posY,
				len * sin(rot * (PI / 180)));

			//頂点色
			pVtx[0].color	=	mColor;

			//テクスチャ座標
			pVtx[0].tex		=	D3DXVECTOR2(
				(1.f / mNumTyle.y) * x,
				(1.f / mNumTyle.x) * (y + 1));

			//ポインタ移動
			pVtx++;
		}
	}
				
	vtx->Unlock();

	//バッファバインド
	bindVtxBuf(vtx);

	//=============================
	// インデックス作成
	//=============================
	makeIdx();

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: makeIndexBuffer
//返り値	: 
//説明		: ポリゴン描画位置設定
//////////////////////////////////////////////////////////////////////////////
HRESULT	Sky::makeIdx(void)
{
	//変数宣言
	WORD		*pIdx;	//インデックス番号
	int			x, y;	//xとzのloop
	int			num;	//必要なインデックス数
	LPDIRECT3DINDEXBUFFER9	idx;	//インデックスバッファ
	
	//=============================
	// 何頂点必要か
	//=============================
	num	=	5 * (int)mNumTyle.y;
	num	+=	(int)(mNumTyle.y + 1) * ((int)mNumTyle.x - 1) * 2;

	//=============================
	// インデックス作成
	//=============================
	idx = makeIdxBuf(num);

	//=============================
	// インデックス登録
	//=============================
	idx->Lock(0, 0, (void**)&pIdx, 0);

	//ドームの1番上
	for(int k = 0; k < mNumTyle.y; k++)
	{
		pIdx[0]	=	0;
		pIdx[1]	=	(WORD)k + 1 + (WORD)k % 2;
		pIdx[2]	=	(WORD)k + 2 - (WORD)k % 2;
		pIdx	+=	3;

		//縮退ポリゴン
		if(k < mNumTyle.y - 1)
		{
			pIdx[3]	=	pIdx[2];
			pIdx[0]	=	0;
			pIdx	+=	2;
		}
	}

	//そっから下
	for(y = 0; y < mNumTyle.x - 1; y++)
	{
		for(x = 0; x < mNumTyle.y + 1; x++)
		{
			pIdx[0]	=	(WORD)((mNumTyle.y + 1) * y + x + 1);
			pIdx[1]	=	(WORD)((mNumTyle.y + 1) * (y + 1) + x + 1);
			pIdx	+=	2;
		}
	}

	idx->Unlock();

	//バッファバインド
	bindIdxBuf(idx);

	return	S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Sky::loadTex
//返り値	: 
//説明		: テクスチャ読み込み
//////////////////////////////////////////////////////////////////////////////
HRESULT	Sky::loadTex(void)
{
	for(UINT i = 0; i < SKY_TEX_MAX; i++)
	{
		//テクスチャの読み込み
		if(FAILED(D3DXCreateTextureFromFile(Renderer::getDevice(), mTexName[i], &mTexBuf[i])))
		{
			MessageBox(NULL, "Sky", "エラー", MB_OK);
			return	E_FAIL;
		}
	}

	return S_OK;
}