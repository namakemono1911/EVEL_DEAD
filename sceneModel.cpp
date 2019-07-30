/*****************************************************************************
scene3D.h
Aythor	: ���@��
Data	: 2017_04_20
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�C���N���[�h
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
//�֐���	: SceneModel::init
//�Ԃ�l	: 
//����		: ������
//////////////////////////////////////////////////////////////////////////////
HRESULT SceneModel::init(void)
{
	mParent = NULL;
	setObjType(OBJECT);

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: SceneModel::uninit
//�Ԃ�l	: 
//����		: �I��
//////////////////////////////////////////////////////////////////////////////
void	SceneModel::uninit	( void )
{
	//���f�����I��
	mData->uninit();
	delete mData;

	//�����[�X
	release();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: SceneModel::update
//�Ԃ�l	: 
//����		: �X�V
//////////////////////////////////////////////////////////////////////////////
void	SceneModel::update	( void )
{
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: SceneModel::draw
//�Ԃ�l	: 
//����		: �`��
//////////////////////////////////////////////////////////////////////////////
void	SceneModel::draw	( void )
{
	mData->draw(mMatrix);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: SceneModel::loadModel
//�Ԃ�l	: 
//����		: ���f���ǂݍ���
//////////////////////////////////////////////////////////////////////////////
HRESULT SceneModel::loadModel(const char * fileName)
{
	//���f���f�[�^�̊g���q����
	mData = ModelData::createModelData(fileName);

	if (mData)
		return S_OK;

	return E_FAIL;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: SceneModel::create
//�Ԃ�l	: 
//����		: ����
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
//�֐���	: SceneModel::createBox
//�Ԃ�l	: 
//����		: �R���W�����{�b�N�X����
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