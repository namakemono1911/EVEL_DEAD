/*****************************************************************************
scene2D.h
Aythor	: 上野　匠
Data	: 2017_04_19
=============================================================================
Updata

*****************************************************************************/
#ifndef SCENE2D_H
#define SCENE2D_H

#include "scene.h"

//////////////////////////////////////////////////////////////////////////////
//クラス宣言
//////////////////////////////////////////////////////////////////////////////
class Scene2D : public Scene
{
public:
	Scene2D(UINT priolity = PRIME_FORTH):Scene(priolity){}
	~Scene2D(){};
	HRESULT init	( void );
	void	uninit	( void );
	void	update	( void );
	void	draw	( void );

	Dvec3	getPos	( void ){return mPos;}
	Dvec3	getSize	( void ){return mSize;}
	D3DXCOLOR	getColor(void){return mColor;}
	Dvec3		getRot	( void ){return Dvec3(mRot, 0, 0);}
	Dvec3		*getPosAd(void){return &mPos;}
	Dvec3		*getSizeAd(void){return &mSize;}
	Dvec3		*getRotAd(void){return nullptr;}

	void	setRot	( float rot ){mRot = rot;}
	void	setColor(D3DXCOLOR color){mColor = color;}
	void	setAll	( Dvec3 pos, Dvec3 size, D3DXVECTOR2 texPos, D3DXVECTOR2 texSize, D3DXCOLOR color = D3DXCOLOR(1.f, 1.f, 1.f, 1.f) );

	void	loadTex	( const char *fileName );
	void	bindTex	( LPDIRECT3DTEXTURE9 texBuf );

private:
	LPDIRECT3DVERTEXBUFFER9		mVtx;	//頂点バッファ
	LPDIRECT3DTEXTURE9			mTex;	//テクスチャバッファ
	Dvec3	mPos;		//座標
	Dvec3	mSize;		//サイズ
	D3DXVECTOR2	mTexPos;	//テクスチャ座標
	D3DXVECTOR2	mTexSize;	//テクスチャサイズ
	D3DXCOLOR	mColor;		//頂点色
	float		mLen;		//長さ
	float		mAngle;		//対角
	float		mRot;		//角度
};

#endif // !

