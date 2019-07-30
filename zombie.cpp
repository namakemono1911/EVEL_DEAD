/*****************************************************************************
zombie.cpp
Aythor	: 上野　匠
Data	: 2017_07_12
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//ファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "scene.h"
#include "motion.h"
#include "collision.h"
#include "collisionBall.h"
#include "player.h"
#include "zombie.h"
#include "zombieState.h"
#include "zombieNeutral.h"
#include "manager.h"
#include "mode.h"
#include "imgui.h"

//////////////////////////////////////////////////////////////////////////////
//定数定義
//////////////////////////////////////////////////////////////////////////////
#define SPD		(0.3f)		//移動速度

//////////////////////////////////////////////////////////////////////////////
//関数名	: Zombie::init()
//返り値	: 
//説明		: 初期化
//////////////////////////////////////////////////////////////////////////////
HRESULT Zombie::init(void)
{
	setObjType(ZOMBIE);
	mMotionData.setParent(this);
	mMotionData.playMotion("neutral");

	mState = NULL;
	setState(new ZombieNeutral(this, Scene::getTypeList(PLAYER).front()));

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Zombie::uninit()
//返り値	: 
//説明		: 終了
//////////////////////////////////////////////////////////////////////////////
void Zombie::uninit(void)
{
	for (auto part : mMotionData.getPartsList())
		part->release();
	release();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Zombie::update()
//返り値	: 
//説明		: 更新
//////////////////////////////////////////////////////////////////////////////
void Zombie::update(void)
{
	mState->update();
	mMotionData.update();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Zombie::draw()
//返り値	: 
//説明		: 描画
//////////////////////////////////////////////////////////////////////////////
void Zombie::draw(void)
{

}

void Zombie::addDamage(int damage)
{ 
	mLife -= damage;
	if (mLife <= 0)
		mLife = 0;
}

bool Zombie::hitCheckAllParts(Dvec3* crossPoint, Dvec3* axis, Dvec3 pos, Dvec3 ray)
{
	if (mCollision != NULL)
		if (mCollision->hitByRayAll(crossPoint, axis, pos, ray))
			return true;

	auto isHit = false;
	auto shortDistance = vec3::lenVector(ray);
	for (auto part : mMotionData.getPartsList())
	{
		if (part->getCollision() == NULL)
			continue;

		if (part->getCollision()->hitByRayAll(crossPoint, axis, pos, ray))
				isHit = true;
	}

	return isHit;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Zombie::setState()
//返り値	: 
//説明		: ステータス設定
//////////////////////////////////////////////////////////////////////////////
void Zombie::setState(ZombieState * state)
{
	if (mState != NULL)
		delete mState;

	mState = state;
	mState->init();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Zombie::create()
//返り値	: 
//説明		: 生成
//////////////////////////////////////////////////////////////////////////////
Zombie * Zombie::create(Dvec3 pos, Dvec3 rot, Dvec3 size)
{
	auto zombie = new Zombie;

	zombie->mMotionData.loadMotionData("data/model/motionModel/zombie001.mo", "data/motion/zombie001.mt", OTHER);
	zombie->mMyName = "zombie";
	zombie->mTransform.pos = pos;
	zombie->mTransform.rot = rot;
	zombie->mTransform.size = size;
	zombie->init();
	zombie->mCenter;
	zombie->mSpd = SPD;

	return zombie;
}
