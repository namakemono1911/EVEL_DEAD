/*****************************************************************************
map.cpp
Aythor	: 上野　匠
Data	: 2017_11_19
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
// ヘッダーインクルード
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
//関数名	: Stage::init()
//返り値	: 
//説明		: 初期化
//////////////////////////////////////////////////////////////////////////////
HRESULT Stage::init(void)
{
	setObjType(OBJECT);

	return E_NOTIMPL;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Stage::uninit()
//返り値	: 
//説明		: 終了
//////////////////////////////////////////////////////////////////////////////
void Stage::uninit(void)
{
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Stage::update()
//返り値	: 
//説明		: 更新
//////////////////////////////////////////////////////////////////////////////
void Stage::update(void)
{
	mMatrix = Conveni::setMatrix(mTransform.pos, mTransform.rot, mTransform.size);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Stage::draw()
//返り値	: 
//説明		: 描画
//////////////////////////////////////////////////////////////////////////////
void Stage::draw(void)
{
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Stage::draw()
//返り値	: 
//説明		: 描画
//////////////////////////////////////////////////////////////////////////////
void Stage::loadMapFile(string mapFileName)
{
	objectPlacement(mapFileName);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Stage::saveMap()
//返り値	: 
//説明		: ステージ情報保存
//////////////////////////////////////////////////////////////////////////////
bool Stage::saveMap(string saveDir)
{
	if (saveDir == "\0")
		return false;

	FILE *fp = fopen(saveDir.c_str(), "w");
	if (fp == NULL)
	{
		saveDir += "を保存できませんでした";
		MessageBox(NULL, saveDir.c_str(), "error", MB_OK);
		return false;
	}

	//オブジェクトとフィールド保存
	saveObject(fp);
	saveField(fp);

	fclose(fp);
	MessageBox(NULL, "保存完了", "メッセージ", MB_OK);

	return true;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Stage::create()
//返り値	: 
//説明		: 生成
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
//関数名	: Stage::objectPlacement()
//返り値	: 
//説明		: オブジェクト配置
//////////////////////////////////////////////////////////////////////////////
Scene* Stage::objectPlacement(string fileName)
{
	FILE	*fp = fopen(fileName.c_str(), "r");
	if (fp == NULL)
	{
		MessageBox(NULL, "マップファイルを読み込めませんでした。", "error", MB_OK);
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
//関数名	: Stage::objectSetting()
//返り値	: 
//説明		: オブジェクト設置
//////////////////////////////////////////////////////////////////////////////
Scene * Stage::objectSetting(string objectName)
{
	auto	obj = SceneModel::create(objectName.c_str());
	mObjectList.push_back(obj);
	setChild(obj);
	return mChildren.back();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Stage::objectSetting()
//返り値	: 
//説明		: オブジェクト設置
//////////////////////////////////////////////////////////////////////////////
void Stage::fieldSetting(MeshField * field)
{
	mFieldList.push_back(field);
	setChild(field);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Stage::saveObject()
//返り値	: 
//説明		: オブジェクト保存
//////////////////////////////////////////////////////////////////////////////
void Stage::saveObject(FILE * fp)
{
	//ヘッダーコメント
	fprintf(fp, "#####################################################\n");
	fprintf(fp, "# オブジェクトの配置\n");
	fprintf(fp, "#####################################################\n");

	for (auto& scene : Scene::getTypeList(Scene::OBJECT))
	{
		//テキスト書き込み内容
		fprintf(fp, "SET_OBJECT %s\n{\n", scene->getMyName().c_str());

		//位置情報保存
		Save::saveTransform(fp, scene->getTransform());

		//コリジョン情報保存
		Save::saveCollision(fp, *scene);

		fprintf(fp, "}\n\n");
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Stage::saveField()
//返り値	: 
//説明		: フィールド保存
//////////////////////////////////////////////////////////////////////////////
void Stage::saveField(FILE * fp)
{
	//ヘッダーコメント
	fprintf(fp, "#####################################################\n");
	fprintf(fp, "# フィールド(地面）の配置\n");
	fprintf(fp, "#####################################################\n");

	//リスト探索
	for (auto& scene : Scene::getTypeList(Scene::FIELD))
	{
		//情報収集
		auto field = (MeshField*)scene;

		if (field->getObjType() != Scene::FIELD)
			continue;

		Transform	transform = field->getTransform();
		Dcolor color = *field->getColorAddr();
		Tyle	numTyle = field->getNumTyle();
		string	texName = field->getTextureNameList()[field->getTextureId()];

		fprintf(fp, "SET_FIELD %s\n{\n", texName.c_str());

		//位置情報保存
		fprintf(fp, "\tpos\t\t= %f %f %f\n", transform.pos.x, transform.pos.y, transform.pos.z);
		fprintf(fp, "\trot\t\t= %f %f %f\n", transform.rot.x, transform.rot.y, transform.rot.z);
		fprintf(fp, "\tsize\t= %f %f\n", field->getTyleSize().x, field->getTyleSize().y);

		//タイル数保存
		fprintf(fp, "\tnumTyle\t= %d %d\n", numTyle.x, numTyle.y);

		//頂点色保存
		fprintf(fp, "\tcolor\t= %f %f %f %f\n", color.r, color.g, color.b, color.a);

		fprintf(fp, "}\n\n");
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Stage::objectAssignmentTarget()
//返り値	: 
//説明		: 命令によって処理
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
//関数名	: Stage::fieldAssignmentTarget()
//返り値	: 
//説明		: 命令によって処理
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
//関数名	: Stage::stageAssignmentTarget()
//返り値	: 
//説明		: 命令によって処理
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
//関数名	: Stage::objectInstructionSearch()
//返り値	: 
//説明		: 命令探索
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
//関数名	: Stage::fieldInstructionSearch()
//返り値	: 
//説明		: 命令探索
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
//関数名	: Stage::stageInstructionSearch()
//返り値	: 
//説明		: 命令探索
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
//関数名	: Stage::setObject()
//返り値	: 
//説明		: オブジェクト設定
//////////////////////////////////////////////////////////////////////////////
auto Stage::setObject(FILE * fp)
{
	auto obj = objectSetting(Load::findWord(fp));
	objectInstructionSearch(fp, obj);

	return obj;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Stage::setField()
//返り値	: 
//説明		: フィールド設定
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
//関数名	: Stage::settingBranch()
//返り値	: 
//説明		: ステージ設定
//////////////////////////////////////////////////////////////////////////////
void Stage::setStage(FILE * fp)
{
	stageInstructionSearch(fp);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Stage::settingBranch()
//返り値	: 
//説明		: 種類選択
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
