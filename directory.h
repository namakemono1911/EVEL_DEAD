/*****************************************************************************
directory.h
Aythor	: ���@��
Data	: 2017_09_02
=============================================================================
Updata

*****************************************************************************/
#ifndef DIRECTORY_H
#define DIRECTORY_H
//////////////////////////////////////////////////////////////////////////////
//�C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include <filesystem>
#include <string>
#include <list>
#include <vector>

//////////////////////////////////////////////////////////////////////////////
//�l�[���X�y�[�X
//////////////////////////////////////////////////////////////////////////////
namespace sys = std::tr2::sys;

//////////////////////////////////////////////////////////////////////////////
// �萔��`
//////////////////////////////////////////////////////////////////////////////
#define FILE_NAME_SIZE	(256)
#define DELIMITER		("\0")

//////////////////////////////////////////////////////////////////////////////
//�N���X�錾
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
