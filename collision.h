/*****************************************************************************
collision.h
Aythor	: ���@��
Data	: 2017_07_13
=============================================================================
Updata

*****************************************************************************/
#ifndef COLLISION_H
#define COLLISION_H
//////////////////////////////////////////////////////////////////////////////
//�C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include <list>
#include <vector>
#include <string>

#define	COLLISION_BOX	(Collision::BOX)
#define COLLISION_BALL	(Collision::BALL)
#define DEFAULT_COLOR	(Dcolor(0.5f, 1.f, 0.5f, 0.5f))	//�ʏ�F
#define HIT_COLOR		(Dcolor(1.f, 0.5f, 0.5f, 0.5f))	//�q�b�g�����F

//////////////////////////////////////////////////////////////////////////////
//�N���X�錾
//////////////////////////////////////////////////////////////////////////////
class Scene;
class CollisionBox;
class CollisionBall;

class Collision
{
public:
	Collision() { mPos = Dvec3(0, 0, 0); }
	~Collision(){}

	typedef enum
	{
		BOX = 0,
		BALL,
		MAX
	}TYPE;

	virtual HRESULT init(void) { return S_OK; };
	virtual void uninit(void) {};
	virtual void update(void) {};
	virtual void draw(void) {};
	virtual Dvec3	getPos(){return mPos;}
	virtual Dvec3*	getPosAddr(){return &mPos;}
	virtual bool	hitByRay(Dvec3 *outCrossPos, Dvec3 *outAxis, Dvec3 pos, Dvec3 ray) = 0;

	virtual void		assignmentTarget(FILE* fp) = 0;
	static Dvec3	faceScrachVec(Dvec3 moveVec, Dvec3 normal);

	static Collision	*create(Collision *collision);
	auto	getType() { return mType; }

protected:
	Scene*	mPearents;		//�e�I�u�W�F�N�g
	Dvec3	mPos;			//���΍��W
	TYPE	mType;			//�R���W�����^�C�v

private:

};

class CollisionManager
{
public:
	CollisionManager() {}
	~CollisionManager() {}

	void	loadCollisionFile(FILE * fp, Scene* pearent);
	void	updateAll(void);
	void	uninitAll(void);
	void	setCollision(Collision* col) { mCollisionList.push_back(col); }
	void	drawAll(void);

	bool	hitByRayAll(Dvec3 *outCrossPos, Dvec3 *outAxis, Dvec3 pos, Dvec3 ray);
	auto	getCollisionList(void) { return &mCollisionList; }

	static CollisionBox* loadCollisionBox(FILE * fp, Scene* pearent);
	static CollisionBall* loadCollisionBall(FILE * fp, Scene* pearent);

private:
	list<Collision*>	mCollisionList;

};

#endif // !COLLISION_H
