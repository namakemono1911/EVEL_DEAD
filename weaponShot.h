/*****************************************************************************
weaponShot.h
Aythor	: ���@��
Data	: 2018_01_30
=============================================================================
Updata

*****************************************************************************/
#ifndef WEAPON_SHOT_H
#define WEAPON_SHOT_H
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�C���N���[�h
//////////////////////////////////////////////////////////////////////////////
class WeaponState;

class WeaponShot : public WeaponState
{
public:
	WeaponShot(Weapon* weapon) : WeaponState(weapon) {}
	~WeaponShot() {}

	void	init() override;
	void	update() override;

private:

};


#endif // !WEAPON_SHOT_H
