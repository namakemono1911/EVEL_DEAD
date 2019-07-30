/*****************************************************************************
weaponState.cpp
Aythor	: 上野　匠
Data	: 2018_01_30
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//ヘッダーインクルード
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "weapon.h"
#include "weaponState.h"

void WeaponState::lookingSite(int& numFrame, int aimTime)
{
	numFrame++;
	if (numFrame > aimTime)
		numFrame = aimTime;

	auto rate = (float)numFrame / mWeapon->getAimTime();
	auto pos = (mWeapon->getSitePos() - mWeapon->getLowerPos()) * rate;
	mWeapon->setPos(mWeapon->getLowerPos() + pos);
}

void WeaponState::lowerGun(int& numFrame)
{
	numFrame--;
	if (numFrame < 0)
		numFrame = 0;

	auto rate = (float)numFrame / mWeapon->getAimTime();
	auto pos = (mWeapon->getSitePos() - mWeapon->getLowerPos()) * rate;
	mWeapon->setPos(mWeapon->getLowerPos() + pos);
}
