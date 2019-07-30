/*****************************************************************************
weaponReload.cpp
Aythor	: 上野　匠
Data	: 2018_01_30
=============================================================================
Updata

*****************************************************************************/
#ifndef WEAPON_RELOAD_H
#define	WEAPON_RELOAD_H
//////////////////////////////////////////////////////////////////////////////
//ヘッダーインクルード
//////////////////////////////////////////////////////////////////////////////
#include "weaponState.h"

class WeaponState;

class WeaponReload : public WeaponState
{
public:
	WeaponReload(Weapon* weapon) : WeaponState(weapon) {}
	~WeaponReload() {}

	void	init() override;
	void	update() override;

private:

};

#endif // !WEAPON_RELOAD_H