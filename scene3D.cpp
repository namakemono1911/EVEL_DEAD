/*****************************************************************************
scene3D.cpp
Aythor	: ���@��
Data	: 2017_04_20
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "scene.h"
#include "scene3DState.h"
#include "scene3D.h"
#include "renderer.h"
#include "camera.h"
#include "scene3DTextureAnimation.h"
#include "scene3DBillboard.h"

//////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Scene3D::init
//�Ԃ�l	: 
//����		: ������
//////////////////////////////////////////////////////////////////////////////
HRESULT	Scene3D::init	(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9	device = Renderer::getDevice();

	//�ϐ�������
	mMyName = "3Dpolygon";
	mAngle = atan2f(mTransform.size.y, mTransform.size.x);
	mRot = 0.f;
	mLen = 5.f;
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

	//���_���o�^
	setVertexBuffer();

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Scene3D::uninit
//�Ԃ�l	: 
//����		: �I��
//////////////////////////////////////////////////////////////////////////////
void	Scene3D::uninit	( void )
{
	//���_�o�b�t�@���
	if(mVtx != NULL)
	{
		mVtx->Release();
		mVtx = NULL;
	}

	for (auto& state : mStateList)
		delete state;

	//�����[�X
	release();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Scene3D::update
//�Ԃ�l	: 
//����		: �X�V
//////////////////////////////////////////////////////////////////////////////
void	Scene3D::update	( void )
{
	for (auto& state : mStateList)
		state->update();

	//���_���o�^
	setVertexBuffer();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Scene3D::draw
//�Ԃ�l	: 
//����		: �`��
//////////////////////////////////////////////////////////////////////////////
void	Scene3D::draw	( void )
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
	device->SetTexture(0, mTex);

	//�s��ݒ�
	device->SetTransform(D3DTS_WORLD, &mMatrix);

	//�|���S���̕`��
	device->DrawPrimitive
	(
		D3DPT_TRIANGLESTRIP,	//�|���S���̎��
		0,						//�I�t�Z�b�g(���_��)
		NUM_POLYGON				//�|���S���̐�
	);

	//���C�g�̉e��on
	device->SetRenderState(D3DRS_LIGHTING, true);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: create
//�Ԃ�l	: 
//����		: ����
//////////////////////////////////////////////////////////////////////////////
Scene3D * Scene3D::create(Dvec3 pos, Dvec3 rot, Dvec3 size, LPDIRECT3DTEXTURE9 texture, Dvec2 texPos, Dvec2 texSize, Dcolor color)
{
	auto polygon = new Scene3D;
	polygon->mTransform = Transform(pos, rot, Dvec3(1, 1, 1));
	polygon->mTexPos = texPos;
	polygon->mTexSize = texSize;
	polygon->mTex = texture;
	polygon->setRect(size);
	polygon->init();

	return polygon;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: create
//�Ԃ�l	: 
//����		: ����
//////////////////////////////////////////////////////////////////////////////
Scene3D * Scene3D::create(Dvec3 topLeft, Dvec3 topRight, Dvec3 bottomLeft, Dvec3 bottomRight, Dvec3 pos, Dvec3 rot, Dvec3 size, LPDIRECT3DTEXTURE9 texture, Dvec2 texPos, Dvec2 texSize, Dcolor color)
{
	auto polygon = new Scene3D;
	polygon->mRectPos[0] = topLeft;
	polygon->mRectPos[1] = topRight;
	polygon->mRectPos[2] = bottomLeft;
	polygon->mRectPos[3] = bottomRight;
	polygon->mTexPos = texPos;
	polygon->mTexSize = texSize;
	polygon->mTex = texture;
	polygon->init();

	return polygon;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: setRect
//�Ԃ�l	: 
//����		: ��`�ݒ�
//////////////////////////////////////////////////////////////////////////////
void Scene3D::setRect(Dvec3 size)
{
	Dvec3 line = size * 0.5f;
	mRectPos[0] = Dvec3(-line.x, line.y, 0.f);
	mRectPos[1] = Dvec3(line.x, line.y, 0.f);
	mRectPos[2] = Dvec3(-line.x, -line.y, 0.f);
	mRectPos[3] = Dvec3(line.x, -line.y, 0.f);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: setTextureAnimation
//�Ԃ�l	: 
//����		: �e�N�X�`���A�j���[�V�����ݒ�
//////////////////////////////////////////////////////////////////////////////
void Scene3D::setTextureAnimation(int numVertical, int numHorizonal, int interval)
{
	mStateList.push_back(Scene3DTextureAnimation::create(this, numVertical, numHorizonal, interval));
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: setBillboard
//�Ԃ�l	: 
//����		: �r���{�[�h�ݒ�
//////////////////////////////////////////////////////////////////////////////
void Scene3D::setBillboard()
{
	mStateList.push_back(Scene3DBillboard::create(this));
}

void Scene3D::setVertexBuffer()
{
	VERTEX3D	*vtx;
	mVtx->Lock(0, 0, (void**)&vtx, 0);

	//���W�ݒ�
	vtx[0].pos = mRectPos[0];
	vtx[1].pos = mRectPos[1];
	vtx[2].pos = mRectPos[2];
	vtx[3].pos = mRectPos[3];

	//�e�N�X�`���ݒ�
	vtx[0].tex = mTexPos;
	vtx[1].tex = D3DXVECTOR2(mTexPos.x + mTexSize.x, mTexPos.y);
	vtx[2].tex = D3DXVECTOR2(mTexPos.x, mTexPos.y + mTexSize.y);
	vtx[3].tex = mTexPos + mTexSize;

	//���_�F�ݒ�
	vtx[0].color =
		vtx[1].color =
		vtx[2].color =
		vtx[3].color = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�@���x�N�g���ݒ�
	vtx[0].nor =
		vtx[1].nor =
		vtx[2].nor =
		vtx[3].nor = vec3::DcrossProduct(mRectPos[1], mRectPos[2], mRectPos[0]);

	mVtx->Unlock();
}
