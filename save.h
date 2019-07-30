/*****************************************************************************
save.h
Aythor	: ���@��
Data	: 2017_08_27
=============================================================================
Updata

*****************************************************************************/
#ifndef SAVE_H
#define	SAVE_H
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include <string>
#include "directory.h"

//////////////////////////////////////////////////////////////////////////////
//�萔��`
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//Save�N���X��`
//////////////////////////////////////////////////////////////////////////////
class Scene;
class Transform;

class Save : public Directory
{
public:
	Save(){}
	~Save(){}

	static string	selectSaveFileDir(HWND wnd, LPCSTR title, LPCSTR extension, LPCSTR extensionFilter);
	static void		saveTransform(FILE *fp, const Transform transform);
	static void		saveCollision(FILE* fp, Scene& scene);

private:
	static void		saveCollisionList(FILE * fp, const list<Collision*> colList);
	static void		saveEachType(FILE * fp, Collision::TYPE type, Collision * col);
	static void		saveCollisionBall(FILE * fp, CollisionBall * col);
	static void		saveCollisionBox(FILE * fp, CollisionBox * col);

	static OPENFILENAME	mOpenFileName;					//���O��t���ĕۑ��̐ݒ�
	static char			mSaveFileDir[FILE_NAME_SIZE];	//�t�@�C���̕ۑ���
};

class SaveMap : public Save
{
public:
	SaveMap(){}
	~SaveMap(){}

	static void saveFile(string fileName);

private:
	static void			saveObject(FILE *fp);
	static void			saveField(FILE *fp);

};

class SaveModel : public Save
{
public:
	SaveModel(){}
	~SaveModel(){}

	static void saveFile(string fileName);

private:
	static void			saveModelInfomation(string destinationDir);
	//static void			savePartsName(FILE *fp, const Parts *part);
	//static void			savePartsInfomation(FILE *fp, const Parts *part);
};
#endif // !SAVE_H
