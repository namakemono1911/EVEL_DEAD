/*****************************************************************************
player.cpp
Aythor	: 上野　匠
Data	: 2017_06_15
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//ファイルインクルード
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
//関数名	: Player::create
//返り値	: 自身のポインタ
//説明		: 生成
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
//関数名	: PlayerTitle::init
//返り値	: 
//説明		: タイトル画面での操作初期化
//////////////////////////////////////////////////////////////////////////////
HRESULT PlayerTitle::init(void)
{
	mFade = Manager::getFade();
	mFade->fadeIn(60);

	mStart = false;
	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: PlayerTitle::uninit
//返り値	: 
//説明		: タイトル画面での操作
//////////////////////////////////////////////////////////////////////////////
void PlayerTitle::uninit(void)
{

}

//////////////////////////////////////////////////////////////////////////////
//関数名	: PlayerTitle::update
//返り値	: 
//説明		: タイトル画面での更新
//////////////////////////////////////////////////////////////////////////////
void PlayerTitle::update(void)
{
	opeTitle();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: PlayerTitle::opeTitle
//返り値	: 
//説明		: タイトル画面での操作
//////////////////////////////////////////////////////////////////////////////
void PlayerTitle::opeTitle(void)
{
	//キー操作
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
//定数定義
//////////////////////////////////////////////////////////////////////////////
#define MOVE	(10.f);

//////////////////////////////////////////////////////////////////////////////
//関数名	: Player::init
//返り値	: 
//説明		: ゲーム中の初期化
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
//関数名	: Player::uninit
//返り値	: 
//説明		: ゲーム終了時の処理
//////////////////////////////////////////////////////////////////////////////
void PlayerGame::uninit(void)
{
	delete mState;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Player::update
//返り値	: 
//説明		: ゲーム中の更新
//////////////////////////////////////////////////////////////////////////////
void PlayerGame::update(void)
{
	mState->update();
	hitCheckEnemy();

	//入力デバイス情報
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
//関数名	: Player::setState
//返り値	: 
//説明		: ステート設定
//////////////////////////////////////////////////////////////////////////////
void PlayerGame::setState(PlayerState * p)
{
	if (mState != NULL)
		delete mState;

	mState = p;
	mState->init();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Player::opeCamera
//返り値	: 
//説明		: カメラ操作
//////////////////////////////////////////////////////////////////////////////
void PlayerGame::opeCamera(void)
{
	//入力デバイス情報
	InputMouse		*mouse = Manager::getMouse();

	//視点操作
	vec2 cameraAngle = mCamera->getAngle();
	cameraAngle.x += fmod(mouse->getMoving().x * mSens, PI);
	cameraAngle.y += -mouse->getMoving().y * mSens;

	if (cameraAngle.y >= PI * 0.3f)			//仰角
		cameraAngle.y = PI * 0.3f;

	if (cameraAngle.y <= -PI * 0.3f)		//俯角
		cameraAngle.y = -PI * 0.3f;

	mCamera->setAngle(cameraAngle);
	mTransform.rot = Dvec3(cameraAngle.x, cameraAngle.y, 0.f);

	//球面座標
	vec3 eye = mCamera->getEye();
	float len = mCamera->getLen();
	vec3 at(
		len * cosf(-cameraAngle.y) * sinf(cameraAngle.x) + eye.x,
		len * sinf(-cameraAngle.y) + eye.y,
		len * cosf(-cameraAngle.y) * cosf(cameraAngle.x) + eye.z);

	mCamera->setPosAt(at);

	//右クリック
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
//関数名	: Player::hitCheckEnemy
//返り値	: 
//説明		: 衝突判定
//////////////////////////////////////////////////////////////////////////////
void PlayerGame::hitCheckEnemy(void)
{
	//衝突判定
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
//関数名	: PlayerResult::init
//返り値	: 
//説明		: 初期化
//////////////////////////////////////////////////////////////////////////////
HRESULT PlayerResult::init(void)
{
	mFade = Manager::getFade();
	mFade->fadeIn(60);

	mNext = false;
	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: PlayerResult::uninit
//返り値	: 
//説明		: 終了
//////////////////////////////////////////////////////////////////////////////
void PlayerResult::uninit(void)
{
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: PlayerResult::update
//返り値	: 
//説明		: 更新
//////////////////////////////////////////////////////////////////////////////
void PlayerResult::update(void)
{
	//キー操作
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
