/*****************************************************************************
bullet.h
Aythor	: 上野　匠
Data	: 2018_01_09
=============================================================================
Updata

*****************************************************************************/
#ifndef BULLET_H
#define	BULLET_H

#include <list>

//////////////////////////////////////////////////////////////////////////////
//前方宣言
//////////////////////////////////////////////////////////////////////////////
class Scene;
class Weapon;
class Collision;
class CollisionManager;
class CollisionBox;
class CollisionBall;
class Zombie;

//////////////////////////////////////////////////////////////////////////////
//クラス宣言
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

	Dvec3	mStartPos;			//発射された位置
	Dvec3	mPos;				//位置
	Dvec3	mMoveVec;			//方向ベクトル
	float	mBulletSpeed;		//弾速
	float	mEffectiveRange;	//有効射程
	bool	mIsClear;			//削除フラグ

};

#endif // !BULLET_H
