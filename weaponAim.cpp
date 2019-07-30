/*****************************************************************************
weaponAim.cpp
Aythor	: ���@��
Data	: 2018_01_30
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "manager.h"
#include "weapon.h"
#include "weaponAim.h"
#include "weaponNeutral.h"
#include "weaponShot.h"
#include "weaponReload.h"
#include "motion.h"

void WeaponAim::init()
{
	mWeapon->getMotionData().playMotion("shake");
	mWeapon->getMotionData().stopMotion();
}

void WeaponAim::update()
{
	if (!mWeapon->whetherAim())
	{
		mWeapon->setState(new WeaponNeutral(mWeapon));
		return;
	}

	if (mWeapon->whetherShot())
	{
		mWeapon->setState(new WeaponShot(mWeapon));
		return;
	}

	if (mWeapon->whetherReload())
	{
		mWeapon->setState(new WeaponReload(mWeapon));
		return;
	}
}
