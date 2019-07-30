/*****************************************************************************
directory.h
Aythor	: 上野　匠
Data	: 2017_09_02
=============================================================================
Updata

*****************************************************************************/
#ifndef DIRECTORY_H
#define DIRECTORY_H
//////////////////////////////////////////////////////////////////////////////
//インクルード
//////////////////////////////////////////////////////////////////////////////
#include <filesystem>
#include <string>
#include <list>
#include <vector>

//////////////////////////////////////////////////////////////////////////////
//ネームスペース
//////////////////////////////////////////////////////////////////////////////
namespace sys = std::tr2::sys;

//////////////////////////////////////////////////////////////////////////////
// 定数定義
//////////////////////////////////////////////////////////////////////////////
#define FILE_NAME_SIZE	(256)
#define DELIMITER		("\0")

//////////////////////////////////////////////////////////////////////////////
//クラス宣言
//////////////////////////////////////////////////////////////////////////////
class Directory
{
public:
	Directory(){}
	~Directory(){}

	static string			getCurrentDir(string addDir = "\0");
	static OPENFILENAME		settingOpenfile(HWND wnd, LPCSTR title, LPCSTR extension, LPCSTR extensionFilter, string initialDir = "\0");
	static vector<sys::path>	fileAllReferenceInDirectory(const string& dirName, const string& extension);

private:
	static vector<sys::path>	directorySearch(sys::path dir, string extension);

};

#endif // !DIRECTORY_H
