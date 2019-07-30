#pragma once
#include "playerState.h"
class PlayerDebug : public PlayerState
{
public:
	PlayerDebug(PlayerGame* p) : PlayerState(p) {}
	~PlayerDebug() {}

	void	init() override;
	void	update() override;
};