/*****************************************************************************
weapon.cpp
Aythor	: 上野　匠
Data	: 2018_01_09
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//ヘッダーインクルード
//////////////////////////////////////////////////////////////////////////////
#include <list>
#include "main.h"
#include "manager.h"
#include "modelData.h"
#include "motion.h"
#include "weaponState.h"
#include "weaponNeutral.h"
#include "input.h"
#include "camera.h"
#include "weapon.h"
#include "zombie.h"

//////////////////////////////////////////////////////////////////////////////
//関数名	: Weapon::init
//返り値	: 
//説明		: 初期化
//////////////////////////////////////////////////////////////////////////////
HRESULT Weapon::init()
{
	mMyName = "weapon";
	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Weapon::init
//返り値	: 
//説明		: 初期化
//////////////////////////////////////////////////////////////////////////////
void Weapon::uninit()
{
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Weapon::update
//返り値	: 
//説明		: 更新
//////////////////////////////////////////////////////////////////////////////
void Weapon::update()
{
	
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Weapon::draw
//返り値	: 
//説明		: 描画
//////////////////////////////////////////////////////////////////////////////
void Weapon::draw()
{

}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Weapon::setState
//返り値	: 
//説明		: ステート設定
//////////////////////////////////////////////////////////////////////////////
void Weapon::setState(WeaponState * state)
{
	if (mState != NULL)
		delete mState;

	mState = state;
	mState->init();
}

/*
###################################################################################################################
PlayerResult class
###################################################################################################################
*/
//////////////////////////////////////////////////////////////////////////////
//関数名	: Goverment::init
//返り値	: 
//説明		: 初期化
//////////////////////////////////////////////////////////////////////////////
HRESULT Goverment::init()
{
	mBullet = 100;
	mMagazineCapacity = 7;
	mBulletInMagazine = mMagazineCapacity;
	
	mMotionData.loadMotionData("data/model/motionModel/government.mo", "data/motion/government.mt");
	mMotionData.setParent(this);

	mCamera = (Camera*)Scene::getTypeList(Scene::CAMERA).front();

	setState(new WeaponNeutral(this));
	Weapon::init();
	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Goverment::uninit
//返り値	: 
//説明		: 終了
//////////////////////////////////////////////////////////////////////////////
void Goverment::uninit()
{
	delete mState;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Goverment::update
//返り値	: 
//説明		: 更新
//////////////////////////////////////////////////////////////////////////////
void Goverment::update()
{
	mState->update();
	if (whetherAim())
		mState->lookingSite(mNumFrame, mAimTime);
	else
		mState->lowerGun(mNumFrame);

	mMotionData.update();

	for (auto it = mBulletList.begin(); it != mBulletList.end(); it)
	{
		auto bullet = *it;

		bullet->update();
		if (bullet->isClear())
		{
			delete bullet;
			it = mBulletList.erase(it);
		}
		else
			++it;
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Goverment::shot
//返り値	: 
//説明		: 発射
//////////////////////////////////////////////////////////////////////////////
void Goverment::shot()
{
	auto direction = mCamera->getAt() - mCamera->getEye();
	D3DXVec3Normalize(&direction, &direction);
	mBulletList.push_back(Bullet::create(mParent->getPos(), direction, 100.f, 100.f));
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Goverment::create
//返り値	: 
//説明		: 生成
//////////////////////////////////////////////////////////////////////////////
Goverment * Goverment::create(Dvec3 pos)
{
	auto goverment = new Goverment(pos);
	goverment->mLowerPos = pos;
	goverment->mSitePos = Dvec3(0, 0, -3);
	goverment->mAimTime = 5;
	goverment->init();
	return goverment;
}
