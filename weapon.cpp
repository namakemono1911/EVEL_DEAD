/*****************************************************************************
weapon.cpp
Aythor	: ���@��
Data	: 2018_01_09
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�C���N���[�h
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
//�֐���	: Weapon::init
//�Ԃ�l	: 
//����		: ������
//////////////////////////////////////////////////////////////////////////////
HRESULT Weapon::init()
{
	mMyName = "weapon";
	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Weapon::init
//�Ԃ�l	: 
//����		: ������
//////////////////////////////////////////////////////////////////////////////
void Weapon::uninit()
{
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Weapon::update
//�Ԃ�l	: 
//����		: �X�V
//////////////////////////////////////////////////////////////////////////////
void Weapon::update()
{
	
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Weapon::draw
//�Ԃ�l	: 
//����		: �`��
//////////////////////////////////////////////////////////////////////////////
void Weapon::draw()
{

}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Weapon::setState
//�Ԃ�l	: 
//����		: �X�e�[�g�ݒ�
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
//�֐���	: Goverment::init
//�Ԃ�l	: 
//����		: ������
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
//�֐���	: Goverment::uninit
//�Ԃ�l	: 
//����		: �I��
//////////////////////////////////////////////////////////////////////////////
void Goverment::uninit()
{
	delete mState;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Goverment::update
//�Ԃ�l	: 
//����		: �X�V
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
//�֐���	: Goverment::shot
//�Ԃ�l	: 
//����		: ����
//////////////////////////////////////////////////////////////////////////////
void Goverment::shot()
{
	auto direction = mCamera->getAt() - mCamera->getEye();
	D3DXVec3Normalize(&direction, &direction);
	mBulletList.push_back(Bullet::create(mParent->getPos(), direction, 100.f, 100.f));
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Goverment::create
//�Ԃ�l	: 
//����		: ����
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
