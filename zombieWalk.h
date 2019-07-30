#pragma once
#include "zombieState.h"

class Zombie;

class ZombieWalk : public ZombieState
{
public:
	ZombieWalk(Zombie* zombie, Scene* p):ZombieState(zombie, p) {}
	~ZombieWalk() {}

	void	init() override;
	void	update() override;

private:
	void	faceToOrientationPlayer();
	void	moveOrientationPlayer();
	void	hitObject();
};

