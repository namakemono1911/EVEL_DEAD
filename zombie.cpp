/*****************************************************************************
zombie.cpp
Aythor	: ���@��
Data	: 2017_07_12
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "scene.h"
#include "motion.h"
#include "collision.h"
#include "collisionBall.h"
#include "player.h"
#include "zombie.h"
#include "zombieState.h"
#include "zombieNeutral.h"
#include "manager.h"
#include "mode.h"
#include "imgui.h"

//////////////////////////////////////////////////////////////////////////////
//�萔��`
//////////////////////////////////////////////////////////////////////////////
#define SPD		(0.3f)		//�ړ����x

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Zombie::init()
//�Ԃ�l	: 
//����		: ������
//////////////////////////////////////////////////////////////////////////////
HRESULT Zombie::init(void)
{
	setObjType(ZOMBIE);
	mMotionData.setParent(this);
	mMotionData.playMotion("neutral");

	mState = NULL;
	setState(new ZombieNeutral(this, Scene::getTypeList(PLAYER).front()));

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Zombie::uninit()
//�Ԃ�l	: 
//����		: �I��
//////////////////////////////////////////////////////////////////////////////
void Zombie::uninit(void)
{
	for (auto part : mMotionData.getPartsList())
		part->release();
	release();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Zombie::update()
//�Ԃ�l	: 
//����		: �X�V
//////////////////////////////////////////////////////////////////////////////
void Zombie::update(void)
{
	mState->update();
	mMotionData.update();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Zombie::draw()
//�Ԃ�l	: 
//����		: �`��
//////////////////////////////////////////////////////////////////////////////
void Zombie::draw(void)
{

}

void Zombie::addDamage(int damage)
{ 
	mLife -= damage;
	if (mLife <= 0)
		mLife = 0;
}

bool Zombie::hitCheckAllParts(Dvec3* crossPoint, Dvec3* axis, Dvec3 pos, Dvec3 ray)
{
	if (mCollision != NULL)
		if (mCollision->hitByRayAll(crossPoint, axis, pos, ray))
			return true;

	auto isHit = false;
	auto shortDistance = vec3::lenVector(ray);
	for (auto part : mMotionData.getPartsList())
	{
		if (part->getCollision() == NULL)
			continue;

		if (part->getCollision()->hitByRayAll(crossPoint, axis, pos, ray))
				isHit = true;
	}

	return isHit;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Zombie::setState()
//�Ԃ�l	: 
//����		: �X�e�[�^�X�ݒ�
//////////////////////////////////////////////////////////////////////////////
void Zombie::setState(ZombieState * state)
{
	if (mState != NULL)
		delete mState;

	mState = state;
	mState->init();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Zombie::create()
//�Ԃ�l	: 
//����		: ����
//////////////////////////////////////////////////////////////////////////////
Zombie * Zombie::create(Dvec3 pos, Dvec3 rot, Dvec3 size)
{
	auto zombie = new Zombie;

	zombie->mMotionData.loadMotionData("data/model/motionModel/zombie001.mo", "data/motion/zombie001.mt", OTHER);
	zombie->mMyName = "zombie";
	zombie->mTransform.pos = pos;
	zombie->mTransform.rot = rot;
	zombie->mTransform.size = size;
	zombie->init();
	zombie->mCenter;
	zombie->mSpd = SPD;

	return zombie;
}
