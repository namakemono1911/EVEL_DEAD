/*****************************************************************************
kamome.h
Aythor	: 上野　匠
Data	: 2017_06_08
=============================================================================
Updata

*****************************************************************************/
#ifndef KAMOME_H
#define KAMOME_H

#include "scene.h"
#include "sceneModel.h"

//////////////////////////////////////////////////////////////////////////////
//前方宣言
//////////////////////////////////////////////////////////////////////////////
class Scene;
class SceneModel;

//////////////////////////////////////////////////////////////////////////////
//Kamomeクラス定義
//////////////////////////////////////////////////////////////////////////////
class Kamome : public SceneModel
{
public:
	Kamome(){}
	~Kamome(){}

	HRESULT	init(void);
	void	uninit(void);
	void	update(void);
	void	draw(void);

	//ゲッター
	float	getLen(void){return mLen;}

	//セッター
	static Kamome	*create(D3DXVECTOR3 pos);

private:
	vec3	mMoveVec;	//進行方向ベクトル
	float	mSpd;		//移動速度
	float	mLen;		//コリジョン半径
};

#endif // !KAMOME_H
