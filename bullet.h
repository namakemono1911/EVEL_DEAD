/*****************************************************************************
bullet.h
Aythor	: ���@��
Data	: 2018_01_09
=============================================================================
Updata

*****************************************************************************/
#ifndef BULLET_H
#define	BULLET_H

#include <list>

//////////////////////////////////////////////////////////////////////////////
//�O���錾
//////////////////////////////////////////////////////////////////////////////
class Scene;
class Weapon;
class Collision;
class CollisionManager;
class CollisionBox;
class CollisionBall;
class Zombie;

//////////////////////////////////////////////////////////////////////////////
//�N���X�錾
//////////////////////////////////////////////////////////////////////////////
struct ComparisonRange
{
	Zombie*	zombie;
	float distance;
};

class Bullet
{
public:
	Bullet() {}
	~Bullet() {}

	static Bullet*	create(Dvec3 pos, Dvec3 moveVec, float bulletSpeed, float range);
	
	void	update();
	Dvec3&	pos() { return mPos; }
	Dvec3&	moveVec() { return mMoveVec; }
	float&	bulletSpeed() { return mBulletSpeed; }
	auto&	isClear() { return mIsClear; }

private:
	struct ReviewMaterial
	{
		Dvec3	crossPos;
		Dvec3	axis;
		float	distance;
	};

	bool		isHittingProcess();
	bool		lengthComparison(float* shortDistance, const float &len);
	Scene*		searchHitScene(list<Scene*> sceneList, ReviewMaterial& review);
	Zombie*		searchHitEnemy(list<Scene*> enemyList, ReviewMaterial& review);

	Dvec3	mStartPos;			//���˂��ꂽ�ʒu
	Dvec3	mPos;				//�ʒu
	Dvec3	mMoveVec;			//�����x�N�g��
	float	mBulletSpeed;		//�e��
	float	mEffectiveRange;	//�L���˒�
	bool	mIsClear;			//�폜�t���O

};

#endif // !BULLET_H
