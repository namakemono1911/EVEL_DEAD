/*****************************************************************************
weaponShot.cpp
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
#include "weaponShot.h"
#include "weaponAim.h"
#include "weaponNeutral.h"
#include "motion.h"

void WeaponShot::init()
{
	mWeapon->getMotionData().playMotion("blowback");
	mWeapon->shot();
}

void WeaponShot::update()
{
	if (mWeapon->getMotionData().isMotion())
		return;

	if (mWeapon->whetherAim())
		mWeapon->setState(new WeaponAim(mWeapon));
	else
		mWeapon->setState(new WeaponNeutral(mWeapon));
}
