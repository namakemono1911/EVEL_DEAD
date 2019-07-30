/*****************************************************************************
weaponNeutral.cpp
Aythor	: ���@��
Data	: 2018_01_30
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "weapon.h"
#include "weaponNeutral.h"
#include "weaponAim.h"
#include "weaponReload.h"
#include "motion.h"

void WeaponNeutral::init()
{
	mWeapon->getMotionData().stopMotion();
}

void WeaponNeutral::update()
{
	if (mWeapon->whetherReload())
	{
		mWeapon->setState(new WeaponReload(mWeapon));
		return;
	}

	if (mWeapon->whetherAim())
	{
		mWeapon->setState(new WeaponAim(mWeapon));
		return;
	}
}
