/*****************************************************************************
weaponAim.cpp
Aythor	: 上野　匠
Data	: 2018_01_30
=============================================================================
Updata

*****************************************************************************/
#ifndef WEAPON_AIM_H
#define	WEAPON_AIM_H
//////////////////////////////////////////////////////////////////////////////
//ヘッダーインクルード
//////////////////////////////////////////////////////////////////////////////
#include "weaponState.h"

class WeaponState;

class WeaponAim : public WeaponState
{
public:
	WeaponAim(Weapon* weapon) : WeaponState(weapon) {}
	~WeaponAim() {}

	void	init() override;
	void	update() override;

private:

};

#endif // !WEAPON_NEUTRAL_H