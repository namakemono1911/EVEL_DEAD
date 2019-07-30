/*****************************************************************************
outlaw2D.h
Aythor	: ���@��
Data	: 2017_07_05
=============================================================================
Updata

*****************************************************************************/
#ifndef OUTLAW2D_H
#define OUTLAW2D_H
//////////////////////////////////////////////////////////////////////////////
//�N���X�錾
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
	LPDIRECT3DVERTEXBUFFER9		mVtx;	//���_�o�b�t�@
	LPDIRECT3DTEXTURE9			mTex;	//�e�N�X�`���o�b�t�@
	D3DXVECTOR3	mPos;		//���W
	D3DXVECTOR3	mSize;		//�T�C�Y
	D3DXVECTOR2	mTexPos;	//�e�N�X�`�����W
	D3DXVECTOR2	mTexSize;	//�e�N�X�`���T�C�Y
	D3DXCOLOR	mColor;		//���_�F
	float		mLen;		//����
	float		mAngle;		//�Ίp
	float		mRot;		//�p�x
};

#endif // !

