/*****************************************************************************
stamp3D.cpp
Aythor	: è„ñÏÅ@è†
Data	: 2017_02_21
=============================================================================
Updata

*****************************************************************************/
#include "main.h"
#include "stamp3D.h"
#include "textureManager.h"

HRESULT Stamp3D::init()
{
	return Scene3D::init();
}

void Stamp3D::uninit()
{
	Scene3D::uninit();
}

void Stamp3D::update()
{
	mLife--;
	if (mLife < 0)
		release();

	Scene3D::update();
}

void Stamp3D::draw()
{
	Scene3D::draw();
}

Stamp3D * Stamp3D::create(int life, Dvec3 pos, Dvec3 rot, Dvec3 size, LPDIRECT3DTEXTURE9 texture, Dvec2 texPos, Dvec2 texSize, Dcolor color)
{
	auto stamp = new Stamp3D;
	stamp->mLife = life;
	stamp->mTransform = Transform(pos, rot, Dvec3(1, 1, 1));
	stamp->setRect(size);
	stamp->setTexture(texture);
	stamp->setTextureInfo(texPos, texSize);
	stamp->setColor(color);
	stamp->init();

	return stamp;
}
