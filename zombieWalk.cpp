#include "main.h"
#include "zombieWalk.h"
#include "zombieAttack.h"
#include "zombieNeutral.h"
#include "zombieDead.h"
#include "manager.h"

void ZombieWalk::init()
{
	mZombie->getMotionData().playMotion("walk");
}

void ZombieWalk::update()
{
	auto len = D3DXVec3Length(&Dvec3(mPlayer->getPos() - mZombie->getPos()));

	if (mZombie->getLife() <= 0)
	{
		mZombie->setState(new ZombieDead(mZombie, mPlayer));
		return;
	}

	/*if (len < attackRange)
	{
		mZombie->setState(new ZombieAttack(mZombie, mPlayer));
		return;
		}*/

	if (len > awareRange)
	{
		mZombie->setState(new ZombieNeutral(mZombie, mPlayer));
		return;
	}

	mZombie->setMoveVec(vec3::Dnormalize(mPlayer->getPos() - mZombie->getPos()));
	faceToOrientationPlayer();
	hitObject();
	moveOrientationPlayer();
}

void ZombieWalk::faceToOrientationPlayer()
{
	Dvec3 pos = mZombie->getPos();
	Dvec3 playerPos = mPlayer->getPos();
	pos.y = 0.f;
	playerPos.y = 0.f;
	auto rot = vec3::Dask(mZombie->getPos(), playerPos);
	rot = vec3::Dnormalize(rot);

	//プレイヤーとの角度算出
	auto angle = vec3::angleVector(rot, Dvec3(0.f, 0.f, 1.f));
	if (pos.x > playerPos.x)
		angle *= -1.f;
	mZombie->setRot(Dvec3((float)angle + PI, 0.f, 0.f));

	mZombie->setMoveVec(mZombie->getSpeed() * rot);
}

void ZombieWalk::moveOrientationPlayer()
{
	//プレイヤーの方向に移動
	mZombie->setPos(mZombie->getPos() + mZombie->getMoveVec() * mZombie->getSpeed());
}

void ZombieWalk::hitObject()
{
	auto objectList = Scene::getTypeList(Scene::OBJECT);

	for (auto& object : objectList)
	{
		if (object->getCollision() != NULL)
		{
			Dvec3 crossPos;
			Dvec3 axis;
			if (object->getCollision()->hitByRayAll(&crossPos, &axis, mZombie->getPos(), mZombie->getPos() + mZombie->getMoveVec() * mZombie->getSpeed()))
			{
				mZombie->setMoveVec(Collision::faceScrachVec(mZombie->getMoveVec(), axis));
			}
		}
	}
}
