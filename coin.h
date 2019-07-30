/*****************************************************************************
coin.h
Aythor	: ���@��
Data	: 2017_06_08
=============================================================================
Updata

*****************************************************************************/
#ifndef COIN_H
#define COIN_H

#include "scene.h"
#include "sceneModel.h"

//////////////////////////////////////////////////////////////////////////////
//�O���錾
//////////////////////////////////////////////////////////////////////////////
class Scene;
class SceneModel;
class Collision;

//////////////////////////////////////////////////////////////////////////////
//Kamome�N���X��`
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

	//�Q�b�^�[
	float	getLen(void){return mLen;}
	auto	getCollisionList(void) { return mCollisionList; }

	//�Z�b�^�[
	static Coin	*create(D3DXVECTOR3 pos);

private:
	list<Collision*>	mCollisionList;	//�R���W�������X�g
	float	mLen;	//�R���W�������a
};

#endif // !KAMOME_H
