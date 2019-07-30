/*****************************************************************************
���b�V���h�[���`��
Aythor	: ���@��
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
//�萔��`
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//�\���̒�`
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//�ÓI�����o�ϐ�������
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9	Sky::mTexBuf[SKY_TEX_MAX] = {NULL};
const char	*Sky::mTexName[SKY_TEX_MAX] =
{
	"data/texture/sky001.jpg",

};

//////////////////////////////////////////////////////////////////////////////
//�֐���	: initMeshDome
//�Ԃ�l	: 
//����		: �|���S��������
//////////////////////////////////////////////////////////////////////////////
HRESULT Sky::init( void )
{
	//�ϐ��錾
	UINT	numPtv;	//�K�v�Ȗʂ̐�

	//�K�v�Ȗʂ̐��v�Z
	numPtv = (int)mNumTyle.y + ((int)mNumTyle.y - 1) * 4;
	numPtv += ((int)mNumTyle.x - 1) * ((int)mNumTyle.y + 1) * 2;

	//�Z�b�g
	setNumPrim(numPtv);

	//�e�N���X�Ɋe��ݒ�
	setAll(mPos, mRot, mColor, D3DXVECTOR2(0.f, 0.f), D3DXVECTOR2(0.f, 0.f));

	return	S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: uninitMeshDome
//�Ԃ�l	: 
//����		: �|���S���I��
//////////////////////////////////////////////////////////////////////////////
void	Sky::uninit( void )
{
	//�e�N�X�`���o�b�t�@�̉��
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
//�֐���	: updateMeshDome
//�Ԃ�l	: 
//����		: �|���S���X�V
//////////////////////////////////////////////////////////////////////////////
void	Sky::update( void )
{
	setRot(getRot() + mRot);

	Mesh::update();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: drawMeshDome
//�Ԃ�l	: 
//����		: �|���S���`��
//////////////////////////////////////////////////////////////////////////////
void Sky::draw( void )
{
	//���C�g�̉e��off
	Manager::getRenderer()->getDevice()->SetRenderState(D3DRS_LIGHTING, false);

	Mesh::draw();

	//���C�g�̉e��on
	Manager::getRenderer()->getDevice()->SetRenderState(D3DRS_LIGHTING, true);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: setMeshDome
//�Ԃ�l	: 
//����		: �t�B�[���h�ݒ�
//////////////////////////////////////////////////////////////////////////////
Sky	*Sky::create (D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR2 numTyle, D3DXCOLOR color, float len, SKY_TEX tex)
{
	//�ϐ��錾
	Sky	*sky;

	//����
	sky = new Sky;

	//������
	sky->setVal(pos, numTyle, color, rot, len, tex);
	sky->bindTexBuf(mTexBuf[tex]);
	sky->makeVtx(numTyle);
	sky->init();

	return sky;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Sky::setVal
//�Ԃ�l	: 
//����		: �ϐ��ݒ�
//////////////////////////////////////////////////////////////////////////////
void	Sky::setVal(D3DXVECTOR3 pos, D3DXVECTOR2 numTyle, D3DXCOLOR color, D3DXVECTOR3 rot, float len, SKY_TEX tex)
{
	//�ϐ����
	mPos = pos;
	mNumTyle = numTyle;
	mColor = color;
	mRot = rot;
	mLen = len;
	mTex = tex;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: makeVertexMeshDome
//�Ԃ�l	: 
//����		: �|���S���`��ʒu�ݒ�
//////////////////////////////////////////////////////////////////////////////
HRESULT	Sky::makeVtx(D3DXVECTOR2 numTyle)
{
	//�ϐ��錾
	VERTEX3D	*pVtx;		//���z�A�h���X�p�|�C���^
	float		posY;		//�`��ʒu
	float		len;		//���a
	float		rot;		//�p�x
	int			x, y;		//x��y�̃��[�v
	int			num;		//�K�v�Ȓ��_��
	D3DXVECTOR3	fullSize;	//�t�B�[���h�S�̂̃T�C�Y
	LPDIRECT3DVERTEXBUFFER9 vtx;	//���_�o�b�t�@

	//=============================
	// �����_�K�v��
	//=============================
	num	=	(int)numTyle.x * ((int)numTyle.y + 1) + 1;

	//=============================
	// ���_�o�b�t�@�쐬
	//=============================
	if((vtx = makeVtxBuf(num)) == NULL)
	{
		return E_FAIL;
	}

	//=============================
	// ���_���o�^
	//=============================
	vtx->Lock(0, 0, (void**)&pVtx, 0);

	//�h�[���̒��_
	pVtx[0].pos		=	D3DXVECTOR3(
		0.f,
		mLen,
		0.f);

	//���_�F
	pVtx[0].color	= mColor;

	//�e�N�X�`�����W
	pVtx[0].tex		= D3DXVECTOR2(0.f, 0.f);

	//�|�C���^�ړ�
	pVtx++;

	for(y = 0; y < mNumTyle.x; y++)
	{
		//�p�x�Z�o
		rot	=	90 * ((mNumTyle.x - (y + 1)) / mNumTyle.x);

		//Y���W�m��
		posY	= mLen * sin(rot * (PI / 180));
		len		= mLen * cos(rot * (PI / 180));

		for(x = 0; x < mNumTyle.y + 1; x++)
		{
			//x,z�̊p�x
			rot	=	360 * (x / mNumTyle.y);

			//���W
			pVtx[0].pos	=	D3DXVECTOR3(
				len * cos(rot * (PI / 180)),
				posY,
				len * sin(rot * (PI / 180)));

			//���_�F
			pVtx[0].color	=	mColor;

			//�e�N�X�`�����W
			pVtx[0].tex		=	D3DXVECTOR2(
				(1.f / mNumTyle.y) * x,
				(1.f / mNumTyle.x) * (y + 1));

			//�|�C���^�ړ�
			pVtx++;
		}
	}
				
	vtx->Unlock();

	//�o�b�t�@�o�C���h
	bindVtxBuf(vtx);

	//=============================
	// �C���f�b�N�X�쐬
	//=============================
	makeIdx();

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: makeIndexBuffer
//�Ԃ�l	: 
//����		: �|���S���`��ʒu�ݒ�
//////////////////////////////////////////////////////////////////////////////
HRESULT	Sky::makeIdx(void)
{
	//�ϐ��錾
	WORD		*pIdx;	//�C���f�b�N�X�ԍ�
	int			x, y;	//x��z��loop
	int			num;	//�K�v�ȃC���f�b�N�X��
	LPDIRECT3DINDEXBUFFER9	idx;	//�C���f�b�N�X�o�b�t�@
	
	//=============================
	// �����_�K�v��
	//=============================
	num	=	5 * (int)mNumTyle.y;
	num	+=	(int)(mNumTyle.y + 1) * ((int)mNumTyle.x - 1) * 2;

	//=============================
	// �C���f�b�N�X�쐬
	//=============================
	idx = makeIdxBuf(num);

	//=============================
	// �C���f�b�N�X�o�^
	//=============================
	idx->Lock(0, 0, (void**)&pIdx, 0);

	//�h�[����1�ԏ�
	for(int k = 0; k < mNumTyle.y; k++)
	{
		pIdx[0]	=	0;
		pIdx[1]	=	(WORD)k + 1 + (WORD)k % 2;
		pIdx[2]	=	(WORD)k + 2 - (WORD)k % 2;
		pIdx	+=	3;

		//�k�ރ|���S��
		if(k < mNumTyle.y - 1)
		{
			pIdx[3]	=	pIdx[2];
			pIdx[0]	=	0;
			pIdx	+=	2;
		}
	}

	//�������牺
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

	//�o�b�t�@�o�C���h
	bindIdxBuf(idx);

	return	S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Sky::loadTex
//�Ԃ�l	: 
//����		: �e�N�X�`���ǂݍ���
//////////////////////////////////////////////////////////////////////////////
HRESULT	Sky::loadTex(void)
{
	for(UINT i = 0; i < SKY_TEX_MAX; i++)
	{
		//�e�N�X�`���̓ǂݍ���
		if(FAILED(D3DXCreateTextureFromFile(Renderer::getDevice(), mTexName[i], &mTexBuf[i])))
		{
			MessageBox(NULL, "Sky", "�G���[", MB_OK);
			return	E_FAIL;
		}
	}

	return S_OK;
}