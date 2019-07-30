/*****************************************************************************
collisionBall.cpp
Aythor	: ���@��
Data	: 2017_07_13
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include <list>
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "collisionBall.h"
#include "load.h"
#include "vec.h"
#include "sceneModel.h"

//////////////////////////////////////////////////////////////////////////////
//�ÓI�����o�ϐ�������
//////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
LPDIRECT3DTEXTURE9	CollisionBall::mTexBuf[2] = {NULL};
#endif // _DEBUG

//////////////////////////////////////////////////////////////////////////////
//�֐���	: CollisionBall::init()
//�Ԃ�l	: 
//����		: ����������
//////////////////////////////////////////////////////////////////////////////
HRESULT CollisionBall::init(void)
{
#ifdef _DEBUG
if (FAILED(
		D3DXCreateSphere(
			Renderer::getDevice(),			// �`���̃f�o�C�X
			mLen,							// ���a�B0.0f�ł�����OK�B�}�C�i�X��NG
			32,								// �X���C�X�̐��B���₷�Ƃ��ꂢ�ȋ��ɂȂ�͂�
			18,								// �X�^�b�N���B���₷�Ƃ��ꂢ�ȋ��ɂȂ�͂�
			&mMesh,							// �o�͂��郁�b�V��
			NULL)))							// ���܂�g��Ȃ��炵�����NULL�ɂ��Ƃ���
		return E_FAIL;

	mMat.Diffuse = DEFAULT_COLOR;
	mMat.Ambient = DEFAULT_COLOR;
	mMat.Specular = Dcolor(0, 0, 0, 0);
	mMat.Emissive = Dcolor(0, 0, 0, 0);
	mMat.Power = 0.f;
#endif // _DEBUG

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: CollisionBall::uninit()
//�Ԃ�l	: 
//����		: �I��
//////////////////////////////////////////////////////////////////////////////
void CollisionBall::uninit(void)
{
#ifdef _DEBUG
if (mMesh != NULL)
	{
		mMesh->Release();
		mMesh = NULL;
	}
#endif // _DEBUG
	
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: CollisionBall::update()
//�Ԃ�l	: 
//����		: �X�V
//////////////////////////////////////////////////////////////////////////////
void CollisionBall::update(void)
{
	auto world = mPearents->getMatrix();
	auto parentPos = Dvec3(world._41, world._42, world._43);
	auto axisX = Dvec3(world._11, world._12, world._13) * mRelativePos.x;
	auto axisY = Dvec3(world._21, world._22, world._23) * mRelativePos.y;
	auto axisZ = Dvec3(world._31, world._32, world._33) * mRelativePos.z;
	mPos = axisX + axisY + axisZ + parentPos;

#ifdef _DEBUG
D3DXCreateSphere(
		Renderer::getDevice(),			// �`���̃f�o�C�X
		mLen,							// ���a�B0.0f�ł�����OK�B�}�C�i�X��NG
		32,								// �X���C�X�̐��B���₷�Ƃ��ꂢ�ȋ��ɂȂ�͂�
		18,								// �X�^�b�N���B���₷�Ƃ��ꂢ�ȋ��ɂȂ�͂�
		&mMesh,							// �o�͂��郁�b�V��
		NULL);							// ���܂�g��Ȃ��炵�����NULL�ɂ��Ƃ���
#endif // _DEBUG
}

#ifdef _DEBUG
//////////////////////////////////////////////////////////////////////////////
//�֐���	: CollisionBall::draw()
//�Ԃ�l	: 
//����		: �`��
//////////////////////////////////////////////////////////////////////////////
void CollisionBall::draw(void)
{
	LPDIRECT3DDEVICE9 device = Renderer::getDevice();

	//���C�g�̉e��off
	device->SetRenderState(D3DRS_LIGHTING, false);

	//�s��ݒ�
	setMtx();

	//�e�N�X�`���ݒ�
	device->SetMaterial(&mMat);

	mMesh->DrawSubset(0);

	//���C�g�̉e��on
	device->SetRenderState(D3DRS_LIGHTING, true);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: CollisionBall::loadTex()
//�Ԃ�l	: 
//����		: �`��
//////////////////////////////////////////////////////////////////////////////
void CollisionBall::loadTex(void)
{
	//�e�N�X�`���̓ǂݍ���
	char *texName[2] = {
		"data/texture/ball000.png",
		"data/texture/ball001.png"
	};

	for (int i = 0; i < 2; i++)
	{
		if (FAILED(D3DXCreateTextureFromFile(Renderer::getDevice(), texName[i], &mTexBuf[i])))
		{
			char message[255];
			sprintf(message, "%s���ǂݍ��߂܂���ł���", texName[i]);

			MessageBox(NULL, message, "�e�N�X�`���ǂݍ��݃G���[", MB_OK);
		}
	}
}
#endif // _DEBUG

void CollisionBall::assignmentTarget(FILE * fp)
{
	string order = "\0";
	while ((order = Load::findWord(fp)) != "}")
	{
		if (order == "pos")
			Load::operatorSelectFloat3(fp, mRelativePos);

		if (order == "len")
			Load::operatorSelectFloat(fp, &mLen);
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: CollisionBall::create()
//�Ԃ�l	: 
//����		: �`��
//////////////////////////////////////////////////////////////////////////////
CollisionBall * CollisionBall::create(Scene* pearent, Dvec3 pos, float len)
{
	CollisionBall *ball;

	ball = new CollisionBall;

	ball->mPearents = pearent;
	ball->mLen = len;
	ball->mRelativePos = pos;
	ball->mType = BALL;
	ball->init();

	return ball;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: CollisionBall::hitByPoint()
//�Ԃ�l	: 
//����		: ���Ɠ_�̔���
//////////////////////////////////////////////////////////////////////////////
bool CollisionBall::hitByPoint(const Dvec3& pos)
{
	if (mLen <= (float)vec3::lenVector(pos - mPos))
		return true;
	return false;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: CollisionBall::hitByRay()
//�Ԃ�l	: 
//����		: ���Ɛ��̔���
//////////////////////////////////////////////////////////////////////////////
bool CollisionBall::hitByRay(Dvec3 *outCrossPos, Dvec3 *outAxis, Dvec3 pos, Dvec3 ray)
{
	Dvec3 normalRay;
	D3DXVec3Normalize(&normalRay, &Dvec3(ray - pos));
	auto dot = vec3::innerProduct(normalRay, mPos - pos);
	
	if (dot < 0)
	{
		if (D3DXVec3Length(&Dvec3(mPos - pos)) < mLen)
		{
			if (outCrossPos != NULL)
				*outCrossPos = pos + ray;

			if (outAxis != NULL)
				D3DXVec3Normalize(outAxis, &Dvec3(mPos - pos));

			return true;
		}
	}
	
	if (dot > D3DXVec3Length(&Dvec3(ray - pos)))
	{
		if (D3DXVec3Length(&Dvec3(ray - pos)) < mLen)
		{
			if (outCrossPos != NULL)
				*outCrossPos = pos;

			if (outAxis != NULL)
				D3DXVec3Normalize(outAxis, &Dvec3(mPos - pos));

			return true;
		}
	}
	else
	{
		auto cross = vec3::DcrossProduct(normalRay, mPos - pos);

		if (D3DXVec3Length(&cross) < mLen)
		{
			if (outCrossPos != NULL)
			{
				if (outCrossPos != NULL)
					*outCrossPos = cross;
				if (outAxis != NULL)
					D3DXVec3Normalize(outAxis, &Dvec3(cross - mPos));
			}
			SceneModel::create("box.x", cross * mLen + mPos);

			return true;
		}
	}

	if (outCrossPos != NULL)
		*outCrossPos = Dvec3(0, 0, 0);
	if (outAxis != NULL)
		*outAxis = Dvec3(0, 0, 0);

	return false;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: CollisionBall::create()
//�Ԃ�l	: 
//����		: �`��
//////////////////////////////////////////////////////////////////////////////
void CollisionBall::setMtx(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9	device;		//�f�o�C�X���
	D3DXMATRIX	world;		//���[���h�s��
	D3DXMATRIX	move;		//���s�ړ��s��

	//�f�o�C�X�擾
	device = Renderer::getDevice();

	//�s�񏉊���
	D3DXMatrixIdentity(&world);

	//���s�ړ�
	D3DXMatrixTranslation(&move,
		mPos.x,
		mPos.y,
		mPos.z);

	//�s�񍇐�
	world *= move;		//���s�ړ�

	device->SetTransform(D3DTS_WORLD, &world);		//�s����f�o�C�X�ɐݒ�
}
