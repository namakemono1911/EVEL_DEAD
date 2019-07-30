/*****************************************************************************
player.cpp
Aythor	: ���@��
Data	: 2017_06_15
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "manager.h"
#include "sceneModel.h"
#include "mesh.h"
#include "collision.h"
#include "collisionBox.h"
#include "collisionBox.h"
#include "meshField.h"
#include "fade.h"
#include "zombie.h"
#include "playerState.h"
#include "player.h"
#include "mode.h"
#include "reticle.h"
#include "coin.h"
#include "weapon.h"
#include "weaponFactory.h"
#include "bullet.h"
#include "playerNeutral.h"

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Player::create
//�Ԃ�l	: ���g�̃|�C���^
//����		: ����
//////////////////////////////////////////////////////////////////////////////
Player *Player::create(Player *player)
{
	Player *p = player;

	p->init();

	return p;
}

/*#################################################################################################################
PlayerTitle class
###################################################################################################################
*/
//////////////////////////////////////////////////////////////////////////////
//�֐���	: PlayerTitle::init
//�Ԃ�l	: 
//����		: �^�C�g����ʂł̑��쏉����
//////////////////////////////////////////////////////////////////////////////
HRESULT PlayerTitle::init(void)
{
	mFade = Manager::getFade();
	mFade->fadeIn(60);

	mStart = false;
	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: PlayerTitle::uninit
//�Ԃ�l	: 
//����		: �^�C�g����ʂł̑���
//////////////////////////////////////////////////////////////////////////////
void PlayerTitle::uninit(void)
{

}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: PlayerTitle::update
//�Ԃ�l	: 
//����		: �^�C�g����ʂł̍X�V
//////////////////////////////////////////////////////////////////////////////
void PlayerTitle::update(void)
{
	opeTitle();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: PlayerTitle::opeTitle
//�Ԃ�l	: 
//����		: �^�C�g����ʂł̑���
//////////////////////////////////////////////////////////////////////////////
void PlayerTitle::opeTitle(void)
{
	//�L�[����
	InputKeyboard *key = Manager::getKeyboard();
	
	if (key->getTrigger(DIK_SPACE))
	{
		if (mStart == false)
		{
			mFade->fadeOut(60);
			mStart = true;
		}
	}

	if (mFade->getFadeMode() == Fade::FADE_NONE && mStart == true)
		Manager::getMode()->ChengeMode();
}

/*#################################################################################################################
PlayerGame class
###################################################################################################################
*/
//////////////////////////////////////////////////////////////////////////////
//�萔��`
//////////////////////////////////////////////////////////////////////////////
#define MOVE	(10.f);

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Player::init
//�Ԃ�l	: 
//����		: �Q�[�����̏�����
//////////////////////////////////////////////////////////////////////////////
HRESULT PlayerGame::init(void)
{
	mFade = Manager::getFade();
	mFade->fadeIn(60);

	mSens = 0.004f;
	mHeight = 20.f;
	mTransform.pos = Dvec3(0.f, mHeight, -20.f);
	mLen = 5.f;
	mMove = MOVE;
	mFadeStart = false;
	mWeapon = WeaponFactory::create(GOVERMENT, Dvec3(-2.f, -1.f, -3.f));
	setChild(mWeapon);

	setState(new PlayerNeutral(this));

	mUpButton = DIK_W;
	mDownButton = DIK_S;
	mRightButton = DIK_D;
	mLeftButton = DIK_A;
	mDebugButton = DIK_TAB;
	mCamera = (Camera*)Scene::getTypeList(Scene::CAMERA).front();

	Player::init();

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Player::uninit
//�Ԃ�l	: 
//����		: �Q�[���I�����̏���
//////////////////////////////////////////////////////////////////////////////
void PlayerGame::uninit(void)
{
	delete mState;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Player::update
//�Ԃ�l	: 
//����		: �Q�[�����̍X�V
//////////////////////////////////////////////////////////////////////////////
void PlayerGame::update(void)
{
	mState->update();
	hitCheckEnemy();

	//���̓f�o�C�X���
	InputKeyboard	*key = Manager::getKeyboard();

	if (key->getTrigger(DIK_SPACE))
	{
		if (mFadeStart == false)
		{
			mFade->fadeOut(60);
			mFadeStart = true;
		}
	}

	if (mFade->getFadeMode() == Fade::FADE_NONE && mFadeStart == true)
		Manager::getMode()->ChengeMode();

	mCamera->setPosEye(mTransform.pos);
}

bool PlayerGame::isPushedUp(void)
{
	return Manager::getKeyboard()->getPress(mUpButton);
}

bool PlayerGame::isPushedDown(void)
{
	return Manager::getKeyboard()->getPress(mDownButton);
}

bool PlayerGame::isPushedRight(void)
{
	return Manager::getKeyboard()->getPress(mRightButton);
}

bool PlayerGame::isPushedLeft(void)
{
	return Manager::getKeyboard()->getPress(mLeftButton);
}

bool PlayerGame::isPushedDebug(void)
{
	return Manager::getKeyboard()->getTrigger(mDebugButton);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Player::setState
//�Ԃ�l	: 
//����		: �X�e�[�g�ݒ�
//////////////////////////////////////////////////////////////////////////////
void PlayerGame::setState(PlayerState * p)
{
	if (mState != NULL)
		delete mState;

	mState = p;
	mState->init();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Player::opeCamera
//�Ԃ�l	: 
//����		: �J��������
//////////////////////////////////////////////////////////////////////////////
void PlayerGame::opeCamera(void)
{
	//���̓f�o�C�X���
	InputMouse		*mouse = Manager::getMouse();

	//���_����
	vec2 cameraAngle = mCamera->getAngle();
	cameraAngle.x += fmod(mouse->getMoving().x * mSens, PI);
	cameraAngle.y += -mouse->getMoving().y * mSens;

	if (cameraAngle.y >= PI * 0.3f)			//�p
		cameraAngle.y = PI * 0.3f;

	if (cameraAngle.y <= -PI * 0.3f)		//��p
		cameraAngle.y = -PI * 0.3f;

	mCamera->setAngle(cameraAngle);
	mTransform.rot = Dvec3(cameraAngle.x, cameraAngle.y, 0.f);

	//���ʍ��W
	vec3 eye = mCamera->getEye();
	float len = mCamera->getLen();
	vec3 at(
		len * cosf(-cameraAngle.y) * sinf(cameraAngle.x) + eye.x,
		len * sinf(-cameraAngle.y) + eye.y,
		len * cosf(-cameraAngle.y) * cosf(cameraAngle.x) + eye.z);

	mCamera->setPosAt(at);

	//�E�N���b�N
	Reticle *rtcl = mMode->getReticle();
	float fovy = mCamera->getFovy();
	if (mouse->getPress(MOUSE_RIGHT))
	{
		rtcl->setDisplay(true);
		mMove = 0.3f * MOVE;
		fovy -= 0.1f;
		if (fovy > PI / 4.f)
			mCamera->setFovy(fovy);
		else
			mCamera->setFovy(PI / 4.f);
	}
	else
	{
		rtcl->setDisplay(false);
		mMove = MOVE;
		fovy += 0.1f;
		if (fovy < PI / 3.f)
			mCamera->setFovy(fovy);
		else
			mCamera->setFovy(PI / 3.f);
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Player::hitCheckEnemy
//�Ԃ�l	: 
//����		: �Փ˔���
//////////////////////////////////////////////////////////////////////////////
void PlayerGame::hitCheckEnemy(void)
{
	//�Փ˔���
	auto enemyList = Scene::getTypeList(ZOMBIE);
	for (const auto& scene : enemyList)
	{
		if ((float)vec3::lenVector(scene->getPos() - Dvec3(mTransform.pos.x, 0, mTransform.pos.z)) <= mLen)
		{
			if (mFadeStart == false)
			{
				mFade->fadeOut(60);
				mFadeStart = true;
			}
		}
	}
}

/*#################################################################################################################
PlayerResult class
###################################################################################################################
*/
//////////////////////////////////////////////////////////////////////////////
//�֐���	: PlayerResult::init
//�Ԃ�l	: 
//����		: ������
//////////////////////////////////////////////////////////////////////////////
HRESULT PlayerResult::init(void)
{
	mFade = Manager::getFade();
	mFade->fadeIn(60);

	mNext = false;
	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: PlayerResult::uninit
//�Ԃ�l	: 
//����		: �I��
//////////////////////////////////////////////////////////////////////////////
void PlayerResult::uninit(void)
{
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: PlayerResult::update
//�Ԃ�l	: 
//����		: �X�V
//////////////////////////////////////////////////////////////////////////////
void PlayerResult::update(void)
{
	//�L�[����
	InputKeyboard *key = Manager::getKeyboard();

	if (key->getTrigger(DIK_SPACE))
	{
		if (mNext == false)
		{
			mFade->fadeOut(60);
			mNext = true;
		}
	}

	if (mFade->getFadeMode() == Fade::FADE_NONE && mNext == true)
		Manager::getMode()->ChengeMode();
}
