/*****************************************************************************
load.h
Aythor	: 上野　匠
Data	: 2017_09_02
=============================================================================
Updata

*****************************************************************************/
#ifndef LOAD_H
#define LOAD_H
//////////////////////////////////////////////////////////////////////////////
//インクルード
//////////////////////////////////////////////////////////////////////////////
#include "directory.h"

//////////////////////////////////////////////////////////////////////////////
//クラス宣言
//////////////////////////////////////////////////////////////////////////////
class ModelParts;

class Load : public Directory
{
public:
	Load(){}
	~Load(){}

	static string	loadingFile(HWND wnd, LPCSTR title, LPCSTR extension, LPCSTR extensionFilter);
	static string	findWord(FILE *fp);
	static string	findOperator(FILE *fp);
	static void		skipToLine(FILE *fp);
	static string	identifyWord(vector<string> wordList, string str);
	static void		setInt(FILE* fp, int* arg);
	static void		setInt2(FILE* fp, int* arg);
	static void		setFloat4(FILE* fp, float* arg);
	static void		setFloat3(FILE* fp, float* arg);
	static void		setFloat2(FILE* fp, float* arg);
	static void		setFloat(FILE* fp, float* arg);
	static void		setString(FILE* fp, string& str);
	static void		operatorSelectInt(FILE* fp, int* vec);
	static void		operatorSelectInt2(FILE* fp, int* vec);
	static void		operatorSelectFloat4(FILE* fp, float* vec);
	static void		operatorSelectFloat3(FILE* fp, float* vec);
	static void		operatorSelectFloat2(FILE* fp, float* vec);
	static void		operatorSelectFloat(FILE* fp, float* vec);
	static void		operatorSelectString(FILE* fp, string& str);
};

class LoadModel : public Load
{
public:
	LoadModel(){}
	~LoadModel(){}

	static	void		loadKeyframe(ModelParts *parts, string fileDir);

private:
};

#endif // !LOAD_H
