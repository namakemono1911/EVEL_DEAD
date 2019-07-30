/*****************************************************************************
mesh.h
Aythor	: 上野　匠
Data	: 2017_05_18
=============================================================================
Updata

*****************************************************************************/
#ifndef MESH_H
#define MESH_H

#include "scene.h"

//////////////////////////////////////////////////////////////////////////////
//前方宣言
//////////////////////////////////////////////////////////////////////////////
class Scene;

//////////////////////////////////////////////////////////////////////////////
//クラス定義
//////////////////////////////////////////////////////////////////////////////
class Mesh : public Scene
{
public:
	Mesh(UINT priolity = PRIME_THIRD):Scene(priolity){}
	~Mesh(){}

	HRESULT	init	( void );
	void	uninit	( void );
	void	update	( void );
	void	draw	( void );
	D3DXVECTOR3	getSize	( void ){return D3DXVECTOR3(0.f, 0.f, 0.f);}

	//セッター
	void	bindVtxBuf	(LPDIRECT3DVERTEXBUFFER9 vtx){mVtxBuf = vtx;}
	void	bindIdxBuf	(LPDIRECT3DINDEXBUFFER9	idx){mIdxBuf = idx;}
	void	loadTex		(const char *texName);
	void	bindTexBuf	(LPDIRECT3DTEXTURE9	tex){mTex = tex;}
	void	setNumVtx	(UINT numVtx){mNumVtx = numVtx;}
	void	setNumPrim	(UINT numPrim){mNumPrim = numPrim;}
	LPDIRECT3DVERTEXBUFFER9	makeVtxBuf	(const UINT numVtx);
	LPDIRECT3DINDEXBUFFER9	makeIdxBuf	(const UINT numIdx);
	void	setTexPos	(D3DXVECTOR2 texPos){mTexPos = texPos;}
	void	setRot(D3DXVECTOR3 rot){mTransform.rot = rot;}
	void	setAll		(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR color, D3DXVECTOR2 texPos, D3DXVECTOR2 texMove)
	{
		mTransform.pos = pos;
		mTransform.rot = rot;
		mColor = color;
		mTexPos = texPos;
		mTexMove = texMove;
	}

	//ゲッター
	LPDIRECT3DVERTEXBUFFER9	getVtxBuf	(void){return mVtxBuf;}
	D3DXVECTOR2		getTexPos	(void){return mTexPos;}
	D3DXVECTOR2		getTexMove	(void){return mTexMove;}
	UINT			getNumVtx	(void){return mNumVtx;}

private:
	//プロトタイプ宣言
	void	setMtx	(LPDIRECT3DDEVICE9 device);

	LPDIRECT3DVERTEXBUFFER9		mVtxBuf;	//頂点バッファ
	LPDIRECT3DINDEXBUFFER9		mIdxBuf;	//インデックスバッファ
	LPDIRECT3DTEXTURE9			mTex;		//テクスチャ

	D3DXCOLOR		mColor;		//頂点色
	D3DXVECTOR2		mTexPos;	//テクスチャ座標
	D3DXVECTOR2		mTexMove;	//テクスチャアニメーションの移動速度
	UINT			mNumVtx;	//描画する頂点数
	UINT			mNumPrim;	//描画する面の数	
};

#endif