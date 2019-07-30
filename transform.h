/*****************************************************************************
transform.h
Aythor	: è„ñÏÅ@è†
Data	: 2017_09_02
=============================================================================
Updata

*****************************************************************************/
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "vec.h"

//////////////////////////////////////////////////////////////////////////////
// ÉNÉâÉXêÈåæ
//////////////////////////////////////////////////////////////////////////////
class Transform
{
public:
	Transform() { pos = Dvec3(0, 0, 0); rot = Dvec3(0, 0, 0); size = Dvec3(1, 1, 1); }
	Transform(Dvec3 argPos, Dvec3 argRot, Dvec3 argSize){pos = argPos; rot = argRot; size = argSize;}
	~Transform(){}

	const Transform operator- (const Transform &ref) const { return Transform(ref.pos - pos, ref.rot - rot, ref.size - size); }
	const Transform operator+ (const Transform &ref) const { return Transform(ref.pos + pos, ref.rot + rot, ref.size + size); }
	const Transform operator* (const Transform &ref) const { return Transform(vec3::conv(vec3(pos) * vec3(ref.pos)), vec3::conv(vec3(rot) * vec3(ref.rot)), vec3::conv(vec3(size) * vec3(ref.size))); }
	const Transform operator/ (const Transform &ref) const { return Transform(vec3::conv(vec3(pos) / vec3(ref.pos)), vec3::conv(vec3(rot) / vec3(ref.rot)), vec3::conv(vec3(size) / vec3(ref.size))); }
	Transform& operator-= (const Transform &ref) { pos -= ref.pos; rot -= ref.rot; size -= ref.size; return *this; }
	Transform& operator+= (const Transform &ref) { pos += ref.pos; rot += ref.rot; size += ref.size; return *this; }
	Transform& operator*= (const Transform &ref) { pos = vec3::conv(vec3(pos) * ref.pos); rot = vec3::conv(vec3(rot) * ref.rot); size = vec3::conv(vec3(size) * ref.size); return *this; }
	Transform& operator/= (const Transform &ref) { pos = vec3::conv(vec3(pos) / ref.pos); rot = vec3::conv(vec3(rot) / ref.rot); size = vec3::conv(vec3(size) / ref.size); return *this; }

	static Transform zero(void){return Transform(Dvec3(0,0,0), Dvec3(0,0,0), Dvec3(1,1,1));}

	Dvec3	pos;
	Dvec3	rot;
	Dvec3	size;
	D3DXQUATERNION	quatenion;
private:
};

#endif // !TRANSFORM_H
