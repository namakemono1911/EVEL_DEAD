/*****************************************************************************
scene3D.h
Aythor	: 上野　匠
Data	: 2017_04_20
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//ヘッダーインクルード
//////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <list>
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "sceneModel.h"
#include "directory.h"
#include "load.h"
#include "convenient.h"

//////////////////////////////////////////////////////////////////////////////
//関数名	: SceneModel::init
//返り値	: 
//説明		: 初期化
//////////////////////////////////////////////////////////////////////////////
HRESULT SceneModel::init(void)
{
	mParent = NULL;
	setObjType(OBJECT);

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: SceneModel::uninit
//返り値	: 
//説明		: 終了
//////////////////////////////////////////////////////////////////////////////
void	SceneModel::uninit	( void )
{
	//モデル情報終了
	mData->uninit();
	delete mData;

	//リリース
	release();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: SceneModel::update
//返り値	: 
//説明		: 更新
//////////////////////////////////////////////////////////////////////////////
void	SceneModel::update	( void )
{
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: SceneModel::draw
//返り値	: 
//説明		: 描画
//////////////////////////////////////////////////////////////////////////////
void	SceneModel::draw	( void )
{
	mData->draw(mMatrix);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: SceneModel::loadModel
//返り値	: 
//説明		: モデル読み込み
//////////////////////////////////////////////////////////////////////////////
HRESULT SceneModel::loadModel(const char * fileName)
{
	//モデルデータの拡張子識別
	mData = ModelData::createModelData(fileName);

	if (mData)
		return S_OK;

	return E_FAIL;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: SceneModel::create
//返り値	: 
//説明		: 生成
//////////////////////////////////////////////////////////////////////////////
SceneModel* SceneModel::create(string modelName, Dvec3 pos)
{
	auto model = new SceneModel;
	model->loadModel(modelName.c_str());
	model->init();
	model->mMyName = modelName;
	model->mTransform.pos = pos;

	return model;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: SceneModel::createBox
//返り値	: 
//説明		: コリジョンボックス生成
//////////////////////////////////////////////////////////////////////////////
map<string, Scene*> SceneModel::loadModelData(string fileName)
{
	FILE	*fp = fopen(fileName.c_str(), "r");

	string statement = "\0";
	map<string, Scene*> modelList;

#pragma omp parallel
	{
		while (statement != "EOF")
		{
			statement = Load::findWord(fp);

#pragma omp section
			{
				if (statement == "PARTS_NAME")
				{
					string modelName = Load::findWord(fp);
					modelList[modelName] = create(modelName.c_str());
				}
			}

			if (statement == "SET_MODEL")
			{
				string	order = "\0";
				auto	model = modelList[Load::findWord(fp)];

				while (order != "}")
				{
					order = Load::findWord(fp);
					string	ope;

					if (order == "COLLISION_BOX")
						model->setCollision(model->getCollision()->loadCollisionBox(fp, model));
					if (order == "COLLISION_BALL")
						model->setCollision(model->getCollision()->loadCollisionBall(fp, model));

#pragma omp section
					{
						if (order == "parent")
						{
							string pearent;
							Load::operatorSelectString(fp, pearent);
							if (pearent == "NULL")
								continue;
							model->setParent(modelList[pearent]);
						}
					}

#pragma omp section
					{
						if (order == "pos")
							Load::operatorSelectFloat3(fp, model->getTransformAdd()->pos);
					}

#pragma omp section
					{
						if (order == "rot")
							Load::operatorSelectFloat3(fp, model->getTransformAdd()->rot);
					}

#pragma omp section
					{
						if (order == "size")
							Load::operatorSelectFloat3(fp, model->getTransformAdd()->size);
					}
				}
			}
		}
	}
	fclose(fp);
	return modelList;
}