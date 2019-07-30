/*****************************************************************************
coin.h
Aythor	: 上野　匠
Data	: 2017_06_08
=============================================================================
Updata

*****************************************************************************/
#ifndef COIN_H
#define COIN_H

#include "scene.h"
#include "sceneModel.h"

//////////////////////////////////////////////////////////////////////////////
//前方宣言
//////////////////////////////////////////////////////////////////////////////
class Scene;
class SceneModel;
class Collision;

//////////////////////////////////////////////////////////////////////////////
//Kamomeクラス定義
//////////////////////////////////////////////////////////////////////////////
class Coin : public SceneModel
{
public:
	Coin(){}
	~Coin(){}

	HRESULT	init(void);
	void	uninit(void);
	void	update(void);
	void	draw(void);

	//ゲッター
	float	getLen(void){return mLen;}
	auto	getCollisionList(void) { return mCollisionList; }

	//セッター
	static Coin	*create(D3DXVECTOR3 pos);

private:
	list<Collision*>	mCollisionList;	//コリジョンリスト
	float	mLen;	//コリジョン半径
};

#endif // !KAMOME_H
