#pragma once
#include "zombieState.h"
class ZombieNeutral :
	public ZombieState
{
public:
	ZombieNeutral(Zombie* zombie, Scene* p) :ZombieState(zombie, p) {};
	~ZombieNeutral() {}

	void	init() override;
	void	update() override;
};

