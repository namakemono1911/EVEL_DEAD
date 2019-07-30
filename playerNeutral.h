#ifndef PLAYER_NEUTRAL_H
#define	PLAYER_NEUTRAL_H

#include "playerState.h"

class PlayerGame;

class PlayerNeutral : public PlayerState
{
public:
	PlayerNeutral(PlayerGame* p) : PlayerState(p) {}
	~PlayerNeutral() {}

	void	update() override;
};


#endif // !PLAYER_NEUTRAL_H