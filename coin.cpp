/*****************************************************************************
coin.cpp
Aythor	: ���@��
Data	: 2017_06_08
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "camera.h"
#include "scene.h"
#include "sceneModel.h"
#include "mesh.h"
#include "meshField.h"
#include "input.h"
#include "collision.h"
#include "collisionBox.h"
#include "collisionBall.h"
#include "coin.h"
#include "manager.h"

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Coin::inint
//�Ԃ�l	: 
//����		: ������
//////////////////////////////////////////////////////////////////////////////
HRESULT Coin::init(void)
{
	HRESULT hr;		//�������ǂ���

	//�ϐ�������
	mLen = 5.f;

	//���f���ǂݍ���
	hr = loadModel("data/model/coin.x");

	SceneModel::init();
	Scene::setObjType(OBJECT);

	mCollisionList.push_back(CollisionBox::create(this, Dvec3(9.7f, 10.9f, 0.f), Dvec3(100.5f, 22.f, 100.f)));
	mCollisionList.push_back(CollisionBox::create(this, Dvec3(-9.6f, 10.6f, 0.f), Dvec3(10.9f, 21.7f, 10.f)));

	mTransform.rot = Dvec3(1, 0, 0);

	return hr;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Coin::uninit
//�Ԃ�l	: 
//����		: ������
//////////////////////////////////////////////////////////////////////////////
void Coin::uninit(void)
{
	SceneModel::uninit();

	for (auto it = mCollisionList.begin(); it != mCollisionList.end(); ++it)
	{
		auto collision = *it;
		collision->uninit();
		delete collision;
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Coin::update
//�Ԃ�l	: 
//����		: �X�V
//////////////////////////////////////////////////////////////////////////////
void Coin::update(void)
{
	for (auto it = mCollisionList.begin(); it != mCollisionList.end(); ++it)
	{
		auto collision = *it;
		collision->update();
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Coin::draw
//�Ԃ�l	: 
//����		: �`��
//////////////////////////////////////////////////////////////////////////////
void Coin::draw(void)
{
	SceneModel::draw();

	for (auto it = mCollisionList.begin(); it != mCollisionList.end(); ++it)
	{
		auto collision = *it;
		collision->draw();
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Coin::create
//�Ԃ�l	: 
//����		: ����
//////////////////////////////////////////////////////////////////////////////
Coin * Coin::create(D3DXVECTOR3 pos)
{
	Coin *coin;

	coin = new Coin;

	coin->init();
	coin->mTransform.pos = pos;

	return coin;
}