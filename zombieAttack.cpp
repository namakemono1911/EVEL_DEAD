#include "main.h"
#include "zombieAttack.h"
#include "zombieNeutral.h"

void ZombieAttack::init()
{
	mZombie->getMotionData().playMotion("attack");
}

void ZombieAttack::update()
{
	if (!mZombie->getMotionData().isMotion())
		mZombie->setState(new ZombieNeutral(mZombie, mPlayer));


}
