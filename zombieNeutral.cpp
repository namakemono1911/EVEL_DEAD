#include <string>
#include "main.h"
#include "zombieNeutral.h"
#include "zombieWalk.h"
#include "zombieDead.h"

void ZombieNeutral::init()
{
	mZombie->getMotionData().playMotion("neutral");
}

void ZombieNeutral::update()
{
	if (D3DXVec3Length(&Dvec3(mPlayer->getPos() - mZombie->getPos())) < awareRange)
	{
		mZombie->setState(new ZombieWalk(mZombie, mPlayer));
		return;
	}

	if (mZombie->getLife() <= 0)
	{
		mZombie->setState(new ZombieDead(mZombie, mPlayer));
		return;
	}
}
