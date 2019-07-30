/*****************************************************************************
vec3.cpp
Aythor	: 上野　匠
Data	: 2017_04_24
=============================================================================
Updata

*****************************************************************************/
#ifndef VEC_H
#define VEC_H

#include <d3dx9.h>

//////////////////////////////////////////////////////////////////////////////
//構造体定義
//////////////////////////////////////////////////////////////////////////////
typedef D3DXVECTOR3 Dvec3;
typedef D3DXVECTOR2 Dvec2;

//////////////////////////////////////////////////////////////////////////////
//クラス定義
//////////////////////////////////////////////////////////////////////////////
class vec3
{
public:
	vec3() {};
	vec3(float refx, float refy, float refz) { x = refx; y = refy; z = refz; }
	vec3(D3DXVECTOR3 ref) { x = ref.x; y = ref.y; z = ref.z; }
	vec3& operator= (const vec3 &ref) { x = ref.x; y = ref.y; z = ref.z; return *this; }
	const vec3 operator+ (const vec3 &ref) const { return vec3(ref.x + x, ref.y + y, ref.z + z); }
	const vec3 operator- (const vec3 &ref) const { return vec3(x - ref.x, y - ref.y, z - ref.z); }
	const vec3 operator* (const vec3 &ref) const { return vec3(ref.x * x, ref.y * y, ref.z * z); }
	const vec3 operator/ (const vec3 &ref) const { return vec3(ref.x / x, ref.y / y, ref.z / z); }
	const vec3 operator* (const float & ref) const { return vec3(ref * x, ref * y, ref * z); }
	vec3& operator+= (const vec3 &ref) { x += ref.x; y += ref.y; z += ref.z; return *this; }
	vec3& operator-= (const vec3 &ref) { x -= ref.x; y -= ref.y; z -= ref.z; return *this; }
	vec3& operator*= (const vec3 &ref) { x *= ref.x; y *= ref.y; z *= ref.z; return *this; }
	vec3& operator*= (const float &ref) { x *= ref; y *= ref; z *= ref; return *this; }
	vec3& operator*= (const double &ref) { x *= (float)ref; y *= (float)ref; z *= (float)ref; return *this; }
	vec3& operator/= (const vec3 &ref) { x /= ref.x; y /= ref.y; z /= ref.z; return *this; }

	static vec3			normalize(vec3 vec);
	static D3DXVECTOR3	Dnormalize(vec3 vec);
	static double		lenVector(vec3 vec);
	static double		innerProduct(vec3 v1, vec3 v2, vec3 point = vec3(0, 0, 0));
	static vec3			crossProduct(vec3 v1, vec3 v2, vec3 point = vec3(0, 0, 0));
	static D3DXVECTOR3	DcrossProduct(vec3 v1, vec3 v2, vec3 point = vec3(0, 0, 0));
	static double		angleVector(vec3 v1, vec3 v2);
	static double		posLen(vec3 v1, vec3 v2);
	static vec3			normalVec(vec3 point, vec3 v1, vec3 v2);
	static D3DXVECTOR3	conv(vec3 i) { return D3DXVECTOR3(i.x, i.y, i.z); }
	static vec3			ask(vec3 center, vec3 obj);
	static D3DXVECTOR3	Dask(vec3 center, vec3 obj);

	float	x;		//x座標
	float	y;		//y座標
	float	z;		//z座標
};

class vec2
{
public:
	vec2() {};
	vec2(float refx, float refy) { x = refx; y = refy; }
	vec2(D3DXVECTOR2 ref) { x = ref.x; y = ref.y; }
	vec2& operator= (const vec2 &ref) { x = ref.x; y = ref.y; return *this; }
	const vec2 operator+ (const vec2 &ref) const { return vec2(ref.x + x, ref.y + y); }
	const vec2 operator- (const vec2 &ref) const { return vec2(ref.x - x, ref.y - y); }
	const vec2 operator* (const vec2 &ref) const { return vec2(ref.x * x, ref.y * y); }
	const vec2 operator/ (const vec2 &ref) const { return vec2(ref.x / x, ref.y / y); }
	vec2& operator+= (const vec2 &ref) { x += ref.x; y += ref.y; return *this; }
	vec2& operator-= (const vec2 &ref) { x -= ref.x; y -= ref.y; return *this; }
	vec2& operator*= (const vec2 &ref) { x *= ref.x; y *= ref.y; return *this; }
	vec2& operator*= (const float &ref) { x *= ref; y *= ref; return *this; }
	vec2& operator*= (const double &ref) { x *= (float)ref; y *= (float)ref; return *this; }
	vec2& operator/= (const vec2 &ref) { x /= ref.x; y /= ref.y; return *this; }

	static vec2	normalize(vec2 vec);
	static D3DXVECTOR2 conv(vec2 vec) { return D3DXVECTOR2(vec.x, vec.y); }

	float	x;		//x座標
	float	y;		//y座標
};

#endif