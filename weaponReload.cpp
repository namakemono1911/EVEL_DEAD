/*****************************************************************************
weaponReload.cpp
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
#include "weaponNeutral.h"
#include "weaponReload.h"
#include "motion.h"

void WeaponReload::init()
{
	mWeapon->getMotionData().playMotion("reload");
}

void WeaponReload::update()
{
	if (!mWeapon->getMotionData().isMotion())
		mWeapon->setState(new WeaponNeutral(mWeapon));
}
