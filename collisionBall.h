/*****************************************************************************
collisionBall.h
Aythor	: ���@��
Data	: 2017_07_13
=============================================================================
Updata

*****************************************************************************/
#ifndef	COLLISION_BALL_H
#define	COLLISION_BALL_H
//////////////////////////////////////////////////////////////////////////////
//�C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "collision.h"

//////////////////////////////////////////////////////////////////////////////
//�O���錾
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
	//�v���g�^�C�v�錾
	void setMtx(void);

	//�ϐ��錾
#ifdef _DEBUG
	static LPDIRECT3DTEXTURE9	mTexBuf[2];	//�e�N�X�`���o�b�t�@
	LPD3DXMESH		mMesh;			//���b�V�����
	D3DMATERIAL9	mMat;			//�}�e���A�����
#endif // _DEBUG
	Dvec3			mRelativePos;	//���W
	float			mLen;			//���a
};

#endif // !COLLISION_BALL_H