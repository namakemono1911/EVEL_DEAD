/*****************************************************************************
zombie.cpp
Aythor	: ���@��
Data	: 2017_07_12
=============================================================================
Updata

*****************************************************************************/
#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <string>
#include "motion.h"
#include "scene.h"

//////////////////////////////////////////////////////////////////////////////
//�萔�錾
//////////////////////////////////////////////////////////////////////////////
const static float	awareRange = 150.f;
const static float	attackRange = 5.f;
const static float	attackMove = 15.f;

//////////////////////////////////////////////////////////////////////////////
//�O���錾
//////////////////////////////////////////////////////////////////////////////
class Scene;
class MotionModel;
class Collision;
class CollisionBall;
class ZombieState;
class Player;

//////////////////////////////////////////////////////////////////////////////
//Zombie class
//////////////////////////////////////////////////////////////////////////////
class Zombie : public Scene
{
public:
	Zombie():Scene(PRIME_THIRD){}
	~Zombie(){}

	HRESULT init(void);
	void uninit(void);
	void update(void);
	void draw(void);

	float			getLen(void){return mLen;}
	Dvec3			getCenter(void){return mCenter;}
	const auto&		getSpeed() { return mSpd; }
	const auto&		getMoveVec() { return mMoveVec; }
	const auto&		getLife() { return mLife; }

	auto			getModelList(void) { return mMotionData.getPartsList(); }
	void			addDamage(int damage);
	bool			hitCheckAllParts(Dvec3* crossPoint, Dvec3* axis, Dvec3 pos, Dvec3 ray);
	
	void			setState(ZombieState* state);
	void			setMoveVec(Dvec3 vec) { mMoveVec = vec; }
	auto&			getMotionData(void) { return mMotionData; }
	static Zombie	*create(Dvec3 pos, Dvec3 rot = Dvec3(0, 0, 0), Dvec3 size = Dvec3(1, 1, 1));

private:
	MotionModel		mMotionData;	//���f���ƃ��[�V�����f�[�^
	ZombieState*	mState = NULL;			//�X�e�[�^�X
	Dvec3			mCenter;		//���S
	Dvec3			mMoveVec;		//�i�s�����x�N�g��
	float			mSpd;			//�ړ����x
	float			mLen;			//�R���W�������a
	int				mLife = 50;		//�̗�
};

#endif // !ZOMBIE_H
