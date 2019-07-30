/*****************************************************************************
playerState.cpp
Aythor	: 上野　匠
Data	: 2017_01_31
=============================================================================
Updata

*****************************************************************************/
#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

#include "camera.h"
#include "player.h"

//////////////////////////////////////////////////////////////////////////////
//クラス定義
//////////////////////////////////////////////////////////////////////////////
class PlayerGame;

class PlayerState
{
public:
	PlayerState(PlayerGame* player) { mPlayer = player; }
	~PlayerState() {}

	virtual void	init() { mCamera = (Camera*)Scene::getTypeList(Scene::CAMERA).front(); }
	virtual void	update() = 0;

	void	viewpointOperation();

protected:
	PlayerGame*		mPlayer;
	Camera*			mCamera;

private:
};

#endif // !PLAYER_STATE_H