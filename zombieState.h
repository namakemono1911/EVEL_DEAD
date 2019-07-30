#pragma once
#include "zombie.h"

class ZombieState
{
public:
	ZombieState(Zombie* zombie, Scene* p) { mZombie = zombie; mPlayer = p; }
	~ZombieState() {}

	virtual void	init() = 0;
	virtual void	update() = 0;

protected:
	Scene * mPlayer;		//ƒvƒŒƒCƒ„[‚Ìî•ñ
	Zombie * mZombie;
};

