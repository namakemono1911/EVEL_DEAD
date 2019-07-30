#pragma once
#include "zombieState.h"

class ZombieAttack : public ZombieState
{
public:
	ZombieAttack(Zombie* z, Scene* p) : ZombieState(z, p) {}
	~ZombieAttack() {}

	void init();
	void update();
};
