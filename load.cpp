/*****************************************************************************
load.cpp
Aythor	: 上野　匠
Data	: 2017_09_02
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include <vector>
#include "main.h"
#include "scene.h"
#include "sceneModel.h"
#include "motion.h"
#include "manager.h"
#include "load.h"

//////////////////////////////////////////////////////////////////////////////
//定数定義
//////////////////////////////////////////////////////////////////////////////
#define ADDITIONAL_DIR	"\\data"	//カレントディレクトリから追加のディレクトリ

//////////////////////////////////////////////////////////////////////////////
//関数名	: Load::loadingFile
//返り値	: 
//説明		: ファイルを読み込み
//////////////////////////////////////////////////////////////////////////////
string Load::loadingFile( HWND wnd, LPCSTR title, LPCSTR extension, LPCSTR extensionFilter)
{
	auto	openFile = 
		Directory::settingOpenfile(wnd, title,extension, extensionFilter, Directory::getCurrentDir("\\data"));
	char loadFileDir[FILE_NAME_SIZE] = "\0";
	openFile.lpstrFile = loadFileDir;

	if (!GetOpenFileName(&openFile))
	{
		MessageBox(NULL, "ファイルを読み込めませんでした", "error", MB_OK);
		return "NONE";
	}

	return string(loadFileDir);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Load::findWord
//返り値	: 
//説明		: テキストから単語を取得
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
//関数名	: Load::findOperator
//返り値	: 
//説明		: 演算子を探す
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
//関数名	: Load::skipToLine
//返り値	: 
//説明		: 1行飛ばす
//////////////////////////////////////////////////////////////////////////////
void Load::skipToLine(FILE * fp)
{
	char	search = '#';
	while(search != '\n' && search != '\0')
		fscanf(fp, "%c", &search);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Load::identifyWord
//返り値	: 
//説明		: 文字列リストにヒットするものがあるか判別
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
//関数名	: Load::setInt2()
//返り値	: 
//説明		: 連続するint型に代入
//////////////////////////////////////////////////////////////////////////////
void Load::setInt(FILE * fp, int * arg)
{
	fscanf(fp, "%d\n", arg);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Load::setInt2()
//返り値	: 
//説明		: 連続するint型に代入
//////////////////////////////////////////////////////////////////////////////
void Load::setInt2(FILE * fp, int * arg)
{
	fscanf(fp, "%d %d\n", arg, (arg + 1));
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Load::setFloat4()
//返り値	: 
//説明		: 連続するfloat型に代入
//////////////////////////////////////////////////////////////////////////////
void Load::setFloat4(FILE * fp, float * arg)
{
	fscanf(fp, "%f %f %f %f\n", arg, (arg + 1), (arg + 2), (arg + 2));
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Load::setFloat3()
//返り値	: 
//説明		: 連続するfloat型に代入
//////////////////////////////////////////////////////////////////////////////
void Load::setFloat3(FILE* fp, float * arg)
{
	fscanf(fp, "%f %f %f\n", arg, (arg + 1), (arg + 2));
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Load::setFloat2()
//返り値	: 
//説明		: 連続するfloat型に代入
//////////////////////////////////////////////////////////////////////////////
void Load::setFloat2(FILE * fp, float * arg)
{
	fscanf(fp, "%f %f\n", arg, (arg + 1));
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Load::setFloat()
//返り値	: 
//説明		: float型に代入
//////////////////////////////////////////////////////////////////////////////
void Load::setFloat(FILE * fp, float * arg)
{
	fscanf(fp, "%f\n", arg);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Load::setString()
//返り値	: 
//説明		: string型に代入
//////////////////////////////////////////////////////////////////////////////
void Load::setString(FILE * fp, string & str)
{
	char work[256];
	fscanf(fp, "%s\n", work);
	str = work;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Load::operatorSelectInt2()
//返り値	: 
//説明		: 演算子によって処理
//////////////////////////////////////////////////////////////////////////////
void Load::operatorSelectInt(FILE * fp, int * vec)
{
	if (Load::findOperator(fp) == "=")
		setInt(fp, vec);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Load::operatorSelectInt2()
//返り値	: 
//説明		: 演算子によって処理
//////////////////////////////////////////////////////////////////////////////
void Load::operatorSelectInt2(FILE * fp, int * vec)
{
	if (Load::findOperator(fp) == "=")
		setInt2(fp, vec);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Load::operatorSelectFloat4()
//返り値	: 
//説明		: 演算子によって処理
//////////////////////////////////////////////////////////////////////////////
void Load::operatorSelectFloat4(FILE * fp, float * vec)
{
	if (Load::findOperator(fp) == "=")
		setFloat4(fp, vec);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Load::operatorSelectFloat3()
//返り値	: 
//説明		: 演算子によって処理
//////////////////////////////////////////////////////////////////////////////
void Load::operatorSelectFloat3(FILE * fp, float * vec)
{
	if (Load::findOperator(fp) == "=")
		setFloat3(fp, vec);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Load::operatorSelectFloat2()
//返り値	: 
//説明		: 演算子によって処理
//////////////////////////////////////////////////////////////////////////////
void Load::operatorSelectFloat2(FILE * fp, float * vec)
{
	if (Load::findOperator(fp) == "=")
		setFloat2(fp, vec);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Load::operatorSelectFloat()
//返り値	: 
//説明		: 演算子によって処理
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