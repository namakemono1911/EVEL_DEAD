/*****************************************************************************
playerEdit.h
Aythor	: è„ñÏÅ@è†
Data	: 2018_03_05
=============================================================================
Updata

*****************************************************************************/
#ifndef PLAYER_EDIT

#include "player.h"

class Camera;

class PlayerEdit : public Player
{
public:
	PlayerEdit();
	~PlayerEdit();

	HRESULT init(void);
	void uninit(void);
	void update(void);
	void draw(void) {};

private:
	Camera*	mCamera;
	float	mSens;
};

#endif // !PLAYER_EDIT