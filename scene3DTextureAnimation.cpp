#include "main.h"
#include "scene3DTextureAnimation.h"

void Scene3DTextureAnimation::init()
{
	mNumFrame = 0;
	mNumAnime = 0;

	auto texPos = calcTexturePos();
	mScene->setTexturePos(texPos);
	mScene->setTextureSize(Dvec2(1.f / mNumHorizonal, 1.f / mNumVertical));
}

void Scene3DTextureAnimation::update()
{
	if (mInterval % ++mNumFrame != 0)
		return;
	
	auto texPos = calcTexturePos();
	mScene->setTexturePos(texPos);
	mNumAnime++;
}

Scene3DTextureAnimation * Scene3DTextureAnimation::create(Scene3D* s, int numVertical, int numHorizonal, int interval)
{
	auto state = new Scene3DTextureAnimation(s);
	state->mNumVertical = numVertical;
	state->mNumHorizonal = numHorizonal;
	state->mInterval = interval;
	state->init();

	return state;
}

Dvec2 Scene3DTextureAnimation::calcTexturePos()
{
	Dvec2	texPos;
	auto rateH = 1.f / mNumHorizonal;
	texPos.x = rateH * mNumAnime;
	auto rateV = 1.f / mNumVertical;
	texPos.y = rateV * (int)texPos.x;

	return texPos;
}
