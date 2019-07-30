/*****************************************************************************
bullet.cpp
Aythor	: ���@��
Data	: 2018_01_09
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "scene.h"
#include "weapon.h"
#include "collision.h"
#include "collisionBox.h"
#include "collisionBall.h"
#include "zombie.h"
#include "bullet.h"
#include "sceneModel.h"
#include "stamp3D.h"
#include "textureManager.h"

#define	BULLET_MARK_SIZE	(Dvec3(1, 1, 1))
#define BLOOD_SIZE			(Dvec3(10, 10, 10))
#define BULLET_MARK_TEX		("bulletMark.png");

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Bullet::create
//�Ԃ�l	: 
//����		: �e����
//////////////////////////////////////////////////////////////////////////////
Bullet * Bullet::create(Dvec3 pos, Dvec3 moveVec, float bulletSpeed, float range)
{
	auto bullet = new Bullet;
	bullet->mStartPos = pos;
	bullet->mPos = pos;
	bullet->mMoveVec = moveVec;
	bullet->mBulletSpeed = bulletSpeed;
	bullet->mEffectiveRange = range;
	bullet->mIsClear = false;
	return bullet;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Bullet::update
//�Ԃ�l	: 
//����		: �X�V
//////////////////////////////////////////////////////////////////////////////
void Bullet::update()
{
	if (isHittingProcess())
	{
		mIsClear = true;
		return;
	}

	mPos += mMoveVec * mBulletSpeed;
	if ((float)D3DXVec3Length(&Dvec3(mPos - mStartPos)) > mEffectiveRange)
		mIsClear = true;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Bullet::isHittingProcess
//�Ԃ�l	: 
//����		: �e���������Ă����珈��
//////////////////////////////////////////////////////////////////////////////
bool Bullet::isHittingProcess()
{
	ReviewMaterial	objectReview;
	objectReview.distance = mBulletSpeed;

	auto nearScene = searchHitScene(Scene::getTypeList(Scene::OBJECT), objectReview);

	ReviewMaterial	enemyReview;
	enemyReview.distance = mBulletSpeed;
	auto hitZombies = searchHitEnemy(Scene::getTypeList(Scene::ZOMBIE), enemyReview);

	if (objectReview.distance < enemyReview.distance)
	{
		if (nearScene != NULL)
		{
			Dvec3 pos = objectReview.crossPos + objectReview.axis * 0.01f;
			auto rotx = (float)vec3::angleVector(vec3(objectReview.axis.x, 0, objectReview.axis.z), vec3(0, 0, 1)) + PI;
			auto roty = (float)vec3::angleVector(objectReview.axis, vec3(objectReview.axis.x, 0, objectReview.axis.z));
			if (objectReview.axis.x < 0)
				rotx *= -1;
			if (objectReview.axis.y < 0)
				roty *= -1;
			
			Stamp3D::create(60 * 30, pos, Dvec3(rotx, roty, 0), BULLET_MARK_SIZE, TextureManager::getTexture("bulletMark.png"));
			return true;
		}
	}

	if (objectReview.distance > enemyReview.distance)
	{
		if (hitZombies != NULL)
			hitZombies->addDamage(50);

		Dvec3 pos = enemyReview.crossPos + enemyReview.axis * 0.01f;
		auto stamp = Stamp3D::create(30, pos, Dvec3(0, 0, 0), BLOOD_SIZE, TextureManager::getTexture("blood.png"));
		stamp->setTextureAnimation(6, 5, 0);
		stamp->setBillboard();

		return true;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Bullet::lengthComparison
//�Ԃ�l	: 
//����		: ������r
//////////////////////////////////////////////////////////////////////////////
bool Bullet::lengthComparison(float * shortDistance, const float & len)
{
	if (*shortDistance > len)
	{
		*shortDistance = len;
		return true;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Bullet::searchHitScene
//�Ԃ�l	: 
//����		: �R���W�����ɓ��������V�[����T��
//////////////////////////////////////////////////////////////////////////////
Scene * Bullet::searchHitScene(list<Scene*> sceneList, ReviewMaterial& review)
{
	Scene* nearScene = NULL;
	for (auto scene : sceneList)
	{
		if (scene->getCollision() == NULL)
			continue;

		if (scene->getCollision()->hitByRayAll(&review.crossPos, &review.axis, mPos, mMoveVec * review.distance + mPos))
		{
			if (lengthComparison(&review.distance, D3DXVec3Length(&Dvec3(review.crossPos - mPos))))
				nearScene = scene;
		}
	}

	return nearScene;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Bullet::searchHitEnemy
//�Ԃ�l	: 
//����		: �R���W�����ɓ������Ă���G��T��
//////////////////////////////////////////////////////////////////////////////
Zombie* Bullet::searchHitEnemy(list<Scene*> enemyList, ReviewMaterial& review)
{
	Zombie*	hitZombie = NULL;
	for (auto enemy : enemyList)
	{
		auto zombie = (Zombie*)enemy;
		if (zombie->hitCheckAllParts(&review.crossPos, &review.axis, mPos, mMoveVec * review.distance + mPos))
			if (review.distance > D3DXVec3Length(&Dvec3(review.crossPos - mPos)))
				if (lengthComparison(&review.distance, D3DXVec3Length(&Dvec3(review.crossPos - mPos))))
					hitZombie = zombie;
	}

	return hitZombie;
}
