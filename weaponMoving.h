/*****************************************************************************
weaponMoving.cpp
Aythor	: ���@��
Data	: 2018_01_30
=============================================================================
Updata

*****************************************************************************/
#ifndef WEAPON_MOVING_H
#define	WEAPON_MOVING_H
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�C���N���[�h
//////////////////////////////////////////////////////////////////////////////
class WeaponState;

class WeaponMoving : public WeaponState
{
public:
	WeaponMoving(Weapon* weapon) : WeaponState(weapon) {}
	~WeaponMoving() {}

	void	init() override;
	void	update() override;

private:

};

#endif // !WEAPON_NEUTRAL_H