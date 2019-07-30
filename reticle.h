/*****************************************************************************
reticle.h
Aythor	: è„ñÏÅ@è†
Data	: 2017_07_19
=============================================================================
Updata

*****************************************************************************/
#ifndef RETICLE_H
#define RETICLE_H

#include "scene.h"
#include "scene2D.h"

//////////////////////////////////////////////////////////////////////////////
//reticle class
//////////////////////////////////////////////////////////////////////////////
class Reticle : public Scene2D
{
public:
	Reticle(){}
	~Reticle(){}

	HRESULT	init(void);
	void	uninit(void);
	void	update(void);
	void	draw(void);

	void	setDisplay(bool disp){mDisp = disp;}

	static Reticle * create();

private:
	bool mDisp;
};

#endif // !RETICLE_H
