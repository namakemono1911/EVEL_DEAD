/*****************************************************************************
weaponState.cpp
Aythor	: ���@��
Data	: 2018_01_30
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#ifndef WEAPON_STATE_H
#define	WEAPON_STATE_H

//////////////////////////////////////////////////////////////////////////////
//�N���X�錾
//////////////////////////////////////////////////////////////////////////////
class Weapon;

class WeaponState
{
public:
	WeaponState(Weapon* weapon) { mWeapon = weapon; }
	~WeaponState() {}

	virtual void	init() = 0;
	virtual void	update() = 0;

	void	lookingSite(int& numFrame, int aimTime);
	void	lowerGun(int& numFrame);

protected:
	Weapon*	mWeapon;
};

#endif // !WEAPON_STATE_H
