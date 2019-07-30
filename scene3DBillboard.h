/*****************************************************************************
scene3DBillboard.h
Aythor	: è„ñÏÅ@è†
Data	: 2018_02_23
=============================================================================
Updata

*****************************************************************************/
#include "scene3DState.h"

class Camera;

class Scene3DBillboard : public Scene3DState
{
public:
	Scene3DBillboard(Scene3D* s) : Scene3DState(s) 
	{
		mCamera = (Camera*)Scene::getTypeList(Scene::CAMERA).front();
	}
	~Scene3DBillboard() {}

	void	init() override {}
	void	update() override;

	static Scene3DBillboard* create(Scene3D* s);

private:
	Camera*	mCamera;
};

