/*****************************************************************************
outlaw2D.h
Aythor	: 上野　匠
Data	: 2017_07_05
=============================================================================
Updata

*****************************************************************************/
#ifndef OUTLAW2D_H
#define OUTLAW2D_H
//////////////////////////////////////////////////////////////////////////////
//クラス宣言
//////////////////////////////////////////////////////////////////////////////
class Outlaw2D
{
public:
	Outlaw2D(){};
	~Outlaw2D(){};
	HRESULT init	( void );
	void	uninit	( void );
	void	update	( void );
	void	draw	( void );

	D3DXVECTOR3	getPos	( void ){return mPos;}
	D3DXVECTOR3	getSize	( void ){return mSize;}
	D3DXCOLOR	getColor(void){return mColor;}
	float		getRot	( void ){return mRot;}

	void	setRot	( float rot ){mRot = rot;}
	void	setColor(D3DXCOLOR color){mColor = color;}
	void	setAll	( D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR2 texPos, D3DXVECTOR2 texSize, D3DXCOLOR color = D3DXCOLOR(1.f, 1.f, 1.f, 1.f) );

	void	loadTex	( const char *fileName );
	void	bindTex	( LPDIRECT3DTEXTURE9 texBuf );

private:
	LPDIRECT3DVERTEXBUFFER9		mVtx;	//頂点バッファ
	LPDIRECT3DTEXTURE9			mTex;	//テクスチャバッファ
	D3DXVECTOR3	mPos;		//座標
	D3DXVECTOR3	mSize;		//サイズ
	D3DXVECTOR2	mTexPos;	//テクスチャ座標
	D3DXVECTOR2	mTexSize;	//テクスチャサイズ
	D3DXCOLOR	mColor;		//頂点色
	float		mLen;		//長さ
	float		mAngle;		//対角
	float		mRot;		//角度
};

#endif // !

