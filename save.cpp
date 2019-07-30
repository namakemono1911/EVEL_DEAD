#include "main.h"
#include "scene.h"
#include "transform.h"
#include "save.h"

#define ADD_DIR	"\\data"	//�J�����g�f�B���N�g������ǉ��̃f�B���N�g��

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Save::selectSaveFileDir
//�Ԃ�l	: 
//����		: �ۑ���f�B���N�g���擾
//////////////////////////////////////////////////////////////////////////////
string Save::selectSaveFileDir(HWND wnd, LPCSTR title, LPCSTR extension, LPCSTR extensionFilter)
{
	char saveFileDir[FILE_NAME_SIZE] = "\0";
	auto openFileName = settingOpenfile(wnd, title, extension, extensionFilter, ADD_DIR);
	openFileName.lpstrFile = saveFileDir;

	//�ۑ�����
	if (!GetSaveFileName(&openFileName))
		return string("\0");

	return string(saveFileDir);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Save::saveTransform
//�Ԃ�l	: 
//����		: �ʒu���ۑ�
//////////////////////////////////////////////////////////////////////////////
void Save::saveTransform(FILE * fp, const Transform transform)
{
	fprintf(fp, "\tpos\t\t= %f %f %f\n", transform.pos.x, transform.pos.y, transform.pos.z);
	fprintf(fp, "\trot\t\t= %f %f %f\n", transform.rot.x, transform.rot.y, transform.rot.z);
	fprintf(fp, "\tsize\t= %f %f %f\n", transform.size.x, transform.size.y, transform.size.z);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Save::saveCollisionBox
//�Ԃ�l	: 
//����		: �R���W�����{�b�N�X�ۑ�
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
//�֐���	: Save::saveCollisionBall
//�Ԃ�l	: 
//����		: �R���W�����{�[���ۑ�
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
//�֐���	: Save::saveEachType
//�Ԃ�l	: 
//����		: �^�C�v���ƕۑ�
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
//�֐���	: Save::saveCollisionList
//�Ԃ�l	: 
//����		: �R���W�������X�g�ۑ�
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
//�֐���	: Save::saveCollisionSceneHas
//�Ԃ�l	: 
//����		: �V�[���������Ă���R���W�����ۑ�
//////////////////////////////////////////////////////////////////////////////
void Save::saveCollision(FILE * fp, Scene& scene)
{
	auto	colManager = scene.getCollision();
	if (colManager == NULL)
		return;

	saveCollisionList(fp, *colManager->getCollisionList());
}