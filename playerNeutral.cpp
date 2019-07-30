#include "main.h"
#include "player.h"
#include "playerNeutral.h"
#include "playerMoving.h"
#include "playerDebug.h"

void PlayerNeutral::update()
{
	viewpointOperation();

	if (mPlayer->isPushedUp() || mPlayer->isPushedDown() ||
		mPlayer->isPushedRight() || mPlayer->isPushedLeft())
	{
		mPlayer->setState(new PlayerMoving(mPlayer));
		return;
	}

	if (mPlayer->isPushedDebug())
	{
		mPlayer->setState(new PlayerDebug(mPlayer));
		return;
	}
}
