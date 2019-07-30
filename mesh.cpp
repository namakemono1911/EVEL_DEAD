/*****************************************************************************
mesh.h
Aythor	: ���@��
Data	: 2017_05_18
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "scene.h"
#include "mesh.h"
#include "renderer.h"

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Mesh::init
//�Ԃ�l	: 
//����		: ������
//////////////////////////////////////////////////////////////////////////////
HRESULT	Mesh::init	(void)
{
	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Mesh::uninit
//�Ԃ�l	: 
//����		: �I��
//////////////////////////////////////////////////////////////////////////////
void	Mesh::uninit	( void )
{
	//���_�o�b�t�@���
	if (mVtxBuf != NULL)
	{
		mVtxBuf->Release();
		mVtxBuf = NULL;
	}

	//�e�N�X�`���o�b�t�@���
	if (mTex != NULL)
	{
		mTex->Release();
		mTex = NULL;
	}

	//Scene���
	release();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Mesh::update
//�Ԃ�l	: 
//����		: �X�V
//////////////////////////////////////////////////////////////////////////////
void	Mesh::update	( void )
{
	//�ϐ��錾
	VERTEX3D	*pVtx;		//���_���|�C���^

	for(UINT i = 0; i < mNumVtx; i++)
	{
		mVtxBuf->Lock(0, 0, (void**)&pVtx, 0);

		//���_�F
		pVtx[0].color = mColor;

		mVtxBuf->Unlock();
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Mesh::draw
//�Ԃ�l	: 
//����		: �`��
//////////////////////////////////////////////////////////////////////////////
void	Mesh::draw	( void )
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9	device = Renderer::getDevice();

	//�X�g���[���쐬
	device->SetStreamSource(0, mVtxBuf, 0, sizeof(VERTEX3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	device->SetFVF(FVF_VERTEX_3D);

	//�T���v���[�X�e�[�g�̐ݒ�
	device->SetIndices(mIdxBuf);

	//�e�N�X�`���Z�b�g
	device->SetTexture(0, mTex);

	//���[���h�}�g���b�N�X�ݒ�
	setMtx(device);
	
	//�|���S���̕`��
	device->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,		//�`����@
		0,							//�ŏ��̒��_�C���f�b�N�X�܂ł̃I�t�Z�b�g
		0,							//�ŏ��̒��_�C���f�b�N�X
		mNumVtx,					//���_��
		0,							//�X�^�[�g�C���f�b�N�X
		mNumPrim);					//�v���~�e�B�u��
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Mesh::setMtx
//�Ԃ�l	: 
//����		: ���[���h�s��ݒ�
//////////////////////////////////////////////////////////////////////////////
void	Mesh::setMtx	( LPDIRECT3DDEVICE9 device )
{
	//�ϐ��錾
	D3DXMATRIX	world;		//���[���h�s��
	D3DXMATRIX	move;		//���s�ړ��s��
	D3DXMATRIX	rot;		//��]�s��
	D3DXVECTOR3	pos;		//�ړ����W

	//�s�񏉊���
	D3DXMatrixIdentity(&world);

	//���s�ړ�
	D3DXMatrixTranslation(&move,
		mTransform.pos.x,
		mTransform.pos.y,
		mTransform.pos.z);

	//��]
	D3DXMatrixRotationYawPitchRoll(&rot,
		mTransform.rot.x,
		mTransform.rot.y,
		mTransform.rot.z);		//��]�s��

	//�s�񍇐�
	world *= rot;		//��]
	world *= move;		//���s�ړ�

	device->SetTransform(D3DTS_WORLD, &world);		//�s����f�o�C�X�ɐݒ�
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Mesh::makeVtxBuf
//�Ԃ�l	: �����������_�o�b�t�@
//����		: ���_�o�b�t�@�쐬
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3DVERTEXBUFFER9	Mesh::makeVtxBuf	(const UINT numVtx)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9	device = Renderer::getDevice();

	mNumVtx = numVtx;

	//=============================
	// ���_�o�b�t�@�쐬
	//=============================
	if (FAILED(device->CreateVertexBuffer
	(
		sizeof(VERTEX3D) * mNumVtx,				//���_�o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,						//���_�o�b�t�@�̎g�p���@
		FVF_VERTEX_3D,							//�Ȃ񂩐ݒ�
		D3DPOOL_MANAGED,						//�������Ǘ����@
		&mVtxBuf,								//���_�o�b�t�@�Ǘ��C���^�[�t�F�C�X
		NULL)))
	{
		return NULL;
	}

	return mVtxBuf;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Mesh::makeIdxBuf
//�Ԃ�l	: ���������C���f�b�N�X�o�b�t�@
//����		: �C���f�b�N�X�o�b�t�@�쐬
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3DINDEXBUFFER9	Mesh::makeIdxBuf	(const UINT numIdx)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9	device = Renderer::getDevice();

	//=============================
	// �C���f�b�N�X�쐬
	//=============================
	if(FAILED(device->CreateIndexBuffer(
		sizeof(WORD) *  numIdx,	//�K�v�ȃC���f�b�N�X�T�C�Y
		D3DUSAGE_WRITEONLY,		//�g�p�p�r�t���O
		D3DFMT_INDEX16,			//�C���f�b�N�X�̃t�H�[�}�b�g
		D3DPOOL_MANAGED,		//�������̊Ǘ����@�i���C�����[�h�j
		&mIdxBuf,				//�C���f�b�N�X�o�b�t�@�C���^�[�t�F�C�X
		NULL)))
	{
		return NULL;
	}

	return mIdxBuf;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Mesh::loadTex
//�Ԃ�l	: 
//����		: �w�肳�ꂽ�e�N�X�`���ǂݍ���
//////////////////////////////////////////////////////////////////////////////
void Mesh::loadTex(const char * texName)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 device = Renderer::getDevice();

	//�e�N�X�`���̓ǂݍ���
	if (FAILED(D3DXCreateTextureFromFile(device, texName, &mTex)))
	{
		MessageBox(NULL, "�G���[", "field�G���[", MB_OK);
		return;
	}
}
