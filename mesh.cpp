/*****************************************************************************
mesh.h
Aythor	: 上野　匠
Data	: 2017_05_18
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "scene.h"
#include "mesh.h"
#include "renderer.h"

//////////////////////////////////////////////////////////////////////////////
//関数名	: Mesh::init
//返り値	: 
//説明		: 初期化
//////////////////////////////////////////////////////////////////////////////
HRESULT	Mesh::init	(void)
{
	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Mesh::uninit
//返り値	: 
//説明		: 終了
//////////////////////////////////////////////////////////////////////////////
void	Mesh::uninit	( void )
{
	//頂点バッファ解放
	if (mVtxBuf != NULL)
	{
		mVtxBuf->Release();
		mVtxBuf = NULL;
	}

	//テクスチャバッファ解放
	if (mTex != NULL)
	{
		mTex->Release();
		mTex = NULL;
	}

	//Scene解放
	release();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Mesh::update
//返り値	: 
//説明		: 更新
//////////////////////////////////////////////////////////////////////////////
void	Mesh::update	( void )
{
	//変数宣言
	VERTEX3D	*pVtx;		//頂点情報ポインタ

	for(UINT i = 0; i < mNumVtx; i++)
	{
		mVtxBuf->Lock(0, 0, (void**)&pVtx, 0);

		//頂点色
		pVtx[0].color = mColor;

		mVtxBuf->Unlock();
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Mesh::draw
//返り値	: 
//説明		: 描画
//////////////////////////////////////////////////////////////////////////////
void	Mesh::draw	( void )
{
	//変数宣言
	LPDIRECT3DDEVICE9	device = Renderer::getDevice();

	//ストリーム作成
	device->SetStreamSource(0, mVtxBuf, 0, sizeof(VERTEX3D));

	//頂点フォーマットの設定
	device->SetFVF(FVF_VERTEX_3D);

	//サンプラーステートの設定
	device->SetIndices(mIdxBuf);

	//テクスチャセット
	device->SetTexture(0, mTex);

	//ワールドマトリックス設定
	setMtx(device);
	
	//ポリゴンの描画
	device->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,		//描画方法
		0,							//最初の頂点インデックスまでのオフセット
		0,							//最小の頂点インデックス
		mNumVtx,					//頂点数
		0,							//スタートインデックス
		mNumPrim);					//プリミティブ数
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Mesh::setMtx
//返り値	: 
//説明		: ワールド行列設定
//////////////////////////////////////////////////////////////////////////////
void	Mesh::setMtx	( LPDIRECT3DDEVICE9 device )
{
	//変数宣言
	D3DXMATRIX	world;		//ワールド行列
	D3DXMATRIX	move;		//平行移動行列
	D3DXMATRIX	rot;		//回転行列
	D3DXVECTOR3	pos;		//移動座標

	//行列初期化
	D3DXMatrixIdentity(&world);

	//平行移動
	D3DXMatrixTranslation(&move,
		mTransform.pos.x,
		mTransform.pos.y,
		mTransform.pos.z);

	//回転
	D3DXMatrixRotationYawPitchRoll(&rot,
		mTransform.rot.x,
		mTransform.rot.y,
		mTransform.rot.z);		//回転行列

	//行列合成
	world *= rot;		//回転
	world *= move;		//平行移動

	device->SetTransform(D3DTS_WORLD, &world);		//行列をデバイスに設定
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Mesh::makeVtxBuf
//返り値	: 生成した頂点バッファ
//説明		: 頂点バッファ作成
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3DVERTEXBUFFER9	Mesh::makeVtxBuf	(const UINT numVtx)
{
	//変数宣言
	LPDIRECT3DDEVICE9	device = Renderer::getDevice();

	mNumVtx = numVtx;

	//=============================
	// 頂点バッファ作成
	//=============================
	if (FAILED(device->CreateVertexBuffer
	(
		sizeof(VERTEX3D) * mNumVtx,				//頂点バッファサイズ
		D3DUSAGE_WRITEONLY,						//頂点バッファの使用方法
		FVF_VERTEX_3D,							//なんか設定
		D3DPOOL_MANAGED,						//メモリ管理方法
		&mVtxBuf,								//頂点バッファ管理インターフェイス
		NULL)))
	{
		return NULL;
	}

	return mVtxBuf;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Mesh::makeIdxBuf
//返り値	: 生成したインデックスバッファ
//説明		: インデックスバッファ作成
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3DINDEXBUFFER9	Mesh::makeIdxBuf	(const UINT numIdx)
{
	//変数宣言
	LPDIRECT3DDEVICE9	device = Renderer::getDevice();

	//=============================
	// インデックス作成
	//=============================
	if(FAILED(device->CreateIndexBuffer(
		sizeof(WORD) *  numIdx,	//必要なインデックスサイズ
		D3DUSAGE_WRITEONLY,		//使用用途フラグ
		D3DFMT_INDEX16,			//インデックスのフォーマット
		D3DPOOL_MANAGED,		//メモリの管理方法（お任せモード）
		&mIdxBuf,				//インデックスバッファインターフェイス
		NULL)))
	{
		return NULL;
	}

	return mIdxBuf;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Mesh::loadTex
//返り値	: 
//説明		: 指定されたテクスチャ読み込み
//////////////////////////////////////////////////////////////////////////////
void Mesh::loadTex(const char * texName)
{
	//変数宣言
	LPDIRECT3DDEVICE9 device = Renderer::getDevice();

	//テクスチャの読み込み
	if (FAILED(D3DXCreateTextureFromFile(device, texName, &mTex)))
	{
		MessageBox(NULL, "エラー", "fieldエラー", MB_OK);
		return;
	}
}
