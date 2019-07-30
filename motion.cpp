/*****************************************************************************
motion.cpp
Aythor	: ���@��
Data	: 2017_09_06
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
// �w�b�_�[�C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include <stdarg.h>
#include "main.h"
#include "transform.h"
#include "collision.h"
#include "scene.h"
#include "sceneModel.h"
#include "convenient.h"
#include "load.h"
#include "modelData.h"
#include "motion.h"

/*
##############################################################################
 Parts class
##############################################################################
*/
void MotionModel::playMotion(string motionName)
{
	for (const auto& motion : mMotionDataList)
	{
		if (motion->getMotionName() == motionName)
		{
			mMotionPlayback = motion;
			mMotionPlayback->init();
			mNumFrame = 0;
			return;
		}
	}

	MessageBox(NULL, "���݂��Ȃ����[�V����", "error", MB_OK);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Parts::update
//�Ԃ�l	: 
//����		: ���f���̃p�[�c�X�V
//////////////////////////////////////////////////////////////////////////////
void MotionModel::update(void)
{
	if (mMotionPlayback == NULL)
		return;
	if (mMotionPlayback->makeMotionPlay() == false)
		return;
	
	mMotionPlayback->calcKeyframe(mPartsList, mNumFrame);
	mNumFrame++;

	if (mNumFrame > mMotionPlayback->getFrameRate())
	{
		mMotionPlayback->addKeyframeList();
		mNumFrame = 0;
	}
}

Scene * MotionModel::findModelParts(string modelName)
{
	if (modelName == "NULL")
		return NULL;
	
	for (const auto& scene : mPartsList)
	{
		if (scene->getMyName() == modelName)
			return scene;
	}

	return NULL;
}

void MotionModel::setDefaultTransform(Scene * scene)
{
	scene->setTransform(mDefaultPosture[scene->getMyName()]);
	for (auto child : *scene->getChildernList())
		setDefaultTransform(child);
}

/*
##############################################################################
ModelParts class
##############################################################################
*/
void MotionModel::loadModelData(string fileDir, Scene::OBJ_TYPE type)
{
	FILE	*fp = fopen(fileDir.c_str(), "r");
	if (fp == NULL)
	{
		MessageBox(NULL, "�����ȃ��f���t�@�C��", "error", MB_OK);
		return;
	}

	string statement = "\0";

#pragma omp parallel
	{
		while (statement != "EOF")
		{
			statement = Load::findWord(fp);

#pragma omp section
			{
				if (statement == "PARTS_NAME")
				{
					auto scene = SceneModel::create(Load::findWord(fp));
					mPartsList.push_back(scene);
					scene->setObjType(type);
				}
			}

			if (statement == "SET_MODEL")
			{
				string	order = "\0";
				string	partsName = Load::findWord(fp);
				auto	partsToEdit = findModelParts(partsName);
				Load::findWord(fp);

				while (order != "}")
				{
					order = Load::findWord(fp);
					string	ope;

					if (order == "COLLISION_BOX")
						partsToEdit->setCollision(CollisionManager::loadCollisionBox(fp, partsToEdit));
					if (order == "COLLISION_BALL")
						partsToEdit->setCollision(CollisionManager::loadCollisionBall(fp, partsToEdit));

#pragma omp section
					{
						if (order == "parent")
						{
							string parent;
							Load::operatorSelectString(fp, parent);
							partsToEdit->setParent(findModelParts(parent));
							if (partsToEdit->getParent() == NULL)
								mMainParts = partsToEdit;
						}
					}

#pragma omp section
					{
						if (order == "pos")
							Load::operatorSelectFloat3(fp, partsToEdit->getTransformAdd()->pos);
					}

#pragma omp section
					{
						if (order == "rot")
							Load::operatorSelectFloat3(fp, partsToEdit->getTransformAdd()->rot);
					}

#pragma omp section
					{
						if (order == "size")
							Load::operatorSelectFloat3(fp, partsToEdit->getTransformAdd()->size);
					}
				}
			}
		}
	}

	mDefaultPosture[mMainParts->getMyName()] = mMainParts->getTransform();
	for (const auto& scene : *mMainParts->getChildernList())
		mDefaultPosture[scene->getMyName()] = scene->getTransform();

	fclose(fp);
}

void MotionModel::stopMotion()
{
	if (mMotionPlayback == NULL)
		return;

	mMotionPlayback->makeMotionPlay() = false; 
	mMotionPlayback = NULL;
	mMainParts->setTransform(mDefaultPosture[mMainParts->getMyName()]);
	setDefaultTransform(mMainParts);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: ModelParts::loadMotionData
//�Ԃ�l	: 
//����		: ���[�V�����f�[�^�ǂݍ���
//////////////////////////////////////////////////////////////////////////////
void MotionModel::loadMotionData(string modelDir, string motionDir, Scene::OBJ_TYPE type)
{
	loadModelData(modelDir, type);
	mMotionDataList = MotionData::loadMotionData(motionDir);
}

/*
##############################################################################
MotionData class
##############################################################################
*/
//////////////////////////////////////////////////////////////////////////////
//�֐���	: MotionData::create
//�Ԃ�l	: 
//����		: ���[�V�����f�[�^������L�[�t���[��������
//////////////////////////////////////////////////////////////////////////////
MotionData * MotionData::create(string motionName, list<Scene*> partsList)
{
	MotionData	*motionData = new MotionData;

	motionData->mMotionName = motionName;
	motionData->mKeyframeList.push_back(Keyframe::create(partsList));

	return motionData;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: MotionData::loadMotionData
//�Ԃ�l	: 
//����		: ���[�V�����f�[�^�ǂݍ���
//////////////////////////////////////////////////////////////////////////////
list<MotionData *> MotionData::loadMotionData(string fileDir)
{
	FILE	*fp = fopen(fileDir.c_str(), "r");
	if (fp == NULL)
		MessageBox(NULL, "���[�V�����t�@�C�����ǂݍ��߂܂���ł���", "error", MB_OK);

	list<MotionData*> motionList;
	string statement = "\0";

#pragma omp parallel
	{
		while (statement != "EOF")
		{
			statement = Load::findWord(fp);

			if (statement == "MOTION")
			{
				auto	motionData = new MotionData;
				string	setting = "\0";
				motionData->mMotionName = Load::findWord(fp);
				Load::findWord(fp);

				while (setting != "}")
				{
					setting = Load::findWord(fp);
					if (setting == "play")
						fscanf(fp, "\t= %d", &motionData->mPlayMode);

					if (setting == "SET_KEY_FRAME")
					{
						string order = "\0";
						Keyframe keyFrame;

						while (order != "}")
						{
							order = Load::findWord(fp);

							if (order == "frame")
								Load::operatorSelectInt2(fp, &keyFrame.frameRate());


							if (order == "KEY")
							{
								string assign = "\0";
								string modelName = Load::findWord(fp);
								Transform trans;

								while (assign != "}")
								{
									assign = Load::findWord(fp);
#pragma omp section
									{
										if (assign == "pos")
											Load::operatorSelectFloat3(fp, trans.pos);
									}

#pragma omp section
									{
										if (assign == "rot")
											Load::operatorSelectFloat3(fp, trans.rot);
									}

#pragma omp section
									{
										if (assign == "size")
											Load::operatorSelectFloat3(fp, trans.size);
									}
								}
								keyFrame.setKey(modelName, trans);
							}
						}
						motionData->mKeyframeList.push_back(keyFrame);
					}
				}
				motionList.push_back(motionData);
			}
		}
	}
	fclose(fp);
	return motionList;
}

void MotionData::calcKeyframe(list<Scene*> partsList, int numFrame)
{
	if (mMakeMotionPlay == false)
		return;

	auto	key = mKeyframeList[0].getKey();
	auto	nextKey = mKeyframeList[0].getKey();
	if (mNumKeyframeList >= mKeyframeList.size() - 1)
	{
		if (mPlayMode == ONECE)
		{
			mNumKeyframeList = 0;
			mMakeMotionPlay = false;
			return;
		}
		if (mPlayMode == LOOP && mNumKeyframeList > mKeyframeList.size() - 1)
		{
			mNumKeyframeList = 0;
			key = mKeyframeList[mNumKeyframeList].getKey();
			nextKey = mKeyframeList[mNumKeyframeList + 1].getKey();
		}
		else
		{
			key = mKeyframeList[mNumKeyframeList].getKey();
			nextKey = mKeyframeList[0].getKey();
		}
	}
	else
	{
		key = mKeyframeList[mNumKeyframeList].getKey();
		nextKey = mKeyframeList[mNumKeyframeList + 1].getKey();
	}

	float		rate = (float)numFrame / mKeyframeList[mNumKeyframeList].frameRate();

#pragma omp parallel for
	for (const auto& scene : partsList)
	{
		scene->setPos(key[scene->getMyName()].pos * (1.f - rate) + nextKey[scene->getMyName()].pos * rate);
		scene->setRot(key[scene->getMyName()].rot * (1.f - rate) + nextKey[scene->getMyName()].rot * rate);
		scene->setSize(key[scene->getMyName()].size * (1.f - rate) + nextKey[scene->getMyName()].size * rate);
	}
}

void MotionData::calcMotion(Scene * part, unordered_map<string, Transform> key, unordered_map<string, Transform> nextKey, float rate)
{
	part->setPos(key[part->getMyName()].pos * (1.f - rate) + nextKey[part->getMyName()].pos * rate);
	part->setRot(key[part->getMyName()].rot * (1.f - rate) + nextKey[part->getMyName()].rot * rate);
	part->setSize(key[part->getMyName()].size * (1.f - rate) + nextKey[part->getMyName()].size * rate);

	for (auto child : *part->getChildernList())
	{
		calcMotion(child, key, nextKey, rate);
	}
}

/*
##############################################################################
Keyframe class
##############################################################################
*/
//////////////////////////////////////////////////////////////////////////////
//�֐���	: Keyframe::create
//�Ԃ�l	: 
//����		: �L�[�t���[������
//////////////////////////////////////////////////////////////////////////////
Keyframe Keyframe::create(list<Scene*> partsList, int frameRate)
{
	Keyframe	keyFrame;

	keyFrame.mFrameRate = frameRate;

#pragma omp parallel for
	for (const auto& part : partsList)
		keyFrame.mKey[part->getMyName()] = part->getTransform();

	return keyFrame;
}

void Keyframe::setPartsTransform(list<Scene*> partsList)
{
#pragma omp parallel for
	for (const auto& parts : partsList)
		parts->setTransform(mKey[parts->getMyName()]);
}

void Keyframe::setKeyValue(list<Scene*> partsList)
{
#pragma omp parallel for
	for (const auto& part : partsList)
		mKey[part->getMyName()] = part->getTransform();
}
