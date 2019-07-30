/*****************************************************************************
collisionBox.h
Aythor	: 上野　匠
Data	: 2017_07_13
=============================================================================
Updata

*****************************************************************************/
#ifndef COLLISION_BOX_H
#define COLLISION_BOX_H

#include "collision.h"

//////////////////////////////////////////////////////////////////////////////
//前方宣言
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

	string	axisName;	//軸の名前
	vec3	axis;		//軸
	double	len;		//軸までの長さ
};

class CollisionBox : public Collision
{
public:
	CollisionBox() { mRelativePos = Dvec3(0, 0, 0); mRot = Dvec3(0, 0, 0); mSize = Dvec3(0, 0, 0); }
	~CollisionBox(){}

	//軸の向き
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

	LPDIRECT3DVERTEXBUFFER9	mVtx;	//頂点バッファ
	Dcolor	mColor;			//頂点色
#endif // _DEBUG
	Dvec3	mRelativePos;	//相対座標
	Dvec3	mSize;			//サイズ
	Dvec3	mRot;			//角度
	AXIS	mAxis;			//軸の向き
	Dvec3	mAxisLen;		//軸の長さ
};

#endif // !COLLISION_BOX