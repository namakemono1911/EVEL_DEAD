/*****************************************************************************
scene3DBillboard.cpp
Aythor	: ã–ì@ 
Data	: 2018_02_23
=============================================================================
Updata

*****************************************************************************/
#include "main.h"
#include "camera.h"
#include "scene3DBillboard.h"

void Scene3DBillboard::update()
{
	DMtx inverseCamera;
	D3DXMatrixInverse(&inverseCamera, NULL, &mCamera->getViewMtx());
	inverseCamera._41 = 0.0f;
	inverseCamera._42 = 0.0f;
	inverseCamera._43 = 0.0f;

	mScene->matrixMulti(inverseCamera);
}

Scene3DBillboard * Scene3DBillboard::create(Scene3D* s)
{
	return new Scene3DBillboard(s);
}
