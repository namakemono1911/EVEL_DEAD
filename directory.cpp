/*****************************************************************************
directory.cpp
Aythor	: 上野　匠
Data	: 2017_09_02
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include <sstream>
#include "main.h"
#include "directory.h"

//////////////////////////////////////////////////////////////////////////////
//関数名	: Directory::getCurrentDir
//返り値	: 
//説明		: カレントディレクトリ取得
//////////////////////////////////////////////////////////////////////////////
string Directory::getCurrentDir(string addDir)
{
	char currentDir[FILE_NAME_SIZE];
	GetCurrentDirectory(sizeof(currentDir), currentDir);
	string	dir(currentDir);

	if (addDir != "\0")
		dir += addDir;

	return dir;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Directory::settingOpenfile
//返り値	: 
//説明		: オブジェクト保存
//////////////////////////////////////////////////////////////////////////////
OPENFILENAME Directory::settingOpenfile(HWND wnd, LPCSTR title, LPCSTR extension, LPCSTR extensionFilter, string initialDir)
{
	//設定
	OPENFILENAME	openFileName;

	ZeroMemory(&openFileName, sizeof(openFileName));
	openFileName.lStructSize = sizeof(OPENFILENAME);
	openFileName.hwndOwner = wnd;
	openFileName.nMaxFile = FILE_NAME_SIZE;
	openFileName.lpstrDefExt = extension;
	openFileName.lpstrFilter = extensionFilter;
	openFileName.lpstrTitle = title;
	openFileName.Flags = OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;
	openFileName.lpstrInitialDir = initialDir.c_str();

	return openFileName;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Directory::fileAllReferenceInDirectory
//返り値	: 
//説明		: 指定ディレクトリ内のファイルを全てリスト化
//////////////////////////////////////////////////////////////////////////////
vector<sys::path> Directory::fileAllReferenceInDirectory(const string & dirName, const string & extension)
{
	vector<sys::path>	pathList;

	sys::path path(dirName); // 列挙の起点
	pathList = directorySearch(path, extension);
	/*list<string> extensionList;
	string buff;
	auto pos = extension.find(DELETE);

	while (pos != UINT_MAX)
	{
		extensionList.push_back(extension.data() + pos);
		extension.find(DELIMITER, pos + sizeof(DELIMITER));
	}*/

	return pathList;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Directory::directorySearch
//返り値	: 
//説明		: ディレクトリ内捜索
//////////////////////////////////////////////////////////////////////////////
vector<sys::path> Directory::directorySearch(sys::path dir, string extension)
{
	vector<sys::path>	pathList;

	for (auto it = sys::directory_iterator(dir); it != sys::directory_iterator(); ++it)
	{
		sys::path target = *it;

		if (sys::is_directory(target))
		{
			auto list = directorySearch(target, extension);
			for (auto listIt = list.begin(); listIt != list.end(); ++listIt)
				pathList.push_back(*listIt);
		}

		if (sys::is_regular_file(target))
		{
			if (extension == ".*")
				pathList.push_back(target);
			else if (target.extension().string() == extension)
				pathList.push_back(target);
		}
	}

	return pathList;
}
