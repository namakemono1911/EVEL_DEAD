/*****************************************************************************
collisionBox.h
Aythor	: ���@��
Data	: 2017_07_13
=============================================================================
Updata

*****************************************************************************/
#ifndef COLLISION_BOX_H
#define COLLISION_BOX_H

#include "collision.h"

//////////////////////////////////////////////////////////////////////////////
//�O���錾
//////////////////////////////////////////////////////////////////////////////
class Collision;
class Scene;
class vec3;

//////////////////////////////////////////////////////////////////////////////
//CollisionBox class
//////////////////////////////////////////////////////////////////////////////
class AxisLen
{
public:
	AxisLen() {}
	~AxisLen() {}

	bool operator< (const AxisLen &ref) { return len < ref.len; }
	bool operator> (const AxisLen &ref) { return len > ref.len; }

	string	axisName;	//���̖��O
	vec3	axis;		//��
	double	len;		//���܂ł̒���
};

class CollisionBox : public Collision
{
public:
	CollisionBox() { mRelativePos = Dvec3(0, 0, 0); mRot = Dvec3(0, 0, 0); mSize = Dvec3(0, 0, 0); }
	~CollisionBox(){}

	//���̌���
	struct AXIS
	{
		vec3	x;
		vec3	y;
		vec3	z;
	};

	HRESULT	init(void);
	void	uninit(void);
	void	update(void);
	
#ifdef _DEBUG
	void draw(void);
#endif // _DEBUG

	void	assignmentTarget(FILE* fp);

	static CollisionBox	*create(Scene *pearents, Dvec3 pos, Dvec3 size);
	auto	getSize(void) { return mSize; }
	auto	getRot(void) { return mRot; }
	Dvec3	*getSizeAd(void){return &mSize;}
	Dvec3	*getRotAd(void){return &mRot;}

	DMtx	calcWorldMtx(void);
	bool	hitByRay(Dvec3 *outCrossPos, Dvec3 *outAxis, Dvec3 pos, Dvec3 ray);
	bool	hitByPoint(Dvec3 point);
	bool	hitFaceAndPoint(string facePos, vec3 pos);
	vector<vec3>	getRectPos(string facePos);
	Dvec3	getCrossPos(Dvec3 pos, Dvec3 ray, double dotPos, double dotRay);
	Dvec3	getDotPosAndRay(string axis, double *dotPos, double *dotRay, vec3 pos, vec3 ray);
	bool	rayIsIntersectioing(double dotPos, double dotRay);

private:
#ifdef _DEBUG
	void	setVtx(void);

	LPDIRECT3DVERTEXBUFFER9	mVtx;	//���_�o�b�t�@
	Dcolor	mColor;			//���_�F
#endif // _DEBUG
	Dvec3	mRelativePos;	//���΍��W
	Dvec3	mSize;			//�T�C�Y
	Dvec3	mRot;			//�p�x
	AXIS	mAxis;			//���̌���
	Dvec3	mAxisLen;		//���̒���
};

#endif // !COLLISION_BOX