#include "main.h"
#include "playerDebug.h"
#include "playerNeutral.h"
#include "manager.h"
#include "input.h"

void PlayerDebug::init()
{
	Manager::getMouse()->fixing(false);
	ShowCursor(true);					//�}�E�X��\��
}

void PlayerDebug::update()
{
	if (mPlayer->isPushedDebug())
	{
		Manager::getMouse()->fixing(true);
		ShowCursor(false);					//�}�E�X��\��

		mPlayer->setState(new PlayerNeutral(mPlayer));
	}
}
