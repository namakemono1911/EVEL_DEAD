/*****************************************************************************
weaponNeutral.cpp
Aythor	: ���@��
Data	: 2018_01_30
=============================================================================
Updata

*****************************************************************************/
#ifndef WEAPON_NEUTRAL_H
#define	WEAPON_NEUTRAL_H
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "weaponState.h"

class WeaponState;

class WeaponNeutral : public WeaponState
{
public:
	WeaponNeutral(Weapon* weapon) : WeaponState(weapon) {}
	~WeaponNeutral() {}

	void	init() override;
	void	update() override;

private:

};

#endif // !WEAPON_NEUTRAL_H