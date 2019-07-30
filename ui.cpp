/*****************************************************************************
ui.cpp
Aythor	: 上野　匠
Data	: 2017_07_28
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
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
//関数名	: Ui::init
//返り値	: 
//説明		: 初期化
//////////////////////////////////////////////////////////////////////////////
HRESULT Ui::init(void)
{
	mMyName = "ui";
	mCamera = (Camera*)Scene::getTypeList(Scene::CAMERA).front();
	setObjType(UI);
	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Ui::cameraUi
//返り値	: 
//説明		: カメラUI作成
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
//関数名	: Ui::setTransformDrag
//返り値	: 
//説明		: 座標系のドラッグ設定
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
//関数名	: MapEditorUi::init
//返り値	: 
//説明		: 初期化
//////////////////////////////////////////////////////////////////////////////
HRESULT MapEditorUi::init(void)
{
	Camera::create(
		D3DXVECTOR3(0.f, 10.f, -30.f),
		D3DXVECTOR3(0.f, 0.f, 0.f),
		D3DXVECTOR3(0.f, 1.f, 0.f),
		-30);
	Player::create(new PlayerEdit);

	//変数初期化
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
//関数名	: MapEditorUi::update
//返り値	: 
//説明		: 更新
//////////////////////////////////////////////////////////////////////////////
void MapEditorUi::update(void)
{
	//カメラUI作成
	cameraUi();

	//エディットウィンドウ生成
	SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_FirstUseEver);
	Begin("Create");
	editWindow();
	End();

	//オブジェクト編集ウィンドウ生成
	SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_FirstUseEver);
	Begin("Obje Config");
	settingWindw();
	End();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: MapEditorUi::load
//返り値	: 
//説明		: ファイルから読み込み
//////////////////////////////////////////////////////////////////////////////
void MapEditorUi::load()
{
	string openFileDir = Load::loadingFile(NULL,
		"データ読み込み",
		".map\0",
		"MAPファイル(*.map)\0*.map\0");
	if (openFileDir == "NONE")
		return;

	reset();
	mStage->loadMapFile(openFileDir);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: MapEditorUi::save
//返り値	: 
//説明		: 保存処理
//////////////////////////////////////////////////////////////////////////////
void MapEditorUi::save(HWND hWnd)
{
	string	saveFileDir = Save::selectSaveFileDir(hWnd, "データ保存", ".map", "MAPファイル(*.map)\0*.map\0");
	mStage->saveMap(saveFileDir);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: MapEditorUi::reset
//返り値	: 
//説明		: リセット
//////////////////////////////////////////////////////////////////////////////
void MapEditorUi::reset()
{
	Scene::releaseAll();
	Scene::updateAll();
	init();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: MapEditorUi::settingWindw
//返り値	: 
//説明		: オブジェクトの設定編集ウィンドウの処理
//////////////////////////////////////////////////////////////////////////////
void MapEditorUi::settingWindw(void)
{
	if (TreeNode("Stage"))
	{
		//情報操作
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
//関数名	: MapEditorUi::editWindow
//返り値	: 
//説明		: エディットウィンドウ生成
//////////////////////////////////////////////////////////////////////////////
void MapEditorUi::editWindow(void)
{
	DragFloat("drag rate", &floatDragRate, 0.01f);

	//オブジェクト生成ボタン
	objectGenerationProcedure();

	//メッシュフィールド生成ボタン
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
//関数名	: MapEditorUi::editObj
//返り値	: 
//説明		: オブジェクトエディタータブの処理
//////////////////////////////////////////////////////////////////////////////
void MapEditorUi::editObj(void)
{
	//出ているオブジェクト表示
	auto	children = mStage->getObjectList();

#pragma omp parallel for
	for (auto objIt = children->begin(); objIt != children->end();)
	{
		auto	obj = (Object*)*objIt;
		PushID(obj);

#pragma omp parallel
		{
			//オブジェクトの名前
			if (TreeNode(obj->getMyName().c_str()))
			{
				//情報操作
				setTransformDrag(obj->getTransformAdd());

				//コピーボタン
				if (Button("Copy"))
				{
					createObj(*obj);
				}

				//削除ボタン
				if (Button("delete"))
				{
					//オブジェクト削除
					obj->release();

					//リストから削除
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
//関数名	: MapEditorUi::editField
//返り値	: 
//説明		: フィールドエディターの処理
//////////////////////////////////////////////////////////////////////////////
void MapEditorUi::editField(void)
{
	//出ているフィールド表示
	auto	fieldList = mStage->getFieldList();

#pragma omp parallel for
	for (auto it = fieldList->begin(); it != fieldList->end();)
	{
		auto field = *it;
		PushID(field);

		//フィールドの名前
		if (TreeNode(string("field").c_str()))
		{
			PushItemWidth(GetContentRegionAvailWidth());


			//座標変換系操作
			DragFloat3("pos", (float*)field->getPosAddr(), floatDragRate);
			DragFloat3("rot", (float*)field->getRotAddr(), floatDragRate);
			DragFloat2("size", (float*)field->getTyleSizeAddr(), floatDragRate);

			//タイル数操作
			DragInt2("tyle", (int*)field->getNumTyleAd(), 1, 0, 1000, "%.0f");

			//頂点色操作
			DragFloat4("color", (float*)field->getColorAddr(), floatDragRate, 0.f, 1.f);
			
			//テクスチャ種類操作
			Combo("texture", field->getTextureIdAddr(), mAllTexInField.c_str(), mAllTexInField.size());

			//削除ボタン
			if (Button("delete"))
			{
				//描画オブジェクト削除
				field->release(field);

				//リストから削除
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
//関数名	: MapEditorUi::objectGenerationProcedure
//返り値	: 
//説明		: オブジェクト生成手順
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
//関数名	: MapEditorUi::createObj
//返り値	: 
//説明		: オブジェクト生成
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
//関数名	: MapEditorUi::create
//返り値	: 
//説明		: 生成
//////////////////////////////////////////////////////////////////////////////
MapEditorUi* MapEditorUi::create()
{
	auto ui = new MapEditorUi;
	ui->init();

	return ui;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: MapEditorUi::createMeshField
//返り値	: 
//説明		: メッシュフィールド生成
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
////関数名	: MotionEditorUi::init
////返り値	: 
////説明		: 初期化
////////////////////////////////////////////////////////////////////////////////
//HRESULT MotionEditorUi::init(void)
//{
//	Player::create(new PlayerEdit);
//
//	//変数初期化
//	mNumMotion = 0;
//
//	//地面
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
////関数名	: MotionEditorUi::uninit
////返り値	: 
////説明		: 終了
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
////関数名	: MotionEditorUi::update
////返り値	: 
////説明		: 更新
////////////////////////////////////////////////////////////////////////////////
//void MotionEditorUi::update(void)
//{
//	//設定ウィンドウ
//	ImGui_ImplDX9_NewFrame();
//	SetNextWindowSize(ImVec2(350, 170), ImGuiSetCond_Once);
//	SetNextWindowPos(ImVec2(SCREEN_WIDTH - 360, 10), ImGuiSetCond_Once);
//	Begin("Infomation");
//	cameraUi();
//	DragFloat("drag rate", &floatDragRate);
//	End();
//
//	//エディットウィンドウ
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
////関数名	: MotionEditorUi::load
////返り値	: 
////説明		: 読み込み
////////////////////////////////////////////////////////////////////////////////
//void MotionEditorUi::load()
//{
//	string openFileDir = Load::loadingFile(NULL,
//		"データ読み込み",
//		".mo\0.mt\0",
//		"MODELファイル(*.mo)\0*.mo\0MOTIONファイル(*.mt)\0*.mt");
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
////関数名	: MotionEditorUi::save
////返り値	: 
////説明		: 保存
////////////////////////////////////////////////////////////////////////////////
//void MotionEditorUi::save(HWND hWnd)
//{
//	string	saveFileDir = Save::selectSaveFileDir(hWnd, "データ保存", ".mt", "MOTIONファイル(*.mt)\0*.mt\0");
//	SaveMotion::saveFile(saveFileDir);
//}
//
////////////////////////////////////////////////////////////////////////////////
////関数名	: MotionEditorUi::editModelParts
////返り値	: 
////説明		: モデルエディターの処理
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
////関数名	: MotionEditorUi::editKeyframe
////返り値	: 
////説明		: キーフレーム作成ウィンドウ表示
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
////関数名	: MotionEditorUi::createNewMotionData
////返り値	: 
////説明		: 新しいモーションを作る
////////////////////////////////////////////////////////////////////////////////
//MotionData	*MotionEditorUi::createNewMotionData(string motionName)
//{
//	mNumMotion++;
//	return MotionData::create(motionName, mDefauldPosture->mPartsList);
//}
//
////////////////////////////////////////////////////////////////////////////////
////関数名	: MotionEditorUi::createNewKeyframe
////返り値	: 
////説明		: 新しいキーフレームを作る
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
////関数名	: MotionEditorUi::seeAllMotionDataList
////返り値	: 
////説明		: モーションデータリストの情報を全て抜き出す
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
//				//MainPartsをHumanにコピー
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
////関数名	: MotionEditorUi::keyframeSetting
////返り値	: 
////説明		: モーションデータの編集
////////////////////////////////////////////////////////////////////////////////
//void MotionEditorUi::keyframeSetting(MotionData *motionData, int id)
//{
//	//ボタンのID登録
//	ImGui::PushID(id);
//
//	//ボタンの色設定
//	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.3f, 0.3f, 1.f, 1.f));
//
//	//ボタン生成
//	createKeyframeButton(motionData);
//	SameLine();
//	playButton(*motionData);
//	SameLine();
//	selectPlayModeCombo(motionData);
//
//	//設定をポップ
//	ImGui::PopStyleColor();
//	ImGui::PopID();
//}
//
////////////////////////////////////////////////////////////////////////////////
////関数名	: MotionEditorUi::createKeyframeButton
////返り値	: 
////説明		: キーフレーム生成処理
////////////////////////////////////////////////////////////////////////////////
//void MotionEditorUi::createKeyframeButton(MotionData *motionData)
//{
//	if (Button("create keyframe"))
//		motionData->mKeyframeList.push_back(createNewKeyframe(*motionData));
//}
//
////////////////////////////////////////////////////////////////////////////////
////関数名	: MotionEditorUi::playButton
////返り値	: 
////説明		: モーション再生ボタン
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
////関数名	: MotionEditorUi::selectPlayModeCombo
////返り値	: 
////説明		: モーション再生モード変更
////////////////////////////////////////////////////////////////////////////////
//void MotionEditorUi::selectPlayModeCombo(MotionData * motionData)
//{
//	Combo("Play mode", &motionData->mPlayMode, "ONECE\0LOOP\0");
//}
//
////////////////////////////////////////////////////////////////////////////////
////関数名	: MotionEditorUi::followPartsChildren
////返り値	: 
////説明		: 子のパーツのスライダー設定
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
//関数名	: CollisionEditorUi::init
//返り値	: 
//説明		: 初期化
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
//関数名	: CollisionEditorUi::uninit
//返り値	: 
//説明		: 終了
//////////////////////////////////////////////////////////////////////////////
void CollisionEditorUi::uninit()
{
	objectList.clear();

	Scene::uninitAll();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: CollisionEditorUi::update
//返り値	: 
//説明		: 更新
//////////////////////////////////////////////////////////////////////////////
void CollisionEditorUi::update()
{
	ImGui_ImplDX9_NewFrame();
	SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_FirstUseEver);
	Begin("Infomation");

	//カメラUI作成
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
//関数名	: CollisionEditorUi::load
//返り値	: 
//説明		: 読み込み
//////////////////////////////////////////////////////////////////////////////
void CollisionEditorUi::load()
{
	mSelectionFilename = Load::loadingFile(NULL,
		"データ読み込み",
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
//関数名	: CollisionEditorUi::save
//返り値	: 
//説明		: 保存
//////////////////////////////////////////////////////////////////////////////
void CollisionEditorUi::save(HWND hWnd)
{
	auto ext = mSelectionFilename.substr(mSelectionFilename.find("."), mSelectionFilename.size());
	string	saveFileDir = Save::selectSaveFileDir(hWnd, "データ保存","", "\0*.*\0");

	if (mSelectionFilename.find(".mo") != UINT_MAX) {}
		///SaveModel::saveFile(saveFileDir);
	if (mSelectionFilename.find(".x") != UINT_MAX) {}
		//SaveCollision::saveFile(saveFileDir, "w");
	if (mSelectionFilename.find(".map") != UINT_MAX)
		mStage->saveMap(saveFileDir);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: CollisionEditorUi::selectCollisionEdit
//返り値	: 
//説明		: コリジョン種類ごとに処理変更
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
//関数名	: CollisionEditorUi::editCollisionBox
//返り値	: 
//説明		: コリジョンボックスの編集
//////////////////////////////////////////////////////////////////////////////
void CollisionEditorUi::editCollisionBox(CollisionBox * box)
{
	DragFloat3("pos", (float*)box->getPosAddr(), floatDragRate);
	DragFloat3("size", (float*)box->getSizeAd(), floatDragRate);
	DragFloat3("rot", (float*)box->getRotAd(), floatDragRate);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: CollisionEditorUi::shawBoxEdit
//返り値	: 
//説明		: コリジョンボックス編集バー表示
//////////////////////////////////////////////////////////////////////////////
list<Collision*>::iterator CollisionEditorUi::shawBoxEdit(CollisionBox * box, list<Collision*>* colList, list<Collision*>::iterator colIt)
{
	//コリジョン操作
	editCollisionBox(box);

	//削除ボタン
	colIt = deleteCollision(box, colList, colIt);

	ImGui::TreePop();

	return colIt;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: CollisionEditorUi::shawBallEdit
//返り値	: 
//説明		: コリジョンボール編集バー表示
//////////////////////////////////////////////////////////////////////////////
list<Collision*>::iterator CollisionEditorUi::shawBallEdit(CollisionBall * ball, list<Collision*>* colList, list<Collision*>::iterator colIt)
{
	//コリジョン操作
	editCollisionBall(ball);

	//削除ボタン
	colIt = deleteCollision(ball, colList, colIt);

	ImGui::TreePop();

	return colIt;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: CollisionEditorUi::isShawBoxEdit
//返り値	: 
//説明		: コリジョンボックスエディットを開くかどうか
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
//関数名	: CollisionEditorUi::isShawBallEdit
//返り値	: 
//説明		: コリジョンボールエディットを開くかどうか
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
//関数名	: CollisionEditorUi::deleteCollision
//返り値	: 
//説明		: コリジョン削除
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
//関数名	: CollisionEditorUi::editCollisionBall
//返り値	: 
//説明		: コリジョンボール編集
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
//関数名	: ModelEditorUi::init
//返り値	: 
//説明		: 初期化
//////////////////////////////////////////////////////////////////////////////
HRESULT ModelEditorUi::init()
{
	Player::create(new PlayerEdit);

	string currendDir = Directory::getCurrentDir("\\data\\model");
	mModelFileNameList = Directory::fileAllReferenceInDirectory(currendDir, ".x");
	floatDragRate = 0.01f;

	//地面
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
//関数名	: ModelEditorUi::uninit
//返り値	: 
//説明		: 終了
//////////////////////////////////////////////////////////////////////////////
void ModelEditorUi::uninit()
{
	mModelList.clear();
	Scene::releaseAll();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: ModelEditorUi::update
//返り値	: 
//説明		: 更新
//////////////////////////////////////////////////////////////////////////////
void ModelEditorUi::update()
{
	ImGui_ImplDX9_NewFrame();

	//案内
	setInfomationWindow();

	//編集ウィンドウ設定
	setEditWindow();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: ModelEditorUi::load
//返り値	: 
//説明		: 読み込み
//////////////////////////////////////////////////////////////////////////////
void ModelEditorUi::load()
{
	string openFileDir = Load::loadingFile(NULL,
		"データ読み込み",
		".mo\0",
		"MODELファイル(*.mo)\0");
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
//関数名	: ModelEditorUi::save
//返り値	: 
//説明		: 保存処理
//////////////////////////////////////////////////////////////////////////////
void ModelEditorUi::save(HWND hWnd)
{
	string	saveFileDir = Save::selectSaveFileDir(hWnd, "データ保存", ".mo", "TXTファイル(*.txt)\0*.txt\0");
	//SaveModel::saveFile(saveFileDir);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: ModelEditorUi::editModelAdd
//返り値	: 
//説明		: 編集モデル追加
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
//関数名	: ModelEditorUi::modelButton
//返り値	: 
//説明		: モデル追加ボタン表示
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
//関数名	: ModelEditorUi::setInfomationWindow
//返り値	: 
//説明		: 案内窓口設定
//////////////////////////////////////////////////////////////////////////////
void ModelEditorUi::setInfomationWindow(void)
{
	SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_FirstUseEver);
	Begin("Infomation");

	//カメラUI作成
	cameraUi();

	//ドラッグレートUI
	DragFloat("drag rate", &floatDragRate, 0.01f);

	//編集モデル追加ボタン
	if (CollapsingHeader("models"))
		modelButton();

	End();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: ModelEditorUi::setEditModelDeleteButton
//返り値	: 
//説明		: 編集モデル削除ボタン設定
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
//関数名	: ModelEditorUi::setParentCombo
//返り値	: 
//説明		: 親モデル設定コンボ
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
//関数名	: ModelEditorUi::getDisplayModelNameList
//返り値	: 
//説明		: 表示モデル名を文字列にしたものを取得
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
//関数名	: ModelEditorUi::setModelEditTool
//返り値	: 
//説明		: 編集ツール設定
//////////////////////////////////////////////////////////////////////////////
void ModelEditorUi::setModelEditTool(Scene * scene, int & id, int arrayNum)
{
	setTransformDrag(scene->getTransformAdd());
	setParentCombo(scene, id);
	setEditModelDeleteButton(scene, arrayNum);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: ModelEditorUi::setModelEditTool
//返り値	: 
//説明		: 編集ツール設定
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
//関数名	: ModelEditorUi::setEditWindow
//返り値	: 
//説明		: 編集ウィンドウ
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
