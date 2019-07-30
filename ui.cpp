/*****************************************************************************
ui.cpp
Aythor	: ���@��
Data	: 2017_07_28
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include <typeinfo.h>
#include "main.h"
#include "manager.h"
#include "convenient.h"
#include "directory.h"
#include "save.h"
#include "load.h"
#include "stage.h"
#include "camera.h"
#include "player.h"
#include "playerEdit.h"
//#include "motionEdit.h"
#include "ui.h"

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Ui::init
//�Ԃ�l	: 
//����		: ������
//////////////////////////////////////////////////////////////////////////////
HRESULT Ui::init(void)
{
	mMyName = "ui";
	mCamera = (Camera*)Scene::getTypeList(Scene::CAMERA).front();
	setObjType(UI);
	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Ui::cameraUi
//�Ԃ�l	: 
//����		: �J����UI�쐬
//////////////////////////////////////////////////////////////////////////////
void Ui::cameraUi(void)
{
	if (CollapsingHeader("Camera"))
	{
		vec3 pos = mCamera->getEye();
		vec3 at = mCamera->getAt();

		DragFloat3("at", (float*)mCamera->getAtAddr(), floatDragRate);
		SliderFloat2("angle", (float*)mCamera->getAngleAddr(), -PI, PI);
		DragFloat("length", mCamera->getLenAddr(), floatDragRate);

		Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / GetIO().Framerate, GetIO().Framerate);
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Ui::setTransformDrag
//�Ԃ�l	: 
//����		: ���W�n�̃h���b�O�ݒ�
//////////////////////////////////////////////////////////////////////////////
void Ui::setTransformDrag(Transform *transform)
{
	DragFloat3("pos", (float*)transform->pos, floatDragRate);
	DragFloat3("rot", (float*)transform->rot, floatDragRate);
	DragFloat3("size", (float*)transform->size, floatDragRate);
}

/*
#################################################################################################################################################
 MapEditorUi class
#################################################################################################################################################
*/

//////////////////////////////////////////////////////////////////////////////
//�֐���	: MapEditorUi::init
//�Ԃ�l	: 
//����		: ������
//////////////////////////////////////////////////////////////////////////////
HRESULT MapEditorUi::init(void)
{
	Camera::create(
		D3DXVECTOR3(0.f, 10.f, -30.f),
		D3DXVECTOR3(0.f, 0.f, 0.f),
		D3DXVECTOR3(0.f, 1.f, 0.f),
		-30);
	Player::create(new PlayerEdit);

	//�ϐ�������
	mNumObj = 0;
	mNumField = 0;

	auto currentDir = Load::getCurrentDir("\\data\\model");
	mNameList = Load::fileAllReferenceInDirectory(currentDir, ".x");
	mStage = Stage::create();
	auto texNameList = MeshField::getTextureNameList();
	for (auto it = texNameList.begin(); it != texNameList.end(); ++it)
		mAllTexInField += *it + '\0';

	floatDragRate = 0.01f;
	Ui::init();
	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: MapEditorUi::update
//�Ԃ�l	: 
//����		: �X�V
//////////////////////////////////////////////////////////////////////////////
void MapEditorUi::update(void)
{
	//�J����UI�쐬
	cameraUi();

	//�G�f�B�b�g�E�B���h�E����
	SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_FirstUseEver);
	Begin("Create");
	editWindow();
	End();

	//�I�u�W�F�N�g�ҏW�E�B���h�E����
	SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_FirstUseEver);
	Begin("Obje Config");
	settingWindw();
	End();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: MapEditorUi::load
