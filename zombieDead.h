#pragma once
#include "zombieState.h"
class ZombieDead :
	public ZombieState
{
public:
	ZombieDead(Zombie* z, Scene* p) : ZombieState(z, p) {}
	~ZombieDead() {}

	void init() override;
	void update() override;
};

