/*****************************************************************************
weapon.cpp
Aythor	: ���@��
Data	: 2018_01_09
=============================================================================
Updata

*****************************************************************************/
#ifndef WEAPON_H
#define WEAPON_H

#include "manager.h"
#include "scene.h"
#include "bullet.h"
#include "motion.h"
#include "input.h"

//////////////////////////////////////////////////////////////////////////////
//�O���錾
//////////////////////////////////////////////////////////////////////////////
class Scene;
class Manager;
class MotionModel;
class Bullet;
class ModelParts;
class WeaponState;
class InputKeyboard;
class InputMouse;
class Camera;

//////////////////////////////////////////////////////////////////////////////
//�N���X��`
//////////////////////////////////////////////////////////////////////////////
class Weapon : public Scene
{
public:
	Weapon() {
		mState = NULL;
		mShotKey = MOUSE_LEFT;
		mAimKey = MOUSE_RIGHT;
		mReloadKey = DIK_R;
	};
	~Weapon() {};

	HRESULT	init() override;
	void	uninit() override;
	void	update() override;
	void	draw() override;

	const auto&	getSitePos() { return mSitePos; }
	const auto&	getLowerPos() { return mLowerPos; }
	const auto&	getAimTime() { return mAimTime; }
	auto&	getMotionData() { return mMotionData; }
	auto	whetherShot() { return Manager::getMouse()->getTrigger(mShotKey); }
	auto	whetherReload() { return Manager::getKeyboard()->getTrigger(mReloadKey); }
	auto	whetherAim() { return Manager::getMouse()->getPress(mAimKey); }
	auto	whetherMoved() { return true; }

	void	setState(WeaponState *state);

	virtual void	shot() = 0;

protected:
	WeaponState		*mState;				//�X�e�[�g
	MotionModel		mMotionData;
	list<Bullet*>	mBulletList;
	int				mMagazineCapacity;		//�}�K�W�����ɓ���e��
	int				mBullet;				//�c�e
	int				mBulletInMagazine;		//�}�K�W�����̎c�e
	int				mAimTime;				//�T�C�g��`���܂ł̃t���[��
	int				mNumFrame;				//�\���Ă���̃t���[����
	Dvec3			mSitePos = Dvec3(0, 0, 0);
	Dvec3			mLowerPos = Dvec3(-2.f, -1.f, -3.f);

private:
	int				mShotKey;
	int				mReloadKey;
	int				mAimKey;
};

class NullWeapon : public Weapon
{
public:
	NullWeapon() {};
	~NullWeapon() {};

	void	shot() override {}

private:

};

class Goverment : public Weapon
{
public:
	Goverment() : Weapon() {};
	Goverment(Dvec3 pos) { mTransform.pos = pos; }
	~Goverment() {};

	HRESULT	init() override;
	void	uninit() override;
	void	update() override;
	void	draw() override {  }

	void	shot() override;

	static Goverment*	create(Dvec3 pos);

private:
	Scene*	mMark;
	Camera* mCamera;
};

#endif // !WEAPON_H