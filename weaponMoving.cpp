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
#include "weaponState.h"
#include "weaponMoving.h"
#include "weaponAim.h"
#include "weaponNeutral.h"
#include "motion.h"

void WeaponMoving::init()
{
	mWeapon->getMotionData().playMotion("moving");
}

void WeaponMoving::update()
{
	if (mWeapon->whetherMoved())
	{
		mWeapon->setState(new WeaponNeutral(mWeapon));
		return;
	}

	if (mWeapon->whetherAim())
	{
		mWeapon->setState(new WeaponAim(mWeapon));
		return;
	}
}