//�Ԃ�l	: 
//����		: �t�@�C������ǂݍ���
//////////////////////////////////////////////////////////////////////////////
void MapEditorUi::load()
{
	string openFileDir = Load::loadingFile(NULL,
		"�f�[�^�ǂݍ���",
		".map\0",
		"MAP�t�@�C��(*.map)\0*.map\0");
	if (openFileDir == "NONE")
		return;

	reset();
	mStage->loadMapFile(openFileDir);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: MapEditorUi::save
//�Ԃ�l	: 
//����		: �ۑ�����
//////////////////////////////////////////////////////////////////////////////
void MapEditorUi::save(HWND hWnd)
{
	string	saveFileDir = Save::selectSaveFileDir(hWnd, "�f�[�^�ۑ�", ".map", "MAP�t�@�C��(*.map)\0*.map\0");
	mStage->saveMap(saveFileDir);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: MapEditorUi::reset
//�Ԃ�l	: 
//����		: ���Z�b�g
//////////////////////////////////////////////////////////////////////////////
void MapEditorUi::reset()
{
	Scene::releaseAll();
	Scene::updateAll();
	init();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: MapEditorUi::settingWindw
//�Ԃ�l	: 
//����		: �I�u�W�F�N�g�̐ݒ�ҏW�E�B���h�E�̏���
//////////////////////////////////////////////////////////////////////////////
void MapEditorUi::settingWindw(void)
{
	if (TreeNode("Stage"))
	{
		//��񑀍�
		setTransformDrag(mStage->getTransformAdd());
		ImGui::TreePop();
	}

	if (CollapsingHeader("Edit Object"))
		editObj();

	if (CollapsingHeader("Edit Field"))
		editField();

	Scene::releaseAll();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: MapEditorUi::editWindow
//�Ԃ�l	: 
//����		: �G�f�B�b�g�E�B���h�E����
//////////////////////////////////////////////////////////////////////////////
void MapEditorUi::editWindow(void)
{
	DragFloat("drag rate", &floatDragRate, 0.01f);

	//�I�u�W�F�N�g�����{�^��
	objectGenerationProcedure();

	//���b�V���t�B�[���h�����{�^��
	if (CollapsingHeader("Mesh Field"))
		if (Button("create"))
		{
			mStage->fieldSetting(MeshField::create(
				Dvec3(0, 0, 0),
				Dvec2(10, 10),
				Tyle(3, 3),
				Dvec3(0, 0, 0),
				Dcolor(1, 1, 1, 1),
				Dvec2(1, 1),
				0));
			mNumField++;
		}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: MapEditorUi::editObj
//�Ԃ�l	: 
//����		: �I�u�W�F�N�g�G�f�B�^�[�^�u�̏���
//////////////////////////////////////////////////////////////////////////////
void MapEditorUi::editObj(void)
{
	//�o�Ă���I�u�W�F�N�g�\��
	auto	children = mStage->getObjectList();

#pragma omp parallel for
	for (auto objIt = children->begin(); objIt != children->end();)
	{
		auto	obj = (Object*)*objIt;
		PushID(obj);

#pragma omp parallel
		{
			//�I�u�W�F�N�g�̖��O
			if (TreeNode(obj->getMyName().c_str()))
			{
				//��񑀍�
				setTransformDrag(obj->getTransformAdd());

				//�R�s�[�{�^��
				if (Button("Copy"))
				{
					createObj(*obj);
				}

				//�폜�{�^��
				if (Button("delete"))
				{
					//�I�u�W�F�N�g�폜
					obj->release();

					//���X�g����폜
					objIt = children->erase(objIt);
				}
				else
					++objIt;

				ImGui::TreePop();
			}
			else
			{
				++objIt;
			}
		}

		PopID();
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: MapEditorUi::editField
//�Ԃ�l	: 
//����		: �t�B�[���h�G�f�B�^�[�̏���
//////////////////////////////////////////////////////////////////////////////
void MapEditorUi::editField(void)
{
	//�o�Ă���t�B�[���h�\��
	auto	fieldList = mStage->getFieldList();

#pragma omp parallel for
	for (auto it = fieldList->begin(); it != fieldList->end();)
	{
		auto field = *it;
		PushID(field);

		//�t�B�[���h�̖��O
		if (TreeNode(string("field").c_str()))
		{
			PushItemWidth(GetContentRegionAvailWidth());


			//���W�ϊ��n����
			DragFloat3("pos", (float*)field->getPosAddr(), floatDragRate);
			DragFloat3("rot", (float*)field->getRotAddr(), floatDragRate);
			DragFloat2("size", (float*)field->getTyleSizeAddr(), floatDragRate);

			//�^�C��������
			DragInt2("tyle", (int*)field->getNumTyleAd(), 1, 0, 1000, "%.0f");

			//���_�F����
			DragFloat4("color", (float*)field->getColorAddr(), floatDragRate, 0.f, 1.f);
			
			//�e�N�X�`����ޑ���
			Combo("texture", field->getTextureIdAddr(), mAllTexInField.c_str(), mAllTexInField.size());

			//�폜�{�^��
			if (Button("delete"))
			{
				//�`��I�u�W�F�N�g�폜
				field->release(field);

				//���X�g����폜
				it = fieldList->erase(it);
			}
			else
			{
				++it;
			}

			ImGui::PopItemWidth();
			ImGui::TreePop();
		}
		else
		{
			++it;
		}

		PopID();
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: MapEditorUi::objectGenerationProcedure
//�Ԃ�l	: 
//����		: �I�u�W�F�N�g�����菇
//////////////////////////////////////////////////////////////////////////////
void MapEditorUi::objectGenerationProcedure(void)
{
	if (CollapsingHeader("Object"))
	{
		for (auto it = mNameList.begin(); it != mNameList.end(); it++)
		{
			std::string fileName = it->filename().string();
			if (Button(fileName.c_str()))
			{
				mStage->objectSetting(fileName);
				mNumObj++;
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: MapEditorUi::createObj
//�Ԃ�l	: 
//����		: �I�u�W�F�N�g����
//////////////////////////////////////////////////////////////////////////////
Object* MapEditorUi::createObj(string fileName)
{
	mStage->objectPlacement(fileName);

	return (Object*)mStage->getChildernList()->back();
}

void MapEditorUi::createObj(Object copyObj)
{
	auto	obj = createObj(copyObj.getModelName());
	obj->setTransform(copyObj.getTransform());
	mNumObj++;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: MapEditorUi::create
//�Ԃ�l	: 
//����		: ����
//////////////////////////////////////////////////////////////////////////////
MapEditorUi* MapEditorUi::create()
{
	auto ui = new MapEditorUi;
	ui->init();

	return ui;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: MapEditorUi::createMeshField
//�Ԃ�l	: 
//����		: ���b�V���t�B�[���h����
//////////////////////////////////////////////////////////////////////////////
MapEditorUi::FIELD MapEditorUi::createMeshField(void)
{
	FIELD	field;

	field.fieldName = "Field";
	field.texture = 0;

	field.field = MeshField::create(
		Dvec3(0, 0, 0),
		Dvec2(10, 10),
		Tyle(3, 3),
		Dvec3(0, 0, 0),
		Dcolor(1, 1, 1, 1),
		Dvec2(0, 0),
		0);

	return field;
}

/*
#################################################################################################################################################
MotionEditorUi class
#################################################################################################################################################
*/
////////////////////////////////////////////////////////////////////////////////
////�֐���	: MotionEditorUi::init
////�Ԃ�l	: 
////����		: ������
////////////////////////////////////////////////////////////////////////////////
//HRESULT MotionEditorUi::init(void)
//{
//	Player::create(new PlayerEdit);
//
//	//�ϐ�������
//	mNumMotion = 0;
//
//	//�n��
//	MeshField::create(
//		Dvec3(0, 0, 0),
//		Dvec2(10, 10),
//		Tyle(3, 3),
//		Dvec3(0, 0, 0),
//		Dcolor(1, 1, 1, 1),
//		Dvec2(0, 0),
//		0);
//
//	floatDragRate = 0.01f;
//	mEditModel = NULL;
//	mDefauldPosture = NULL;
//
//	return S_OK;
//}
//
////////////////////////////////////////////////////////////////////////////////
////�֐���	: MotionEditorUi::uninit
////�Ԃ�l	: 
////����		: �I��
////////////////////////////////////////////////////////////////////////////////
//void MotionEditorUi::uninit(void)
//{
//	mNameList.clear();
//	mPathList.clear();
//	Scene::releaseAll();
//	if (mEditModel != NULL)
//	{
//		mEditModel->uninit();
//		delete mEditModel;
//		mEditModel = NULL;
//	}
//	if (mDefauldPosture != NULL)
//		delete mDefauldPosture;
//}
//
////////////////////////////////////////////////////////////////////////////////
////�֐���	: MotionEditorUi::update
////�Ԃ�l	: 
////����		: �X�V
////////////////////////////////////////////////////////////////////////////////
//void MotionEditorUi::update(void)
//{
//	//�ݒ�E�B���h�E
//	ImGui_ImplDX9_NewFrame();
//	SetNextWindowSize(ImVec2(350, 170), ImGuiSetCond_Once);
//	SetNextWindowPos(ImVec2(SCREEN_WIDTH - 360, 10), ImGuiSetCond_Once);
//	Begin("Infomation");
//	cameraUi();
//	DragFloat("drag rate", &floatDragRate);
//	End();
//
//	//�G�f�B�b�g�E�B���h�E
//	if (mEditModel != NULL)
//	{
//		SetNextWindowSize(ImVec2(350, 450), 4);
//		SetNextWindowPos(ImVec2(SCREEN_WIDTH - 360, SCREEN_HEIGHT - 450), 4);
//		Begin("Edit Key");
//		editModelParts();
//		End();
//
//		editKeyframe();
//	}
//}
//
////////////////////////////////////////////////////////////////////////////////
////�֐���	: MotionEditorUi::load
////�Ԃ�l	: 
////����		: �ǂݍ���
////////////////////////////////////////////////////////////////////////////////
//void MotionEditorUi::load()
//{
//	string openFileDir = Load::loadingFile(NULL,
//		"�f�[�^�ǂݍ���",
//		".mo\0.mt\0",
//		"MODEL�t�@�C��(*.mo)\0*.mo\0MOTION�t�@�C��(*.mt)\0*.mt");
//	if (openFileDir == "NONE")
//		return;
//
//	uninit();
//	init();
//	mEditModel = MotionEdit::create(Transform::zero());
//	mDefauldPosture = new ModelParts;
//
//	if (openFileDir.find(".mo") != UINT_MAX)
//	{
//		mDefauldPosture->loadModelData(openFileDir);
//		auto	motionData = mEditModel->getModelPartsAddr();
//		*motionData = *mDefauldPosture;
//		mEditModel->getModelPartsAddr()->mMotionDataList.
//			push_back(MotionData::create("motion0", mDefauldPosture->mPartsList));
//
//		auto	data = *motionData->mMotionDataList.begin();
//		auto	key = data->mKeyframeList[0];
//		Keyframe::setPartsTransform(motionData->mPartsList, key->mKey);
//		mKeyToEdit = key;
//		mCopyKeyframe = *key;
//	}
//	if (openFileDir.find(".mt") != UINT_MAX)
//	{
//		mDefauldPosture->loadModelData(openFileDir);
//		auto	motionData = mEditModel->getModelPartsAddr();
//		*motionData = *mDefauldPosture;
//		mEditModel->getModelPartsAddr()->mMotionDataList = MotionData::loadMotionData(openFileDir);
//	}
//}
//
////////////////////////////////////////////////////////////////////////////////
////�֐���	: MotionEditorUi::save
////�Ԃ�l	: 
////����		: �ۑ�
////////////////////////////////////////////////////////////////////////////////
//void MotionEditorUi::save(HWND hWnd)
//{
//	string	saveFileDir = Save::selectSaveFileDir(hWnd, "�f�[�^�ۑ�", ".mt", "MOTION�t�@�C��(*.mt)\0*.mt\0");
//	SaveMotion::saveFile(saveFileDir);
//}
//
////////////////////////////////////////////////////////////////////////////////
////�֐���	: MotionEditorUi::editModelParts
////�Ԃ�l	: 
////����		: ���f���G�f�B�^�[�̏���
////////////////////////////////////////////////////////////////////////////////
//void MotionEditorUi::editModelParts(void)
//{
//	if (CollapsingHeader("Model Parts"))
//	{
//		if (Button("Accept", ImVec2(100, 0)))
//		{
//			auto	partsList = mEditModel->getPartsAddr()->mPartsList;
//			mKeyToEdit->setKeyValue(partsList);
//		}
//		SameLine();
//		if (Button("Copy", ImVec2(100, 0)))
//		{
//			mCopyKeyframe.setKeyValue(mEditModel->getPartsAddr()->mPartsList);
//		}
//		SameLine();
//		if (Button("Paste", ImVec2(100, 0)))
//		{
//			Keyframe::setPartsTransform(mEditModel->getPartsAddr()->mPartsList, mCopyKeyframe.mKey);
//		}
//		DragInt("Frame rate", &mKeyToEdit->mFrameRate, 1, 0, 300);
//
//		Parts	*part = mEditModel->getPartsAddr()->mMainParts;
//		if (TreeNode(part->mModelData->getModelName().c_str()))
//		{
//			setTransformDrag(&mEditModel->getModelPartsAddr()->mMainParts->mTransform);
//
//			ImGui::TreePop();
//		}
//
//		followPartsChildren(part->mChildrenList);
//	}
//
//}
//
////////////////////////////////////////////////////////////////////////////////
////�֐���	: MotionEditorUi::editKeyframe
////�Ԃ�l	: 
////����		: �L�[�t���[���쐬�E�B���h�E�\��
////////////////////////////////////////////////////////////////////////////////
//void MotionEditorUi::editKeyframe(void)
//{
//	Begin("Key frame");
//	if (Button("New motion"))
//		mEditModel->getPartsAddr()->mMotionDataList.push_back(createNewMotionData("motion" + to_string(mNumMotion)));
//
//	seeAllMotionDataList(mEditModel->getParts().mMotionDataList);
//	End();
//}
//
////////////////////////////////////////////////////////////////////////////////
////�֐���	: MotionEditorUi::createNewMotionData
////�Ԃ�l	: 
////����		: �V�������[�V���������
////////////////////////////////////////////////////////////////////////////////
//MotionData	*MotionEditorUi::createNewMotionData(string motionName)
//{
//	mNumMotion++;
//	return MotionData::create(motionName, mDefauldPosture->mPartsList);
//}
//
////////////////////////////////////////////////////////////////////////////////
////�֐���	: MotionEditorUi::createNewKeyframe
////�Ԃ�l	: 
////����		: �V�����L�[�t���[�������
////////////////////////////////////////////////////////////////////////////////
//auto	MotionEditorUi::createNewKeyframe(MotionData motionData)
//{
//	if (motionData.mKeyframeList.size() != 0)
//		return new Keyframe(*motionData.mKeyframeList[motionData.mKeyframeList.size() - 1]);
//
//	return Keyframe::create(mDefauldPosture->mPartsList);
//}
//
////////////////////////////////////////////////////////////////////////////////
////�֐���	: MotionEditorUi::seeAllMotionDataList
////�Ԃ�l	: 
////����		: ���[�V�����f�[�^���X�g�̏���S�Ĕ����o��
////////////////////////////////////////////////////////////////////////////////
//void MotionEditorUi::seeAllMotionDataList(list<MotionData*> dataList)
//{
//	int i = 0;
//	for (auto it = dataList.begin(); it != dataList.end(); ++it, i++)
//	{
//		auto	data = *it;
//		PushID(data);
//		char	work[CHAR_MAX];
//		sprintf(work, data->mMotionName.c_str());
//		ImGui::InputText("motionName", work, sizeof(work));
//		data->mMotionName = work;
//
//		if (CollapsingHeader(data->mMotionName.c_str()))
//		{
//			keyframeSetting(data, i);
//			for (UINT j = 0; j < data->mKeyframeList.size(); j++)
//			{
//				string	keyFrameName = "Keyframe" + to_string(j);
//				auto	key = data->mKeyframeList[j];
//
//				//MainParts��Human�ɃR�s�[
//				if (Button(keyFrameName.c_str()))
//				{
//					Keyframe::setPartsTransform(mEditModel->getPartsAddr()->mPartsList, key->mKey);
//					mKeyToEdit = key;
//				}
//
//				SameLine();
//				if (Button("Delete"))
//				{
//					delete key;
//					data->mKeyframeList.erase(data->mKeyframeList.begin() + j);
//				}
//			}
//		}
//		PopID();
//	}
//}
//
////////////////////////////////////////////////////////////////////////////////
////�֐���	: MotionEditorUi::keyframeSetting
////�Ԃ�l	: 
////����		: ���[�V�����f�[�^�̕ҏW
////////////////////////////////////////////////////////////////////////////////
//void MotionEditorUi::keyframeSetting(MotionData *motionData, int id)
//{
//	//�{�^����ID�o�^
//	ImGui::PushID(id);
//
//	//�{�^���̐F�ݒ�
//	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.3f, 0.3f, 1.f, 1.f));
//
//	//�{�^������
//	createKeyframeButton(motionData);
//	SameLine();
//	playButton(*motionData);
//	SameLine();
//	selectPlayModeCombo(motionData);
//
//	//�ݒ���|�b�v
//	ImGui::PopStyleColor();
//	ImGui::PopID();
//}
//
////////////////////////////////////////////////////////////////////////////////
////�֐���	: MotionEditorUi::createKeyframeButton
////�Ԃ�l	: 
////����		: �L�[�t���[����������
////////////////////////////////////////////////////////////////////////////////
//void MotionEditorUi::createKeyframeButton(MotionData *motionData)
//{
//	if (Button("create keyframe"))
//		motionData->mKeyframeList.push_back(createNewKeyframe(*motionData));
//}
//
////////////////////////////////////////////////////////////////////////////////
////�֐���	: MotionEditorUi::playButton
////�Ԃ�l	: 
////����		: ���[�V�����Đ��{�^��
////////////////////////////////////////////////////////////////////////////////
//void MotionEditorUi::playButton(MotionData motionData)
//{
//	if (Button("Play"))
//	{
//		Keyframe::setPartsTransform(mEditModel->getPartsAddr()->mPartsList, motionData.mKeyframeList[0]->mKey);
//		mEditModel->getPartsAddr()->playMotion(motionData.mMotionName);
//	}
//}
//
////////////////////////////////////////////////////////////////////////////////
////�֐���	: MotionEditorUi::selectPlayModeCombo
////�Ԃ�l	: 
////����		: ���[�V�����Đ����[�h�ύX
////////////////////////////////////////////////////////////////////////////////
//void MotionEditorUi::selectPlayModeCombo(MotionData * motionData)
//{
//	Combo("Play mode", &motionData->mPlayMode, "ONECE\0LOOP\0");
//}
//
////////////////////////////////////////////////////////////////////////////////
////�֐���	: MotionEditorUi::followPartsChildren
////�Ԃ�l	: 
////����		: �q�̃p�[�c�̃X���C�_�[�ݒ�
////////////////////////////////////////////////////////////////////////////////
//void MotionEditorUi::followPartsChildren(list<Parts*> childrenList)
//{
//	for (auto it = childrenList.begin(); it != childrenList.end(); ++it)
//	{
//		auto part = *it;
//		if (TreeNode(part->mModelData->getModelName().c_str()))
//		{
//			setTransformDrag(&part->mTransform);
//
//			ImGui::TreePop();
//		}
//
//		followPartsChildren(part->mChildrenList);
//	}
//}

/*
#################################################################################################################################################
CollisionEditorUi class
#################################################################################################################################################
*/
//////////////////////////////////////////////////////////////////////////////
//�֐���	: CollisionEditorUi::init
//�Ԃ�l	: 
//����		: ������
//////////////////////////////////////////////////////////////////////////////
HRESULT CollisionEditorUi::init()
{
	Player::create(new PlayerEdit);
#pragma omp parallel for
	objectList = Scene::getTypeList(Scene::OBJECT);

	floatDragRate = 0.01f;
	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: CollisionEditorUi::uninit
//�Ԃ�l	: 
//����		: �I��
//////////////////////////////////////////////////////////////////////////////
void CollisionEditorUi::uninit()
{
	objectList.clear();

	Scene::uninitAll();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: CollisionEditorUi::update
//�Ԃ�l	: 
//����		: �X�V
//////////////////////////////////////////////////////////////////////////////
void CollisionEditorUi::update()
{
	ImGui_ImplDX9_NewFrame();
	SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_FirstUseEver);
	Begin("Infomation");

	//�J����UI�쐬
	cameraUi();

	DragFloat("drag rate", &floatDragRate, 0.01f);
	End();

	SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_FirstUseEver);
	Begin("Obje Config");

#pragma omp paralell for
	for (auto it = objectList.begin(); it != objectList.end(); ++it)
	{
		auto	scene = *it;
		PushID(scene);

		if (TreeNode(scene->getMyName().c_str()))
		{
			if (Button("create box"))
				scene->setCollision(CollisionBox::create(scene, Dvec3(0, 0, 0), Dvec3(10, 10, 10)));

			if (Button("create ball"))
				scene->setCollision(CollisionBall::create(scene, Dvec3(0, 0, 0), 5.f));

			if (scene->getCollision() == NULL)
			{
				PopID();
				ImGui::TreePop();
				continue;
			}

			auto colList = scene->getCollision()->getCollisionList();
			for (auto colIt = colList->begin(); colIt != colList->end();)
			{
				colIt = selectCollisionEdit(*colIt, colList, colIt);
			}
			ImGui::TreePop();
		}
		PopID();
	}

	End();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: CollisionEditorUi::load
//�Ԃ�l	: 
//����		: �ǂݍ���
//////////////////////////////////////////////////////////////////////////////
void CollisionEditorUi::load()
{
	mSelectionFilename = Load::loadingFile(NULL,
		"�f�[�^�ǂݍ���",
		".map\0.txt\0.col\0.mo\0",
		"\0*.*\0");
	if (mSelectionFilename == "NONE")
		return;

	if (mSelectionFilename.find(".map") != UINT_MAX)
	{
		mStage = Stage::create();
		mStage->loadMapFile(mSelectionFilename);
	}

	if (mSelectionFilename.find(".x") != UINT_MAX)
		Object::create(mSelectionFilename);

	if (mSelectionFilename.find(".mo") != UINT_MAX)
		SceneModel::loadModelData(mSelectionFilename);
	
	Ui::init();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: CollisionEditorUi::save
//�Ԃ�l	: 
//����		: �ۑ�
//////////////////////////////////////////////////////////////////////////////
void CollisionEditorUi::save(HWND hWnd)
{
	auto ext = mSelectionFilename.substr(mSelectionFilename.find("."), mSelectionFilename.size());
	string	saveFileDir = Save::selectSaveFileDir(hWnd, "�f�[�^�ۑ�","", "\0*.*\0");

	if (mSelectionFilename.find(".mo") != UINT_MAX) {}
		///SaveModel::saveFile(saveFileDir);
	if (mSelectionFilename.find(".x") != UINT_MAX) {}
		//SaveCollision::saveFile(saveFileDir, "w");
	if (mSelectionFilename.find(".map") != UINT_MAX)
		mStage->saveMap(saveFileDir);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: CollisionEditorUi::selectCollisionEdit
//�Ԃ�l	: 
//����		: �R���W������ނ��Ƃɏ����ύX
//////////////////////////////////////////////////////////////////////////////
list<Collision*>::iterator CollisionEditorUi::selectCollisionEdit(Collision * col, list<Collision*>* colList, list<Collision*>::iterator colIt)
{
	PushItemWidth(GetContentRegionAvailWidth() * 0.5f);
	PushID(col);
	switch (col->getType())
	{
	case Collision::BOX:
		colIt = shouldShawBoxEdit((CollisionBox*)col, colList, colIt);
		break;

	case Collision::BALL:
		colIt = shouldShawBallEdit((CollisionBall*)col, colList, colIt);
		break;

	default:
		++colIt;
	}
	ImGui::PopItemWidth();
	ImGui::PopID();

	return colIt;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: CollisionEditorUi::editCollisionBox
//�Ԃ�l	: 
//����		: �R���W�����{�b�N�X�̕ҏW
//////////////////////////////////////////////////////////////////////////////
void CollisionEditorUi::editCollisionBox(CollisionBox * box)
{
	DragFloat3("pos", (float*)box->getPosAddr(), floatDragRate);
	DragFloat3("size", (float*)box->getSizeAd(), floatDragRate);
	DragFloat3("rot", (float*)box->getRotAd(), floatDragRate);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: CollisionEditorUi::shawBoxEdit
//�Ԃ�l	: 
//����		: �R���W�����{�b�N�X�ҏW�o�[�\��
//////////////////////////////////////////////////////////////////////////////
list<Collision*>::iterator CollisionEditorUi::shawBoxEdit(CollisionBox * box, list<Collision*>* colList, list<Collision*>::iterator colIt)
{
	//�R���W��������
	editCollisionBox(box);

	//�폜�{�^��
	colIt = deleteCollision(box, colList, colIt);

	ImGui::TreePop();

	return colIt;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: CollisionEditorUi::shawBallEdit
//�Ԃ�l	: 
//����		: �R���W�����{�[���ҏW�o�[�\��
//////////////////////////////////////////////////////////////////////////////
list<Collision*>::iterator CollisionEditorUi::shawBallEdit(CollisionBall * ball, list<Collision*>* colList, list<Collision*>::iterator colIt)
{
	//�R���W��������
	editCollisionBall(ball);

	//�폜�{�^��
	colIt = deleteCollision(ball, colList, colIt);

	ImGui::TreePop();

	return colIt;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: CollisionEditorUi::isShawBoxEdit
//�Ԃ�l	: 
//����		: �R���W�����{�b�N�X�G�f�B�b�g���J�����ǂ���
//////////////////////////////////////////////////////////////////////////////
list<Collision*>::iterator CollisionEditorUi::shouldShawBoxEdit(CollisionBox* box, list<Collision*>* colList, list<Collision*>::iterator colIt)
{
	if (TreeNode("box"))
		colIt = shawBoxEdit(box, colList, colIt);
	else
		++colIt;

	return colIt;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: CollisionEditorUi::isShawBallEdit
//�Ԃ�l	: 
//����		: �R���W�����{�[���G�f�B�b�g���J�����ǂ���
//////////////////////////////////////////////////////////////////////////////
list<Collision*>::iterator CollisionEditorUi::shouldShawBallEdit(CollisionBall * ball, list<Collision*>* colList, list<Collision*>::iterator colIt)
{
	if (TreeNode("ball"))
		colIt = shawBallEdit(ball, colList, colIt);
	else
		++colIt;

	return colIt;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: CollisionEditorUi::deleteCollision
//�Ԃ�l	: 
//����		: �R���W�����폜
//////////////////////////////////////////////////////////////////////////////
list<Collision*>::iterator CollisionEditorUi::deleteCollision(Collision * col, list<Collision*>* colList, list<Collision*>::iterator colIt)
{
	if (Button("delete"))
	{
		col->uninit();
		delete col;
		colIt = colList->erase(colIt);
	}
	else
		++colIt;

	return colIt;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: CollisionEditorUi::editCollisionBall
//�Ԃ�l	: 
//����		: �R���W�����{�[���ҏW
//////////////////////////////////////////////////////////////////////////////
void CollisionEditorUi::editCollisionBall(CollisionBall * ball)
{
	DragFloat3("pos", (float*)ball->getRelativePosAddr(), floatDragRate);
	DragFloat("length", (float*)ball->getLenAddr(), floatDragRate);
}

/*
#################################################################################################################################################
ModelEditorUi class
#################################################################################################################################################
*/
//////////////////////////////////////////////////////////////////////////////
//�֐���	: ModelEditorUi::init
//�Ԃ�l	: 
//����		: ������
//////////////////////////////////////////////////////////////////////////////
HRESULT ModelEditorUi::init()
{
	Player::create(new PlayerEdit);

	string currendDir = Directory::getCurrentDir("\\data\\model");
	mModelFileNameList = Directory::fileAllReferenceInDirectory(currendDir, ".x");
	floatDragRate = 0.01f;

	//�n��
	MeshField::create(
		Dvec3(0, 0, 0),
		Dvec2(10, 10),
		Tyle(3, 3),
		Dvec3(0, 0, 0),
		Dcolor(1, 1, 1, 1),
		Dvec2(0, 0),
		0);

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: ModelEditorUi::uninit
//�Ԃ�l	: 
//����		: �I��
//////////////////////////////////////////////////////////////////////////////
void ModelEditorUi::uninit()
{
	mModelList.clear();
	Scene::releaseAll();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: ModelEditorUi::update
//�Ԃ�l	: 
//����		: �X�V
//////////////////////////////////////////////////////////////////////////////
void ModelEditorUi::update()
{
	ImGui_ImplDX9_NewFrame();

	//�ē�
	setInfomationWindow();

	//�ҏW�E�B���h�E�ݒ�
	setEditWindow();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: ModelEditorUi::load
//�Ԃ�l	: 
//����		: �ǂݍ���
//////////////////////////////////////////////////////////////////////////////
void ModelEditorUi::load()
{
	string openFileDir = Load::loadingFile(NULL,
		"�f�[�^�ǂݍ���",
		".mo\0",
		"MODEL�t�@�C��(*.mo)\0");
	if (openFileDir == "NONE")
		return;

	uninit();
	auto modelMap = SceneModel::loadModelData(openFileDir);
#pragma omp parallel for
	for (auto it = modelMap.begin(); it != modelMap.end(); ++it)
	{
		auto map = *it;
		editModelAdd(map.second);
	}

#pragma omp parallel for
	for (UINT i = 0; i < mModelList.size(); i++)
	{
		UINT id;
		auto parent = mModelList[i].scene->getParent();
		if (parent == NULL)
		{
			mModelList[i].parentID = 0;
			continue;
		}

		for (id = 0; id < mModelList.size(); id++)
		{
			if (parent->getMyName() == mModelList[id].scene->getMyName())
			{
				mModelList[i].scene->setParent(mModelList[id].scene);
				break;
			}
		}
		mModelList[i].parentID = id + 1;
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: ModelEditorUi::save
//�Ԃ�l	: 
//����		: �ۑ�����
//////////////////////////////////////////////////////////////////////////////
void ModelEditorUi::save(HWND hWnd)
{
	string	saveFileDir = Save::selectSaveFileDir(hWnd, "�f�[�^�ۑ�", ".mo", "TXT�t�@�C��(*.txt)\0*.txt\0");
	//SaveModel::saveFile(saveFileDir);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: ModelEditorUi::editModelAdd
//�Ԃ�l	: 
//����		: �ҏW���f���ǉ�
//////////////////////////////////////////////////////////////////////////////
void ModelEditorUi::editModelAdd(string modelName)
{
	EDIT_DATA data;
	data.scene = Object::create(modelName.c_str());
	data.parentID = 0;
	mModelList.push_back(data);
}

void ModelEditorUi::editModelAdd(Scene * scene)
{
	EDIT_DATA data;
	data.scene = scene;
	data.parentID = 0;
	mModelList.push_back(data);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: ModelEditorUi::modelButton
//�Ԃ�l	: 
//����		: ���f���ǉ��{�^���\��
//////////////////////////////////////////////////////////////////////////////
void ModelEditorUi::modelButton(void)
{
	for (auto it = mModelFileNameList.begin(); it != mModelFileNameList.end(); ++it)
	{
		auto name = *it;
		if (Button(name.filename().string().c_str()))
			editModelAdd(name.filename().string());
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: ModelEditorUi::setInfomationWindow
//�Ԃ�l	: 
//����		: �ē������ݒ�
//////////////////////////////////////////////////////////////////////////////
void ModelEditorUi::setInfomationWindow(void)
{
	SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_FirstUseEver);
	Begin("Infomation");

	//�J����UI�쐬
	cameraUi();

	//�h���b�O���[�gUI
	DragFloat("drag rate", &floatDragRate, 0.01f);

	//�ҏW���f���ǉ��{�^��
	if (CollapsingHeader("models"))
		modelButton();

	End();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: ModelEditorUi::setEditModelDeleteButton
//�Ԃ�l	: 
//����		: �ҏW���f���폜�{�^���ݒ�
//////////////////////////////////////////////////////////////////////////////
void ModelEditorUi::setEditModelDeleteButton(Scene* scene, int num)
{
	if (Button("delete"))
	{
		scene->release();
		mModelList.erase(mModelList.begin() + num);
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: ModelEditorUi::setParentCombo
//�Ԃ�l	: 
//����		: �e���f���ݒ�R���{
//////////////////////////////////////////////////////////////////////////////
void ModelEditorUi::setParentCombo(Scene * scene, int & id)
{
	string objectList = getDisplayModelNameList();
	if (Combo("parent", &id, objectList.c_str()))
	{
		if (id == 0)
			scene->setParent(NULL);
		else
			scene->setParent(mModelList[id - 1].scene);
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: ModelEditorUi::getDisplayModelNameList
//�Ԃ�l	: 
//����		: �\�����f�����𕶎���ɂ������̂��擾
//////////////////////////////////////////////////////////////////////////////
string ModelEditorUi::getDisplayModelNameList(void)
{
	string objectList = "NULL";
	for (auto it = mModelList.begin(); it != mModelList.end(); it++)
	{
		auto data = *it;
		objectList.push_back('\0');
		objectList += data.scene->getMyName();
	}
	objectList.push_back('\0');
	return objectList;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: ModelEditorUi::setModelEditTool
//�Ԃ�l	: 
//����		: �ҏW�c�[���ݒ�
//////////////////////////////////////////////////////////////////////////////
void ModelEditorUi::setModelEditTool(Scene * scene, int & id, int arrayNum)
{
	setTransformDrag(scene->getTransformAdd());
	setParentCombo(scene, id);
	setEditModelDeleteButton(scene, arrayNum);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: ModelEditorUi::setModelEditTool
//�Ԃ�l	: 
//����		: �ҏW�c�[���ݒ�
//////////////////////////////////////////////////////////////////////////////
void ModelEditorUi::setEditModelTree(int arrayNum)
{
	if (TreeNode(mModelList[arrayNum].scene->getMyName().c_str()))
	{
		setModelEditTool(mModelList[arrayNum].scene, mModelList[arrayNum].parentID, arrayNum);
		TreePop();
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: ModelEditorUi::setEditWindow
//�Ԃ�l	: 
//����		: �ҏW�E�B���h�E
//////////////////////////////////////////////////////////////////////////////
void ModelEditorUi::setEditWindow(void)
{
	SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_FirstUseEver);
	Begin("Editor");

	for (UINT i = 0; i < mModelList.size(); i++)
	{
		PushID(mModelList[i].scene);
		setEditModelTree(i);
		PopID();
	}

	End();
}
