/*****************************************************************************
stampState.cpp
Aythor	: è„ñÏÅ@è†
Data	: 2017_02_14
=============================================================================
Updata

*****************************************************************************/
#ifndef STAMP_STATE_H
#define STAMP_STATE_H

#include "scene3D.h"

class Scene3D;

class Scene3DState
{
public:
	Scene3DState(Scene3D* s) { mScene = s; }
	~Scene3DState() {}

	virtual void	init() = 0;
	virtual void	update() = 0;

protected:
	Scene3D*	mScene;
};

#endif // !STAMP_STATE_H

