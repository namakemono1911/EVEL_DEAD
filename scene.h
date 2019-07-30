/*****************************************************************************
scene.cpp
Aythor	: ���@��
Data	: 2017_05_10
=============================================================================
Updata

*****************************************************************************/
#ifndef _SCENE_H_
#define _SCENE_H_
//////////////////////////////////////////////////////////////////////////////
// �C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include <list>
#include <vector>
#include <string>
#include <map>
#include "transform.h"
#include "collision.h"
#include "collisionBall.h"
#include "collisionBox.h"

//////////////////////////////////////////////////////////////////////////////
// �萔��`
//////////////////////////////////////////////////////////////////////////////
#define	MAX_OBJ			(100)
#define PRIORITY		(5)
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//2D�|���S���ݒ�
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_NORMAL | D3DFVF_TEX1)	//3D�|���S���ݒ�

//////////////////////////////////////////////////////////////////////////////
// �\���̒�`
//////////////////////////////////////////////////////////////////////////////
//2D�|���S���`�ʗp�\����
typedef struct
{
	Dvec3		 pos;		//���W
	float		 rhw;
	D3DCOLOR	 color;		//���_�F
	D3DXVECTOR2	tex;		//�e�N�X�`�����W
}VERTEX2D;

//3D�|���S���`��p�\����
typedef struct
{
	Dvec3		pos;		//���W
	Dvec3		nor;		//�@��
	D3DCOLOR	color;		//���_���W
	D3DXVECTOR2	tex;		//�e�N�X�`�����W
}VERTEX3D;

//////////////////////////////////////////////////////////////////////////////
// �I�u�W�F�N�g�N���X
//////////////////////////////////////////////////////////////////////////////
class Collision;
class Transform;

class	Scene
{
public:
	typedef enum
	{
		OBJECT = 0,
		FIELD,
		NONE,			//����
		PLAYER,
		ZOMBIE,
		OTHER,
		CAMERA,
		UI,
		OBJ_TYPE_MAX
	}OBJ_TYPE;		//�I�u�W�F�N�g�^�C�v

	typedef enum
	{
		PRIME_FIRST = 0,
		PRIME_SECOND,
		PRIME_THIRD,
		PRIME_FORTH,
		PRIME_FIFTH,
		PRIME_MAX,
	}PRIME;

	Scene(UINT priolity = PRIME_THIRD);
	virtual	~Scene();

	virtual	HRESULT	init(void){return S_OK;}
	virtual	void	uninit(void) = 0;
	virtual	void	update(void) = 0;
	virtual	void	draw(void) = 0;

	static	void	uninitAll(void);
	static	void	updateAll(void);
	static	void	drawAll(void);
	static	void	releaseAll(void);
	void	release(void);

	//�Q�b�^�[
	static auto		getSceneList(int prime) { return mSceneList[prime]; }
	static list<Scene*>		getTypeList(OBJ_TYPE);
	OBJ_TYPE		getObjType(void);
	Transform		getTransform(void) { return mTransform; }
	Transform		*getTransformAdd(void) { return &mTransform; }
	auto			getPos(void) { return mTransform.pos; }
	auto			getPosAddr(void) { return &mTransform.pos; }
	auto			getRot(void) { return mTransform.rot; }
	auto			getRotAddr(void) { return &mTransform.rot; }
	auto			getSize(void){return mTransform.size;}
	auto			getSizeAddr(void) { return &mTransform.size; }
	const auto		getParent(void) { return mParent; }
	auto			getChildernList(void) { return &mChildren; }
	auto			getMatrix(void) { return mMatrix; }
	auto			getMyName(void) { return mMyName; }
	auto			getCollision(void) { return mCollision; }

	//�Z�b�^�[
	void			setObjType(OBJ_TYPE type);
	void			setTransform(Transform transform){mTransform = transform;}
	void			setPos(Dvec3 pos){mTransform.pos = pos;}
	void			setRot(Dvec3 rot){mTransform.rot = rot;}
	void			setSize(Dvec3 size){mTransform.size = size;}
	void			setChild(Scene* child);
	void			setCollision(Collision* col);
	void			setParent(Scene* pearent);
	void			setMatrix(DMtx matrix) { mMatrix = matrix; }
	void			matrixMulti(DMtx matrix) { mMatrix *= matrix; }

protected:
	//�ϐ��錾
	Dmtx					mMatrix;				//�s��
	Transform				mTransform;				//���W�A��]�A�g�k
	Scene*					mParent;				//�e�I�u�W�F�N�g
	list<Scene*>			mChildren;				//�q�I�u�W�F�N�g
	string					mMyName;				//�I�u�W�F�N�g�̖��O
	CollisionManager*		mCollision;				//�R���W�����}�l�[�W��

#ifdef _DEBUG
	string					mProcessTimeText;	//��������
	int						mNumFrame = 15;			//�t���[����
#endif // _DEBUG

private:
	//�v���g�^�C�v�錾
	static void			RunUninitOneByOne(const list<Scene*> scene);
	static void			RunUpdateOneByOne(const list<Scene*> scene);
	static void			RunDrawOneByOne(const list<Scene*> scene);
	static void			RunEraseOneByOne(list<Scene*> &scene);
	static void			RunDrawCollision(const list<Scene*> scene);

	//�ϐ��錾
	static	list<Scene*>	mSceneList[PRIME_MAX];	//�e�I�u�W�F�N�g��ۑ�

	int						mID;				//�C���f�b�N�X�i���o�[
	OBJ_TYPE				mType;				//�I�u�W�F�N�g�^�C�v
	bool					mDelete;			//�폜�t���O

};

#endif
