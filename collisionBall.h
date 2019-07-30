/*****************************************************************************
collisionBall.h
Aythor	: 上野　匠
Data	: 2017_07_13
=============================================================================
Updata

*****************************************************************************/
#ifndef	COLLISION_BALL_H
#define	COLLISION_BALL_H
//////////////////////////////////////////////////////////////////////////////
//インクルード
//////////////////////////////////////////////////////////////////////////////
#include "collision.h"

//////////////////////////////////////////////////////////////////////////////
//前方宣言
//////////////////////////////////////////////////////////////////////////////
class Collision;
class Scene;

//////////////////////////////////////////////////////////////////////////////
//CollisionBall class
//////////////////////////////////////////////////////////////////////////////
class CollisionBall : public Collision
{
public:
	CollisionBall(){}
	CollisionBall(float len){mLen = len;}
	~CollisionBall(){}

	HRESULT init(void);
	void uninit(void);
	void update(void);
#ifdef _DEBUG
	void draw(void);
	static void	loadTex(void);
#endif // _DEBUG

	void	assignmentTarget(FILE* fp);

	static CollisionBall *create(Scene* pearent, Dvec3 pos, float len);
	float	getLen(){return mLen;}
	float*	getLenAddr(){return &mLen;}
	auto	getRelativePos() { return mRelativePos; }
	auto	getRelativePosAddr() { return &mRelativePos; }
	bool	hitByPoint(const Dvec3& pos);
	bool	hitByRay(Dvec3 *outCrossPos, Dvec3 *outAxis, Dvec3 pos, Dvec3 ray);

private:
	//プロトタイプ宣言
	void setMtx(void);

	//変数宣言
#ifdef _DEBUG
	static LPDIRECT3DTEXTURE9	mTexBuf[2];	//テクスチャバッファ
	LPD3DXMESH		mMesh;			//メッシュ情報
	D3DMATERIAL9	mMat;			//マテリアル情報
#endif // _DEBUG
	Dvec3			mRelativePos;	//座標
	float			mLen;			//半径
};

#endif // !COLLISION_BALL_H