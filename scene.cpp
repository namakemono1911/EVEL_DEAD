/*****************************************************************************
meshField.cpp
Aythor	: 上野　匠
Data	: 2017_05_10
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
// ヘッダーインクルード
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "convenient.h"
#include "scene.h"
#include "renderer.h"
#include "imgui.h"

//////////////////////////////////////////////////////////////////////////////
// マクロ定義
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// 構造体定義
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// 静的メンバ変数初期化
//////////////////////////////////////////////////////////////////////////////
list<Scene*>		Scene::mSceneList[PRIME_MAX];

//////////////////////////////////////////////////////////////////////////////
//関数名	: Scene::Scene()
//返り値	: 
//説明		: コンストラクタ
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

	//削除フラグ初期化
	mDelete = false;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Scene::~Scene()
//返り値	: 
//説明		: デストラクタ
//////////////////////////////////////////////////////////////////////////////
Scene::~Scene()
{
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Scene::uninitAll()
//返り値	: 
//説明		: 全終了
//////////////////////////////////////////////////////////////////////////////
void	Scene::uninitAll(void)
{
	// リストの中身をすべて終了
	for (int i = PRIME_FIRST; i < PRIME_MAX; i++)
	{
		RunUninitOneByOne(mSceneList[i]);
	}
	releaseAll();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Scene::updateAll()
//返り値	: 
//説明		: 全更新
//////////////////////////////////////////////////////////////////////////////
void	Scene::updateAll(void)
{
	//リストの中身をすべて更新
	for (int i = PRIME_FIRST; i < PRIME_MAX; i++)
	{
		RunUpdateOneByOne(mSceneList[i]);
	}

	//更新中にリリースされたものを削除
	releaseAll();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Scene::drawAll()
//返り値	: 
//説明		: 全描画
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
//関数名	: Scene::release()
//返り値	: 
//説明		: 解放
//////////////////////////////////////////////////////////////////////////////
void	Scene::release(void)
{
	mDelete = true;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Scene::RunUninitOneByOne()
//返り値	: 
//説明		: リストを一つずつ終了
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
//関数名	: Scene::RunUpdateOneByOne()
//返り値	: 
//説明		: リストを一つずつ更新
//////////////////////////////////////////////////////////////////////////////
void Scene::RunUpdateOneByOne(const list<Scene*> scene)
{
	LARGE_INTEGER freq;
	if (!QueryPerformanceFrequency(&freq))      // 単位習得
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
//関数名	: Scene::RunDrawOneByOne()
//返り値	: 
//説明		: リストの中身を一つずつ描画
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
//関数名	: Scene::RunEraseOneByOne()
//返り値	: 
//説明		: リストを一つずつ削除
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
//関数名	: Scene::RunDrawCollision()
//返り値	: 
//説明		: コリジョン全描画
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
//関数名	: Scene::releaseAll()
//返り値	: 
//説明		: 全開放
//////////////////////////////////////////////////////////////////////////////
void	Scene::releaseAll(void)
{
	//削除フラグが立っているものを削除
	for (int i = PRIME_FIRST; i < PRIME_MAX; i++)
	{
		RunEraseOneByOne(mSceneList[i]);
	}
}
/*
//////////////////////////////////////////////////////////////////////////////
//関数名	: Scene::getScene()
//返り値	:
//説明		: ポインタ取得
//////////////////////////////////////////////////////////////////////////////
Scene	*Scene::getScene(int idx, int priolity)
{
return this;
}
*/

//////////////////////////////////////////////////////////////////////////////
//関数名	: Scene::setParent()
//返り値	: 
//説明		: 親Scene設定
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
//関数名	: Scene::getTypeList()
//返り値	: 
//説明		: 指定されたタイプのシーンをリスト化して返却
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
//関数名	: Scene::setObjType()
//返り値	: 
//説明		: オブジェクトタイプ設定
//////////////////////////////////////////////////////////////////////////////
void	Scene::setObjType(OBJ_TYPE type)
{
	mType = type;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Scene::setCollision()
//返り値	: 
//説明		: コリジョン設定
//////////////////////////////////////////////////////////////////////////////
void Scene::setCollision(Collision * col)
{
	if (mCollision == NULL)
		mCollision = new CollisionManager;

	mCollision->setCollision(col);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Scene::getObjType()
//返り値	: 
//説明		: オブジェクトタイプ取得
//////////////////////////////////////////////////////////////////////////////
Scene::OBJ_TYPE	Scene::getObjType(void)
{
	return mType;
}