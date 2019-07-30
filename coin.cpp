/*****************************************************************************
coin.cpp
Aythor	: 上野　匠
Data	: 2017_06_08
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//ヘッダーインクルード
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
//関数名	: Coin::inint
//返り値	: 
//説明		: 初期化
//////////////////////////////////////////////////////////////////////////////
HRESULT Coin::init(void)
{
	HRESULT hr;		//成功かどうか

	//変数初期化
	mLen = 5.f;

	//モデル読み込み
	hr = loadModel("data/model/coin.x");

	SceneModel::init();
	Scene::setObjType(OBJECT);

	mCollisionList.push_back(CollisionBox::create(this, Dvec3(9.7f, 10.9f, 0.f), Dvec3(100.5f, 22.f, 100.f)));
	mCollisionList.push_back(CollisionBox::create(this, Dvec3(-9.6f, 10.6f, 0.f), Dvec3(10.9f, 21.7f, 10.f)));

	mTransform.rot = Dvec3(1, 0, 0);

	return hr;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Coin::uninit
//返り値	: 
//説明		: 初期化
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
//関数名	: Coin::update
//返り値	: 
//説明		: 更新
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
//関数名	: Coin::draw
//返り値	: 
//説明		: 描画
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
//関数名	: Coin::create
//返り値	: 
//説明		: 生成
//////////////////////////////////////////////////////////////////////////////
Coin * Coin::create(D3DXVECTOR3 pos)
{
	Coin *coin;

	coin = new Coin;

	coin->init();
	coin->mTransform.pos = pos;

	return coin;
}