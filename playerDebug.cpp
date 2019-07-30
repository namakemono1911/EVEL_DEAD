#include "main.h"
#include "playerDebug.h"
#include "playerNeutral.h"
#include "manager.h"
#include "input.h"

void PlayerDebug::init()
{
	Manager::getMouse()->fixing(false);
	ShowCursor(true);					//マウス非表示
}

void PlayerDebug::update()
{
	if (mPlayer->isPushedDebug())
	{
		Manager::getMouse()->fixing(true);
		ShowCursor(false);					//マウス非表示

		mPlayer->setState(new PlayerNeutral(mPlayer));
	}
}
