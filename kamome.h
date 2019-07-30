/*****************************************************************************
kamome.h
Aythor	: ���@��
Data	: 2017_06_08
=============================================================================
Updata

*****************************************************************************/
#ifndef KAMOME_H
#define KAMOME_H

#include "scene.h"
#include "sceneModel.h"

//////////////////////////////////////////////////////////////////////////////
//�O���錾
//////////////////////////////////////////////////////////////////////////////
class Scene;
class SceneModel;

//////////////////////////////////////////////////////////////////////////////
//Kamome�N���X��`
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

	//�Q�b�^�[
	float	getLen(void){return mLen;}

	//�Z�b�^�[
	static Kamome	*create(D3DXVECTOR3 pos);

private:
	vec3	mMoveVec;	//�i�s�����x�N�g��
	float	mSpd;		//�ړ����x
	float	mLen;		//�R���W�������a
};

#endif // !KAMOME_H
