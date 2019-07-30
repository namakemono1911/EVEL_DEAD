/*****************************************************************************
stamp3D.cpp
Aythor	: è„ñÏÅ@è†
Data	: 2017_02_21
=============================================================================
Updata

*****************************************************************************/
#ifndef STAMP3D_H
#define	STAMP3D_H

#include <list>
#include "scene3D.h"

class StampState;

class Stamp3D : public Scene3D
{
public:
	Stamp3D() {}
	~Stamp3D() {}

	HRESULT	init();
	void	uninit();
	void	update();
	void	draw();

	static Stamp3D*	create(int life, Dvec3 pos, Dvec3 rot, Dvec3 size, LPDIRECT3DTEXTURE9 texture, Dvec2 texPos = Dvec2(0, 0),
		Dvec2 texSize = Dvec2(1, 1), Dcolor color = Dcolor(1, 1, 1, 1));

private:
	int		mLife = 0;		//éıñΩ
};


#endif // !STAMP3D_H