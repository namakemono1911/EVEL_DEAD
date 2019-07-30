/*****************************************************************************
weaponAim.cpp
Aythor	: 上野　匠
Data	: 2018_01_30
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//ヘッダーインクルード
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
