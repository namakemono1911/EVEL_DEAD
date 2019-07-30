/*****************************************************************************
sceneGrid.cpp
Aythor	: ���@��
Data	: 2017_07_26
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "manager.h"
#include "sceneGrid.h"

//////////////////////////////////////////////////////////////////////////////
//�萔��`
//////////////////////////////////////////////////////////////////////////////
#define NUM_GRIT	(11)		//�O���b�g��

//////////////////////////////////////////////////////////////////////////////
//�֐���	: SceneGrid::init
//�Ԃ�l	: 
//����		: ������
//////////////////////////////////////////////////////////////////////////////
HRESULT SceneGrid::init(void)
{

	//�ϐ��錾
	LPDIRECT3DDEVICE9	device = Renderer::getDevice();

	//�ϐ�������
	mMyName = "grid";
	setObjType(NONE);

	//=============================
	// ���_�o�b�t�@�쐬
	//=============================
	if (FAILED(device->CreateVertexBuffer
	(sizeof(VERTEX3D) * NUM_VERTEX,			//���_�o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,						//���_�o�b�t�@�̎g�p���@
		FVF_VERTEX_3D,							//�Ȃ񂩐ݒ�
		D3DPOOL_MANAGED,						//�������Ǘ����@
		&mVtx,									//���_�o�b�t�@�Ǘ��C���^�[�t�F�C�X
		NULL)))
		return E_FAIL;

	VERTEX3D	*vtx;
	Dvec3	center = mTransform.size * 0.5f;
	mVtx->Lock(0, 0, (void**)&vtx, 0);

	//���W�ݒ�
	vtx[0].pos = mStartPos;
	vtx[1].pos = mEndPos;

	//�e�N�X�`���ݒ�
	vtx[0].tex = Dvec2(0, 0);
	vtx[1].tex = Dvec2(0, 0);

	//���_�F�ݒ�
	vtx[0].color =
	vtx[1].color = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�@���x�N�g���ݒ�
	vtx[0].nor =
	vtx[1].nor = Dvec3(-1, 0, 0);

	mVtx->Unlock();

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: SceneGrid::uninit
//�Ԃ�l	: 
//����		: ������
//////////////////////////////////////////////////////////////////////////////
void SceneGrid::uninit(void)
{
	if (mVtx != NULL)
	{
		mVtx->Release();
		mVtx = NULL;
	}

	release();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: SceneGrid::update
//�Ԃ�l	: 
//����		: ������
//////////////////////////////////////////////////////////////////////////////
void SceneGrid::update(void)
{
	VERTEX3D	*vtx;
	mVtx->Lock(0, 0, (void**)&vtx, 0);
	
	vtx[0].pos = mStartPos;
	vtx[1].pos = mEndPos;

	mVtx->Unlock();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: SceneGrid::draw
//�Ԃ�l	: 
//����		: ������
//////////////////////////////////////////////////////////////////////////////
void SceneGrid::draw(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9	device = Renderer::getDevice();

	//�X�g���[���쐬
	device->SetStreamSource(0, mVtx, 0, sizeof(VERTEX3D));

	//���C�g�̉e��off
	device->SetRenderState(D3DRS_LIGHTING, false);

	//���_�t�H�[�}�b�g�̐ݒ�
	device->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	device->SetTexture(0, NULL);

	//�s��ݒ�
	device->SetTransform(D3DTS_WORLD, &mMatrix);

	//�|���S���̕`��
	device->DrawPrimitive
	(
		D3DPT_LINELIST,	//�|���S���̎��
		0,						//�I�t�Z�b�g(���_��)
		1				//�|���S���̐�
	);

	//���C�g�̉e��on
	device->SetRenderState(D3DRS_LIGHTING, true);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: SceneGrid::create
//�Ԃ�l	: 
//����		: ����
//////////////////////////////////////////////////////////////////////////////
SceneGrid * SceneGrid::create(Dvec3 startPos, Dvec3 endPos)
{
	SceneGrid *grit = new SceneGrid;
	grit->mStartPos = startPos;
	grit->mEndPos = endPos;
	grit->init();

	return grit;
}
