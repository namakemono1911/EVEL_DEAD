#include "main.h"
#include "scene.h"
#include "transform.h"
#include "save.h"

#define ADD_DIR	"\\data"	//カレントディレクトリから追加のディレクトリ

//////////////////////////////////////////////////////////////////////////////
//関数名	: Save::selectSaveFileDir
//返り値	: 
//説明		: 保存先ディレクトリ取得
//////////////////////////////////////////////////////////////////////////////
string Save::selectSaveFileDir(HWND wnd, LPCSTR title, LPCSTR extension, LPCSTR extensionFilter)
{
	char saveFileDir[FILE_NAME_SIZE] = "\0";
	auto openFileName = settingOpenfile(wnd, title, extension, extensionFilter, ADD_DIR);
	openFileName.lpstrFile = saveFileDir;

	//保存処理
	if (!GetSaveFileName(&openFileName))
		return string("\0");

	return string(saveFileDir);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Save::saveTransform
//返り値	: 
//説明		: 位置情報保存
//////////////////////////////////////////////////////////////////////////////
void Save::saveTransform(FILE * fp, const Transform transform)
{
	fprintf(fp, "\tpos\t\t= %f %f %f\n", transform.pos.x, transform.pos.y, transform.pos.z);
	fprintf(fp, "\trot\t\t= %f %f %f\n", transform.rot.x, transform.rot.y, transform.rot.z);
	fprintf(fp, "\tsize\t= %f %f %f\n", transform.size.x, transform.size.y, transform.size.z);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Save::saveCollisionBox
//返り値	: 
//説明		: コリジョンボックス保存
//////////////////////////////////////////////////////////////////////////////
void Save::saveCollisionBox(FILE * fp, CollisionBox * col)
{
	auto	box = (CollisionBox*)col;
	fprintf(fp, "COLLISION_BOX\n");
	fprintf(fp, "{\n");
	saveTransform(fp, Transform(box->getPos(), box->getRot(), box->getSize()));
	fprintf(fp, "}\n");
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Save::saveCollisionBall
//返り値	: 
//説明		: コリジョンボール保存
//////////////////////////////////////////////////////////////////////////////
void Save::saveCollisionBall(FILE * fp, CollisionBall * col)
{
	auto	ball = (CollisionBall*)col;
	fprintf(fp, "COLLISION_BALL\n");
	fprintf(fp, "{\n");
	fprintf(fp, "\tpos\t\t= %f %f %f\n", ball->getPos().x, ball->getPos().y, ball->getPos().z);
	fprintf(fp, "\tlen\t\t= %f\n", ball->getLen());
	fprintf(fp, "}\n");
}
//////////////////////////////////////////////////////////////////////////////
//関数名	: Save::saveEachType
//返り値	: 
//説明		: タイプごと保存
//////////////////////////////////////////////////////////////////////////////
void Save::saveEachType(FILE * fp, Collision::TYPE type, Collision * col)
{
	switch (type)
	{
	case COLLISION_BOX:
		saveCollisionBox(fp, (CollisionBox*)col);
		break;

	case COLLISION_BALL:
		saveCollisionBall(fp, (CollisionBall*)col);
		break;
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Save::saveCollisionList
//返り値	: 
//説明		: コリジョンリスト保存
//////////////////////////////////////////////////////////////////////////////
void Save::saveCollisionList(FILE * fp, const list<Collision*> colList)
{
#pragma omp parallel for
	for (auto colIt = colList.begin(); colIt != colList.end(); ++colIt)
	{
		auto	col = *colIt;
		saveEachType(fp, col->getType(), col);
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Save::saveCollisionSceneHas
//返り値	: 
//説明		: シーンが持っているコリジョン保存
//////////////////////////////////////////////////////////////////////////////
void Save::saveCollision(FILE * fp, Scene& scene)
{
	auto	colManager = scene.getCollision();
	if (colManager == NULL)
		return;

	saveCollisionList(fp, *colManager->getCollisionList());
}