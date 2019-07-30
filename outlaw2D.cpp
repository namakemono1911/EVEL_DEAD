/*****************************************************************************
outlaw2D.cpp
Aythor	: ���@��
Data	: 2017_07_05
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "scene.h"
#include "outlaw2D.h"
#include "renderer.h"

//////////////////////////////////////////////////////////////////////////////
//�萔��`
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//�v���g�^�C�v�錾
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//�ÓI�����o�ϐ�������
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Outlaw2D::init
//�Ԃ�l	: 
//����		: ������
//////////////////////////////////////////////////////////////////////////////
HRESULT	Outlaw2D::init	( void )
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9	device;	//�f�o�C�X���
	VERTEX2D	*pVtx = NULL;	//���z�A�h���X�p�|�C���^

	//�f�o�C�X���擾
	device = Renderer::getDevice();

	//���_�o�b�t�@�̐ݒ�
	if (FAILED(device->CreateVertexBuffer
	(
		sizeof(VERTEX2D) * NUM_VERTEX,	//���_�o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,				//���_�o�b�t�@�̎g�p���@
		FVF_VERTEX_2D,					//�o�^�ݒ�
		D3DPOOL_MANAGED,				//�������Ǘ����@
		&mVtx,							//���_�o�b�t�@�Ǘ��C���^�[�t�F�C�X
		NULL
	)
	))
	{
		return E_FAIL;
	}

	//�o�b�t�@�o�^�J�n
	mVtx->Lock(0, 0, (void**)&pVtx, 0);

	//���W�ݒ�
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

	//�e�N�X�`���ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.f, 0.f);
	pVtx[1].tex = D3DXVECTOR2(1.f, 0.f);
	pVtx[2].tex = D3DXVECTOR2(0.f, 1.f);
	pVtx[3].tex = D3DXVECTOR2(1.f, 1.f);

	//���_�F�ݒ�
	pVtx[0].color =
	pVtx[1].color =
	pVtx[2].color =
	pVtx[3].color = mColor;

	//rhw�ݒ�
	pVtx[0].rhw =
	pVtx[1].rhw =
	pVtx[2].rhw =
	pVtx[3].rhw = 1.f;

	//�o�^�I��
	mVtx->Unlock();

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Outlaw2D::uninit
//�Ԃ�l	: 
//����		: �I��
//////////////////////////////////////////////////////////////////////////////
void	Outlaw2D::uninit	( void )
{
	//�e�N�X�`���o�b�t�@���
	if(mTex != NULL)
	{
		mTex->Release();
		mTex = NULL;
	}

	//���_�o�b�t�@���
	if(mVtx != NULL)
	{
		mVtx->Release();
		mVtx = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Outlaw2D::update
//�Ԃ�l	: 
//����		: �X�V
//////////////////////////////////////////////////////////////////////////////
void	Outlaw2D::update	( void )
{
	//�ϐ��錾
	VERTEX2D	*pVtx;

	//�o�b�t�@�o�^�J�n
	mVtx->Lock(0, 0, (void**)&pVtx, 0);

	//���W�ݒ�
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

	//���_�F�ݒ�
	pVtx[0].color =
		pVtx[1].color =
		pVtx[2].color =
		pVtx[3].color = mColor;

	//�o�^�I��
	mVtx->Unlock();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Outlaw2D::draw
//�Ԃ�l	: 
//����		: �`��
//////////////////////////////////////////////////////////////////////////////
void Outlaw2D::draw	( void )
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9	device;		//�f�o�C�X���

	//�f�o�C�X���擾
	device = Renderer::getDevice();

	//�X�g���[���쐬
	device->SetStreamSource(0, mVtx, 0, sizeof(VERTEX2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	device->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	device->SetTexture(0, mTex);

	//�|���S���̕`��
	device->DrawPrimitive
	(
		D3DPT_TRIANGLESTRIP,	//�|���S���̎��
		0,						//�I�t�Z�b�g(���_��)
		NUM_POLYGON				//�|���S���̐�
	);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Outlaw2D::setAll
//�Ԃ�l	: 
//����		: �S���ݒ�
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
//�֐���	: Outlaw2D::loadTex
//�Ԃ�l	: 
//����		: �e�N�X�`���ǂݍ���
//////////////////////////////////////////////////////////////////////////////
void	Outlaw2D::loadTex	( const char *fileName )
{
	//�ϑ��錾
	LPDIRECT3DDEVICE9 device = Renderer::getDevice();

	//�e�N�X�`���̓ǂݍ���
	if (FAILED(D3DXCreateTextureFromFile(device, fileName, &mTex)))
	{
		char message[256];
		sprintf(message, "%s���ǂݍ��߂܂���ł���", fileName);

		MessageBox(NULL, message, "�e�N�X�`���ǂݍ��݃G���[", MB_OK);
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Outlaw2D::bindTex
//�Ԃ�l	: 
//����		: �e�N�X�`���R�s�[
//////////////////////////////////////////////////////////////////////////////
void	Outlaw2D::bindTex	( LPDIRECT3DTEXTURE9 texBuf )
{
	mTex = texBuf;
}