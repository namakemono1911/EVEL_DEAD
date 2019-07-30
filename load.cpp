/*****************************************************************************
load.cpp
Aythor	: ���@��
Data	: 2017_09_02
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include <vector>
#include "main.h"
#include "scene.h"
#include "sceneModel.h"
#include "motion.h"
#include "manager.h"
#include "load.h"

//////////////////////////////////////////////////////////////////////////////
//�萔��`
//////////////////////////////////////////////////////////////////////////////
#define ADDITIONAL_DIR	"\\data"	//�J�����g�f�B���N�g������ǉ��̃f�B���N�g��

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Load::loadingFile
//�Ԃ�l	: 
//����		: �t�@�C����ǂݍ���
//////////////////////////////////////////////////////////////////////////////
string Load::loadingFile( HWND wnd, LPCSTR title, LPCSTR extension, LPCSTR extensionFilter)
{
	auto	openFile = 
		Directory::settingOpenfile(wnd, title,extension, extensionFilter, Directory::getCurrentDir("\\data"));
	char loadFileDir[FILE_NAME_SIZE] = "\0";
	openFile.lpstrFile = loadFileDir;

	if (!GetOpenFileName(&openFile))
	{
		MessageBox(NULL, "�t�@�C����ǂݍ��߂܂���ł���", "error", MB_OK);
		return "NONE";
	}

	return string(loadFileDir);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Load::findWord
//�Ԃ�l	: 
//����		: �e�L�X�g����P����擾
//////////////////////////////////////////////////////////////////////////////
string Load::findWord(FILE *fp)
{
	char	order = '\0';
	string	statement;
	bool	shouldSkip = true;

	while (order != '\n')
	{
		fscanf(fp, "%c", &order);
		if (order =='\n')
			return statement;

		if (shouldSkip == true && (order == ' ' || order == '\t'))
			continue;

		if (shouldSkip == false && (order == ' ' || order == '\t'))
			return statement;

		if (order == '#')
		{
			skipToLine(fp);
			return statement;
		}
		if (order == '\0')
			return string("EOF");

		shouldSkip = false;
		statement.push_back(order);
	}

	return statement;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Load::findOperator
//�Ԃ�l	: 
//����		: ���Z�q��T��
//////////////////////////////////////////////////////////////////////////////
string Load::findOperator(FILE *fp)
{
	char order = '\0';
	string	statement;

	while (order != '\n')
	{
		fscanf(fp, "%c", &order);
		if (order == '+' || order == '-' || order == '*' || order == '/' || order == '=')
			statement.push_back(order);
		if (order == '=')
			return statement;
		if (order == ' ' || order == '\t')
			continue;
	}

	return statement;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Load::skipToLine
//�Ԃ�l	: 
//����		: 1�s��΂�
//////////////////////////////////////////////////////////////////////////////
void Load::skipToLine(FILE * fp)
{
	char	search = '#';
	while(search != '\n' && search != '\0')
		fscanf(fp, "%c", &search);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Load::identifyWord
//�Ԃ�l	: 
//����		: �����񃊃X�g�Ƀq�b�g������̂����邩����
//////////////////////////////////////////////////////////////////////////////
string Load::identifyWord(vector<string> wordList, string str)
{
#pragma omp parallel for
	for (UINT i = 0; i < wordList.size(); i++)
		if (wordList[i] == str)
			return str;

	return "\0";
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Load::setInt2()
//�Ԃ�l	: 
//����		: �A������int�^�ɑ��
//////////////////////////////////////////////////////////////////////////////
void Load::setInt(FILE * fp, int * arg)
{
	fscanf(fp, "%d\n", arg);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Load::setInt2()
//�Ԃ�l	: 
//����		: �A������int�^�ɑ��
//////////////////////////////////////////////////////////////////////////////
void Load::setInt2(FILE * fp, int * arg)
{
	fscanf(fp, "%d %d\n", arg, (arg + 1));
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Load::setFloat4()
//�Ԃ�l	: 
//����		: �A������float�^�ɑ��
//////////////////////////////////////////////////////////////////////////////
void Load::setFloat4(FILE * fp, float * arg)
{
	fscanf(fp, "%f %f %f %f\n", arg, (arg + 1), (arg + 2), (arg + 2));
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Load::setFloat3()
//�Ԃ�l	: 
//����		: �A������float�^�ɑ��
//////////////////////////////////////////////////////////////////////////////
void Load::setFloat3(FILE* fp, float * arg)
{
	fscanf(fp, "%f %f %f\n", arg, (arg + 1), (arg + 2));
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Load::setFloat2()
//�Ԃ�l	: 
//����		: �A������float�^�ɑ��
//////////////////////////////////////////////////////////////////////////////
void Load::setFloat2(FILE * fp, float * arg)
{
	fscanf(fp, "%f %f\n", arg, (arg + 1));
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Load::setFloat()
//�Ԃ�l	: 
//����		: float�^�ɑ��
//////////////////////////////////////////////////////////////////////////////
void Load::setFloat(FILE * fp, float * arg)
{
	fscanf(fp, "%f\n", arg);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Load::setString()
//�Ԃ�l	: 
//����		: string�^�ɑ��
//////////////////////////////////////////////////////////////////////////////
void Load::setString(FILE * fp, string & str)
{
	char work[256];
	fscanf(fp, "%s\n", work);
	str = work;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Load::operatorSelectInt2()
//�Ԃ�l	: 
//����		: ���Z�q�ɂ���ď���
//////////////////////////////////////////////////////////////////////////////
void Load::operatorSelectInt(FILE * fp, int * vec)
{
	if (Load::findOperator(fp) == "=")
		setInt(fp, vec);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Load::operatorSelectInt2()
//�Ԃ�l	: 
//����		: ���Z�q�ɂ���ď���
//////////////////////////////////////////////////////////////////////////////
void Load::operatorSelectInt2(FILE * fp, int * vec)
{
	if (Load::findOperator(fp) == "=")
		setInt2(fp, vec);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Load::operatorSelectFloat4()
//�Ԃ�l	: 
//����		: ���Z�q�ɂ���ď���
//////////////////////////////////////////////////////////////////////////////
void Load::operatorSelectFloat4(FILE * fp, float * vec)
{
	if (Load::findOperator(fp) == "=")
		setFloat4(fp, vec);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Load::operatorSelectFloat3()
//�Ԃ�l	: 
//����		: ���Z�q�ɂ���ď���
//////////////////////////////////////////////////////////////////////////////
void Load::operatorSelectFloat3(FILE * fp, float * vec)
{
	if (Load::findOperator(fp) == "=")
		setFloat3(fp, vec);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Load::operatorSelectFloat2()
//�Ԃ�l	: 
//����		: ���Z�q�ɂ���ď���
//////////////////////////////////////////////////////////////////////////////
void Load::operatorSelectFloat2(FILE * fp, float * vec)
{
	if (Load::findOperator(fp) == "=")
		setFloat2(fp, vec);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Load::operatorSelectFloat()
//�Ԃ�l	: 
//����		: ���Z�q�ɂ���ď���
//////////////////////////////////////////////////////////////////////////////
void Load::operatorSelectFloat(FILE * fp, float * vec)
{
	if (Load::findOperator(fp) == "=")
		setFloat(fp, vec);
}

void Load::operatorSelectString(FILE * fp, string & str)
{
	if (Load::findOperator(fp) == "=")
		setString(fp, str);
}

/*
##############################################################################################################################################
LoadModel class
##############################################################################################################################################
*/