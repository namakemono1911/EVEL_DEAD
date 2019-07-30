/*****************************************************************************
playerState.cpp
Aythor	: 上野　匠
Data	: 2017_01_31
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//ファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "playerState.h"
#include "manager.h"

#define MOVE	(0.7f);

void PlayerState::viewpointOperation()
{
	//入力デバイス情報
	InputMouse		*mouse = Manager::getMouse();

	//視点操作
	vec2 mCameraAngle = mCamera->getAngle();
	mCameraAngle.x += fmod(mouse->getMoving().x * mPlayer->getSens(), PI);
	mCameraAngle.y += -mouse->getMoving().y * mPlayer->getSens();

	if (mCameraAngle.y >= PI * 0.3f)			//仰角
		mCameraAngle.y = PI * 0.3f;

	if (mCameraAngle.y <= -PI * 0.3f)		//俯角
		mCameraAngle.y = -PI * 0.3f;

	mCamera->setAngle(mCameraAngle);
	mPlayer->setRot(Dvec3(mCameraAngle.x, mCameraAngle.y, 0.f));

	//球面座標
	vec3 eye = mCamera->getEye();
	float len = mCamera->getLen();
	vec3 at(
		len * cosf(-mCameraAngle.y) * sinf(mCameraAngle.x) + eye.x,
		len * sinf(-mCameraAngle.y) + eye.y,
		len * cosf(-mCameraAngle.y) * cosf(mCameraAngle.x) + eye.z);

	mCamera->setPosAt(at);

	//右クリック
	float fovy = mCamera->getFovy();
	if (mouse->getPress(MOUSE_RIGHT))
	{
		mPlayer->moveSpeed() = 0.3f * MOVE;
		fovy -= 0.1f;
		if (fovy > PI / 4.f)
			mCamera->setFovy(fovy);
		else
			mCamera->setFovy(PI / 4.f);
	}
	else
	{
		mPlayer->moveSpeed() = MOVE;
		fovy += 0.1f;
		if (fovy < PI / 3.f)
			mCamera->setFovy(fovy);
		else
			mCamera->setFovy(PI / 3.f);
	}
}
