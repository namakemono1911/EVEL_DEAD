/*****************************************************************************
scene2D.h
Aythor	: ���@��
Data	: 2017_04_19
=============================================================================
Updata

*****************************************************************************/
#ifndef SCENE2D_H
#define SCENE2D_H

#include "scene.h"

//////////////////////////////////////////////////////////////////////////////
//�N���X�錾
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
	LPDIRECT3DVERTEXBUFFER9		mVtx;	//���_�o�b�t�@
	LPDIRECT3DTEXTURE9			mTex;	//�e�N�X�`���o�b�t�@
	Dvec3	mPos;		//���W
	Dvec3	mSize;		//�T�C�Y
	D3DXVECTOR2	mTexPos;	//�e�N�X�`�����W
	D3DXVECTOR2	mTexSize;	//�e�N�X�`���T�C�Y
	D3DXCOLOR	mColor;		//���_�F
	float		mLen;		//����
	float		mAngle;		//�Ίp
	float		mRot;		//�p�x
};

#endif // !

