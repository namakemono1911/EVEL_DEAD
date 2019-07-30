/*****************************************************************************
collision.cpp
Aythor	: ���@��
Data	: 2017_07_13
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "collision.h"
#include "collisionBox.h"
#include "collisionBall.h"
#include "load.h"
#include "sceneModel.h"

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Collision::create()
//�Ԃ�l	: 
//����		: ����
//////////////////////////////////////////////////////////////////////////////
Collision * Collision::create(Collision * collision)
{
	Collision *col;

	col = collision;
	col->init();

	return col;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Collision::faceScrachVec()
//�Ԃ�l	: 
//����		: �ǂ���x�N�g���v�Z
//////////////////////////////////////////////////////////////////////////////
Dvec3 Collision::faceScrachVec(Dvec3 moveVec, Dvec3 normal)
{
	D3DXVECTOR3 normal_n;
	D3DXVec3Normalize(&normal_n, &normal);
	Dvec3 vec = moveVec - D3DXVec3Dot(&moveVec, &normal_n) * normal_n;
	return vec;
}

/*
###################################################################################################################################
 CollisionManager class
###################################################################################################################################
*/
//////////////////////////////////////////////////////////////////////////////
//�֐���	: CollisionManager::loadCollisionFile()
//�Ԃ�l	: 
//����		: �R���W�����t�@�C������ݒ�ǂݍ���
//////////////////////////////////////////////////////////////////////////////
void CollisionManager::loadCollisionFile(FILE * fp, Scene* pearent)
{
	string statement = "\0";
	while ((statement = Load::findWord(fp)) != "EOF")
	{
		if (statement == "COLLISION_BOX")
			loadCollisionBox(fp, pearent);

		if (statement == "COLLISION_BALL")
			loadCollisionBall(fp, pearent);
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: CollisionManager::updateAll()
//�Ԃ�l	: 
//����		: �S�X�V
//////////////////////////////////////////////////////////////////////////////
void CollisionManager::updateAll(void)
{
#pragma	omp	paralell for
	for (auto it = mCollisionList.begin(); it != mCollisionList.end(); ++it)
	{
		auto col = *it;

		col->update();
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: CollisionManager::uninitAll()
//�Ԃ�l	: 
//����		: �S�I��
//////////////////////////////////////////////////////////////////////////////
void CollisionManager::uninitAll(void)
{
#pragma	omp	paralell for
	for (auto it = mCollisionList.begin(); it != mCollisionList.end(); ++it)
	{
		auto col = *it;

		col->uninit();
		delete col;
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: CollisionManager::drawAll()
//�Ԃ�l	: 
//����		: �S�`��
//////////////////////////////////////////////////////////////////////////////
void CollisionManager::drawAll(void)
{
#pragma	omp	paralell for
	for (auto it = mCollisionList.begin(); it != mCollisionList.end(); ++it)
	{
		auto col = *it;

		col->draw();
	}
}

bool CollisionManager::hitByRayAll(Dvec3 *outCrossPos, Dvec3 *outAxis, Dvec3 pos, Dvec3 ray)
{
	auto shortDistance = vec3::lenVector(ray);
	Dvec3 crossPos;
	Dvec3 axis;
	bool isHit = false;

	for (auto col : mCollisionList)
	{
		if (col->hitByRay(&crossPos, &axis, pos, ray))
		{
			auto crossLen = vec3::lenVector(crossPos - pos);
			if (crossLen < shortDistance)
			{
				if (outCrossPos != NULL)
					*outCrossPos = crossPos;

				if (outAxis != NULL)
					*outAxis = axis;

				shortDistance = crossLen;
				isHit = true;
			}
		}
	}

	return isHit;
}

CollisionBox* CollisionManager::loadCollisionBox(FILE * fp, Scene* pearent)
{
	auto box = CollisionBox::create(pearent, Dvec3(0, 0, 0), Dvec3(0, 0, 0));
	box->assignmentTarget(fp);
	return box;
}

CollisionBall* CollisionManager::loadCollisionBall(FILE * fp, Scene* pearent)
{
	auto ball = CollisionBall::create(pearent, Dvec3(0, 0, 0), 0.f);
	ball->assignmentTarget(fp);
	return ball;
}
