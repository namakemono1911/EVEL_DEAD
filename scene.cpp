/*****************************************************************************
meshField.cpp
Aythor	: ���@��
Data	: 2017_05_10
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
// �w�b�_�[�C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "convenient.h"
#include "scene.h"
#include "renderer.h"
#include "imgui.h"

//////////////////////////////////////////////////////////////////////////////
// �}�N����`
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// �\���̒�`
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// �ÓI�����o�ϐ�������
//////////////////////////////////////////////////////////////////////////////
list<Scene*>		Scene::mSceneList[PRIME_MAX];

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Scene::Scene()
//�Ԃ�l	: 
//����		: �R���X�g���N�^
//////////////////////////////////////////////////////////////////////////////
Scene::Scene(UINT priolity)
{
	mSceneList[priolity].push_back(this);
	mTransform.pos = Dvec3(0, 0, 0);
	mTransform.size = Dvec3(1, 1, 1);
	mTransform.rot = Dvec3(0, 0, 0);
	D3DXMatrixIdentity(&mMatrix);
	mParent = NULL;
	mCollision = NULL;

	//�폜�t���O������
	mDelete = false;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Scene::~Scene()
//�Ԃ�l	: 
//����		: �f�X�g���N�^
//////////////////////////////////////////////////////////////////////////////
Scene::~Scene()
{
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Scene::uninitAll()
//�Ԃ�l	: 
//����		: �S�I��
//////////////////////////////////////////////////////////////////////////////
void	Scene::uninitAll(void)
{
	// ���X�g�̒��g�����ׂďI��
	for (int i = PRIME_FIRST; i < PRIME_MAX; i++)
	{
		RunUninitOneByOne(mSceneList[i]);
	}
	releaseAll();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Scene::updateAll()
//�Ԃ�l	: 
//����		: �S�X�V
//////////////////////////////////////////////////////////////////////////////
void	Scene::updateAll(void)
{
	//���X�g�̒��g�����ׂčX�V
	for (int i = PRIME_FIRST; i < PRIME_MAX; i++)
	{
		RunUpdateOneByOne(mSceneList[i]);
	}

	//�X�V���Ƀ����[�X���ꂽ���̂��폜
	releaseAll();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Scene::drawAll()
//�Ԃ�l	: 
//����		: �S�`��
//////////////////////////////////////////////////////////////////////////////
void	Scene::drawAll(void)
{
	for (int i = PRIME_FIRST; i < PRIME_MAX; i++)
	{
		RunDrawOneByOne(mSceneList[i]);
	}

	for (int i = PRIME_FIRST; i < PRIME_MAX; i++)
	{
		RunDrawCollision(mSceneList[i]);
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Scene::release()
//�Ԃ�l	: 
//����		: ���
//////////////////////////////////////////////////////////////////////////////
void	Scene::release(void)
{
	mDelete = true;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Scene::RunUninitOneByOne()
//�Ԃ�l	: 
//����		: ���X�g������I��
//////////////////////////////////////////////////////////////////////////////
void Scene::RunUninitOneByOne(const list<Scene*> scene)
{
	for (auto it = scene.begin(); it != scene.end(); ++it)
	{
		auto listContents = *it;

		listContents->uninit();

		if (listContents->mCollision != NULL)
		{
			listContents->mCollision->uninitAll();
			delete listContents->mCollision;
			listContents->mCollision = NULL;
		}
		listContents->mDelete = true;
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Scene::RunUpdateOneByOne()
//�Ԃ�l	: 
//����		: ���X�g������X�V
//////////////////////////////////////////////////////////////////////////////
void Scene::RunUpdateOneByOne(const list<Scene*> scene)
{
	LARGE_INTEGER freq;
	if (!QueryPerformanceFrequency(&freq))      // �P�ʏK��
		return;
	LARGE_INTEGER start, end;

	for (auto it = scene.begin(); it != scene.end(); ++it)
	{
		auto listContents = *it;

#ifdef _DEBUG
	/*	ImGui::Begin("process speed");
		QueryPerformanceCounter(&start);
		listContents->mNumFrame++;*/
#endif // _DEBUG

		D3DXMatrixIdentity(&listContents->mMatrix);
		listContents->update();
		listContents->mMatrix *= Conveni::setMatrix(listContents->mTransform);
		if (listContents->mParent != NULL)
			listContents->mMatrix *= listContents->mParent->mMatrix;

		if (listContents->mCollision != NULL)
			listContents->mCollision->updateAll();
		
#ifdef _DEBUG
		/*QueryPerformanceCounter(&end);
		if (listContents->mNumFrame >= 15)
		{
			listContents->mProcessTimeText = listContents->getMyName() + " : " +
				to_string((double)(end.QuadPart - start.QuadPart) / freq.QuadPart);
			listContents->mNumFrame = 0;
		}
		ImGui::Text(listContents->mProcessTimeText.c_str());
		ImGui::End();*/
