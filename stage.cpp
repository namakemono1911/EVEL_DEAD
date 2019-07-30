/*****************************************************************************
map.cpp
Aythor	: ���@��
Data	: 2017_11_19
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
// �w�b�_�[�C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include <list>
#include <string>
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "sceneModel.h"
#include "mesh.h"
#include "meshField.h"
#include "stage.h"
#include "object.h"
#include "save.h"
#include "load.h"
#include "meshfield.h"
#include "convenient.h"
#include "manager.h"

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Stage::init()
//�Ԃ�l	: 
//����		: ������
//////////////////////////////////////////////////////////////////////////////
HRESULT Stage::init(void)
{
	setObjType(OBJECT);

	return E_NOTIMPL;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Stage::uninit()
//�Ԃ�l	: 
//����		: �I��
//////////////////////////////////////////////////////////////////////////////
void Stage::uninit(void)
{
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Stage::update()
//�Ԃ�l	: 
//����		: �X�V
//////////////////////////////////////////////////////////////////////////////
void Stage::update(void)
{
	mMatrix = Conveni::setMatrix(mTransform.pos, mTransform.rot, mTransform.size);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Stage::draw()
//�Ԃ�l	: 
//����		: �`��
//////////////////////////////////////////////////////////////////////////////
void Stage::draw(void)
{
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Stage::draw()
//�Ԃ�l	: 
//����		: �`��
//////////////////////////////////////////////////////////////////////////////
void Stage::loadMapFile(string mapFileName)
{
	objectPlacement(mapFileName);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Stage::saveMap()
//�Ԃ�l	: 
//����		: �X�e�[�W���ۑ�
//////////////////////////////////////////////////////////////////////////////
bool Stage::saveMap(string saveDir)
{
	if (saveDir == "\0")
		return false;

	FILE *fp = fopen(saveDir.c_str(), "w");
	if (fp == NULL)
	{
		saveDir += "��ۑ��ł��܂���ł���";
		MessageBox(NULL, saveDir.c_str(), "error", MB_OK);
		return false;
	}

	//�I�u�W�F�N�g�ƃt�B�[���h�ۑ�
	saveObject(fp);
	saveField(fp);

	fclose(fp);
	MessageBox(NULL, "�ۑ�����", "���b�Z�[�W", MB_OK);

	return true;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Stage::create()
//�Ԃ�l	: 
//����		: ����
//////////////////////////////////////////////////////////////////////////////
Stage * Stage::create(void)
{
	Stage*	stage = new Stage;

	stage->init();
	stage->mMyName = "stage";

	return stage;
}

Stage * Stage::create(string fileDir)
{
	auto stage = create();

	stage->loadMapFile(fileDir);

	return nullptr;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Stage::objectPlacement()
//�Ԃ�l	: 
//����		: �I�u�W�F�N�g�z�u
//////////////////////////////////////////////////////////////////////////////
Scene* Stage::objectPlacement(string fileName)
{
	FILE	*fp = fopen(fileName.c_str(), "r");
	if (fp == NULL)
	{
		MessageBox(NULL, "�}�b�v�t�@�C����ǂݍ��߂܂���ł����B", "error", MB_OK);
		exit(1);
	}

	string	statement = "\0";
#pragma omp parallel
	{
		while ((statement = Load::findWord(fp)) != "EOF")
			settingBranch(fp, statement);
	}

	fclose(fp);
	return this;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Stage::objectSetting()
//�Ԃ�l	: 
//����		: �I�u�W�F�N�g�ݒu
//////////////////////////////////////////////////////////////////////////////
Scene * Stage::objectSetting(string objectName)
{
	auto	obj = SceneModel::create(objectName.c_str());
	mObjectList.push_back(obj);
	setChild(obj);
	return mChildren.back();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Stage::objectSetting()
//�Ԃ�l	: 
//����		: �I�u�W�F�N�g�ݒu
//////////////////////////////////////////////////////////////////////////////
void Stage::fieldSetting(MeshField * field)
{
	mFieldList.push_back(field);
	setChild(field);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Stage::saveObject()
//�Ԃ�l	: 
//����		: �I�u�W�F�N�g�ۑ�
//////////////////////////////////////////////////////////////////////////////
void Stage::saveObject(FILE * fp)
{
	//�w�b�_�[�R�����g
	fprintf(fp, "#####################################################\n");
	fprintf(fp, "# �I�u�W�F�N�g�̔z�u\n");
	fprintf(fp, "#####################################################\n");

	for (auto& scene : Scene::getTypeList(Scene::OBJECT))
	{
		//�e�L�X�g�������ݓ��e
		fprintf(fp, "SET_OBJECT %s\n{\n", scene->getMyName().c_str());

		//�ʒu���ۑ�
		Save::saveTransform(fp, scene->getTransform());

		//�R���W�������ۑ�
		Save::saveCollision(fp, *scene);

		fprintf(fp, "}\n\n");
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Stage::saveField()
//�Ԃ�l	: 
//����		: �t�B�[���h�ۑ�
//////////////////////////////////////////////////////////////////////////////
void Stage::saveField(FILE * fp)
{
	//�w�b�_�[�R�����g
	fprintf(fp, "#####################################################\n");
	fprintf(fp, "# �t�B�[���h(�n�ʁj�̔z�u\n");
	fprintf(fp, "#####################################################\n");

	//���X�g�T��
	for (auto& scene : Scene::getTypeList(Scene::FIELD))
	{
		//�����W
		auto field = (MeshField*)scene;

		if (field->getObjType() != Scene::FIELD)
			continue;

		Transform	transform = field->getTransform();
		Dcolor color = *field->getColorAddr();
		Tyle	numTyle = field->getNumTyle();
		string	texName = field->getTextureNameList()[field->getTextureId()];

		fprintf(fp, "SET_FIELD %s\n{\n", texName.c_str());

		//�ʒu���ۑ�
		fprintf(fp, "\tpos\t\t= %f %f %f\n", transform.pos.x, transform.pos.y, transform.pos.z);
		fprintf(fp, "\trot\t\t= %f %f %f\n", transform.rot.x, transform.rot.y, transform.rot.z);
		fprintf(fp, "\tsize\t= %f %f\n", field->getTyleSize().x, field->getTyleSize().y);

		//�^�C�����ۑ�
		fprintf(fp, "\tnumTyle\t= %d %d\n", numTyle.x, numTyle.y);

		//���_�F�ۑ�
		fprintf(fp, "\tcolor\t= %f %f %f %f\n", color.r, color.g, color.b, color.a);

		fprintf(fp, "}\n\n");
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Stage::objectAssignmentTarget()
//�Ԃ�l	: 
//����		: ���߂ɂ���ď���
//////////////////////////////////////////////////////////////////////////////
void Stage::objectAssignmentTarget(FILE * fp, string order, Scene * scene)
{
#pragma omp section
	{
		if (order == "pos")
			Load::operatorSelectFloat3(fp, scene->getTransformAdd()->pos);

		if (order == "rot")
			Load::operatorSelectFloat3(fp, scene->getTransformAdd()->rot);

		if (order == "size")
			Load::operatorSelectFloat3(fp, scene->getTransformAdd()->size);

		if (order == "COLLISION_BOX")
			setCollision(mCollision->loadCollisionBox(fp, scene));

		if (order == "COLLISIOIN_BALL")
			mCollision->loadCollisionBall(fp, scene);
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Stage::fieldAssignmentTarget()
//�Ԃ�l	: 
//����		: ���߂ɂ���ď���
//////////////////////////////////////////////////////////////////////////////
void Stage::fieldAssignmentTarget(FILE * fp, string order, MeshField * field)
{
#pragma omp section
	{
		if (order == "pos")
			Load::operatorSelectFloat3(fp, *field->getPosAddr());

		if (order == "rot")
			Load::operatorSelectFloat3(fp, (float*)field->getRotAddr());

		if (order == "size")
			Load::operatorSelectFloat2(fp, (float*)field->getTyleSizeAddr());

		if (order == "color")
			Load::operatorSelectFloat4(fp, (float*)field->getColorAddr());

		if (order == "numTyle")
			Load::operatorSelectInt2(fp, (int*)field->getNumTyleAd());
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Stage::stageAssignmentTarget()
//�Ԃ�l	: 
//����		: ���߂ɂ���ď���
//////////////////////////////////////////////////////////////////////////////
void Stage::stageAssignmentTarget(FILE * fp, string order)
{
#pragma omp section
	{
		if (order == "pos")
			Load::operatorSelectFloat3(fp, mTransform.pos);

		if (order == "rot")
			Load::operatorSelectFloat3(fp, mTransform.rot);

		if (order == "size")
			Load::operatorSelectFloat3(fp, mTransform.size);

		if (order == "COLLISION_BOX")
			setCollision(mCollision->loadCollisionBox(fp, this));

		if (order == "COLLISIOIN_BALL")
			mCollision->loadCollisionBall(fp, this);
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Stage::objectInstructionSearch()
//�Ԃ�l	: 
//����		: ���ߒT��
//////////////////////////////////////////////////////////////////////////////
void Stage::objectInstructionSearch(FILE * fp, Scene * scene)
{
	string order;
#pragma omp section
	{
		while ((order = Load::findWord(fp)) != "}")
			objectAssignmentTarget(fp, order, scene);
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Stage::fieldInstructionSearch()
//�Ԃ�l	: 
//����		: ���ߒT��
//////////////////////////////////////////////////////////////////////////////
void Stage::fieldInstructionSearch(FILE * fp, MeshField * field)
{
	string order;
#pragma omp section
	{
		while ((order = Load::findWord(fp)) != "}")
			fieldAssignmentTarget(fp, order, field);
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Stage::stageInstructionSearch()
//�Ԃ�l	: 
//����		: ���ߒT��
//////////////////////////////////////////////////////////////////////////////
void Stage::stageInstructionSearch(FILE * fp)
{
	string order;
#pragma omp section
	{
		while ((order = Load::findWord(fp)) != "}")
			stageAssignmentTarget(fp, order);
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Stage::setObject()
//�Ԃ�l	: 
//����		: �I�u�W�F�N�g�ݒ�
//////////////////////////////////////////////////////////////////////////////
auto Stage::setObject(FILE * fp)
{
	auto obj = objectSetting(Load::findWord(fp));
	objectInstructionSearch(fp, obj);

	return obj;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Stage::setField()
//�Ԃ�l	: 
//����		: �t�B�[���h�ݒ�
//////////////////////////////////////////////////////////////////////////////
auto Stage::setField(FILE * fp)
{
	auto	field = MeshField::create(
		Dvec3(0, 0, 0),
		Dvec2(10, 10),
		Tyle(3, 3),
		Dvec3(0, 0, 0),
		Dcolor(1, 1, 1, 1),
		Dvec2(0, 0),
		0);
	field->setTextureId(MeshField::getTextureIdFormMap(Load::findWord(fp)));

	fieldInstructionSearch(fp, field);
	fieldSetting(field);

	return field;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Stage::settingBranch()
//�Ԃ�l	: 
//����		: �X�e�[�W�ݒ�
//////////////////////////////////////////////////////////////////////////////
void Stage::setStage(FILE * fp)
{
	stageInstructionSearch(fp);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Stage::settingBranch()
//�Ԃ�l	: 
//����		: ��ޑI��
//////////////////////////////////////////////////////////////////////////////
void Stage::settingBranch(FILE * fp, string statement)
{
	if (statement == "SET_STAGE")
		 setStage(fp);

	if (statement == "SET_OBJECT")
		setObject(fp);

	if (statement == "SET_FIELD")
		setField(fp);
}
