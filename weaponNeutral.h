/*****************************************************************************
weaponNeutral.cpp
Aythor	: 上野　匠
Data	: 2018_01_30
=============================================================================
Updata

*****************************************************************************/
#ifndef WEAPON_NEUTRAL_H
#define	WEAPON_NEUTRAL_H
//////////////////////////////////////////////////////////////////////////////
//ヘッダーインクルード
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