#endif // _DEBUG
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Scene::RunDrawOneByOne()
//�Ԃ�l	: 
//����		: ���X�g�̒��g������`��
//////////////////////////////////////////////////////////////////////////////
void Scene::RunDrawOneByOne(const list<Scene*> scene)
{
#pragma omp parallel for
	for (auto it = scene.begin(); it != scene.end(); ++it)
	{
		auto listContents = *it;

		listContents->draw();
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Scene::RunEraseOneByOne()
//�Ԃ�l	: 
//����		: ���X�g������폜
//////////////////////////////////////////////////////////////////////////////
void Scene::RunEraseOneByOne(list<Scene*> &scene)
{
#pragma omp parallel for
	for (auto it = scene.begin(); it != scene.end();)
	{
		auto listContents = *it;

		if (listContents->mDelete)
		{
			if (listContents->mCollision != NULL)
			{
				listContents->mCollision->uninitAll();
			}
			delete listContents;
			it = scene.erase(it);
		}
		else
			++it;
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Scene::RunDrawCollision()
//�Ԃ�l	: 
//����		: �R���W�����S�`��
//////////////////////////////////////////////////////////////////////////////
void Scene::RunDrawCollision(const list<Scene*> scene)
{
	for (auto it = scene.begin(); it != scene.end(); ++it)
	{
		auto listContent = *it;

		if (listContent->mCollision != NULL)
			listContent->mCollision->drawAll();
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Scene::releaseAll()
//�Ԃ�l	: 
//����		: �S�J��
//////////////////////////////////////////////////////////////////////////////
void	Scene::releaseAll(void)
{
	//�폜�t���O�������Ă�����̂��폜
	for (int i = PRIME_FIRST; i < PRIME_MAX; i++)
	{
		RunEraseOneByOne(mSceneList[i]);
	}
}
/*
//////////////////////////////////////////////////////////////////////////////
//�֐���	: Scene::getScene()
//�Ԃ�l	:
//����		: �|�C���^�擾
//////////////////////////////////////////////////////////////////////////////
Scene	*Scene::getScene(int idx, int priolity)
{
return this;
}
*/

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Scene::setParent()
//�Ԃ�l	: 
//����		: �eScene�ݒ�
//////////////////////////////////////////////////////////////////////////////
void Scene::setParent(Scene * pearent)
{
	mParent = pearent;

	if (pearent == NULL)
		return;

	pearent->mChildren.push_back(this);
#pragma omp parallel for
	for (UINT i = PRIME_FIRST; i < PRIME_MAX; i++)
	{
		for (auto it = mSceneList[i].begin(); it != mSceneList[i].end(); ++it)
		{
			if (this == *it)
			{
				mSceneList[i].erase(it);
				break;
			}
		}
	}

#pragma omp parallel for
	for (UINT i = PRIME_FIRST; i < PRIME_MAX; i++)
	{
		for (auto it = mSceneList[i].begin(); it != mSceneList[i].end(); ++it)
		{
			if (mParent == *it)
			{
				++it;
				mSceneList[i].insert(it, this);
				break;
			}
		}
	}
}

void Scene::setChild(Scene * child)
{
	child->setParent(this);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Scene::getTypeList()
//�Ԃ�l	: 
//����		: �w�肳�ꂽ�^�C�v�̃V�[�������X�g�����ĕԋp
//////////////////////////////////////////////////////////////////////////////
list<Scene*> Scene::getTypeList(OBJ_TYPE type)
{
	list<Scene*> sceneList;
#pragma omp parallel for
	for (int i = 0; i < PRIME_MAX; i++)
	{
		for (auto& scene : mSceneList[i])
		{
			if (scene->getObjType() == type)
				sceneList.push_back(scene);
		}
	}

	return sceneList;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Scene::setObjType()
//�Ԃ�l	: 
//����		: �I�u�W�F�N�g�^�C�v�ݒ�
//////////////////////////////////////////////////////////////////////////////
void	Scene::setObjType(OBJ_TYPE type)
{
	mType = type;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Scene::setCollision()
//�Ԃ�l	: 
//����		: �R���W�����ݒ�
//////////////////////////////////////////////////////////////////////////////
void Scene::setCollision(Collision * col)
{
	if (mCollision == NULL)
		mCollision = new CollisionManager;

	mCollision->setCollision(col);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Scene::getObjType()
//�Ԃ�l	: 
//����		: �I�u�W�F�N�g�^�C�v�擾
//////////////////////////////////////////////////////////////////////////////
Scene::OBJ_TYPE	Scene::getObjType(void)
{
	return mType;
}