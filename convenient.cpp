/*****************************************************************************
convenient.cpp
Aythor	: 上野　匠
Data	: 2017_08_18
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "transform.h"
#include "convenient.h"

//////////////////////////////////////////////////////////////////////////////
//関数名	: getDirFile()
//
//引数		: dirName	ディレクトリパス
//			: ext		拡張子
//
//返り値	: ファイル名リスト
//説明		: ディレクトリ内の指定拡張子ファイルリスト取得
//////////////////////////////////////////////////////////////////////////////
std::list<std::string> Conveni::getDirFile(const std::string dirName, const std::string ext)
{
	HANDLE	find;
	WIN32_FIND_DATA	findData;
	std::list<std::string>	fileName;

	std::string	search = dirName + "/*." + ext;

	find = FindFirstFile(search.c_str(), &findData);

	//エラーメッセージ
	if (find == INVALID_HANDLE_VALUE)
	{
		std::string error = dirName + "フォルダが開けませんでした。";
		MessageBox(NULL, error.c_str(), "error", MB_OK);
		return std::list<std::string>();
	}

	//ファイル探索
	while (FindNextFile(find, &findData))
	{
		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{

		}
		else
		{
			fileName.push_back(findData.cFileName);
		}
	}

	FindClose(find);
	return fileName;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: getCharPosition()
//
//引数		: str		対象文字列
//			: target	探したい文字
//
//返り値	: ファイル名リスト
//説明		: ディレクトリ内の指定拡張子ファイルリスト取得
//////////////////////////////////////////////////////////////////////////////
int Conveni::getCharPosition(const string str, const string target)
{
	for (int i = 0; str[i] != '\0'; i++)
		for (int j = 0; target[j] != '\0'; j++)
			if (str[i] == target[j])
				return i;

	return -1;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Conveni::setMatrix
//返り値	: 
//説明		: 通常行列をデバイスに設定
//////////////////////////////////////////////////////////////////////////////
Dmtx Conveni::setMatrix(Dvec3 pos, Dvec3 rot, Dvec3 size)
{
	//変数宣言
	D3DXMATRIX	world;				//ワールド行列
	D3DXMATRIX	scaleMtx;			//スケール
	D3DXMATRIX	rotMtx;				//回転行列
	D3DXMATRIX	moveMtx;			//平行移動行列

									//行列設定
	D3DXMatrixIdentity(&world);
	D3DXMatrixScaling(&scaleMtx, size.x, size.y, size.z);
	D3DXMatrixRotationYawPitchRoll(&rotMtx, rot.x, rot.y, rot.z);
	D3DXMatrixTranslation(&moveMtx, pos.x, pos.y, pos.z);

	//行列合成
	world *= scaleMtx * rotMtx * moveMtx;

	return world;
}

Dmtx Conveni::setMatrix(Transform trans)
{
	return setMatrix(trans.pos, trans.rot, trans.size);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Conveni::setQuatenionMatrixToDevice
//返り値	: 
//説明		: クォータニオンを使った行列をデバイスに設定
//////////////////////////////////////////////////////////////////////////////
Dmtx Conveni::setQuatenionMatrix(Dvec3 pos, Dvec3 quatenion, Dvec3 size)
{
	//変数宣言
	DMtx	world;
	DMtx	scaleMtx;
	DMtx	rotMtx;
	DMtx	moveMtx;
	DQuate	quatenionMtx(quatenion.x, quatenion.y, quatenion.z, 0);

	//行列設定
	D3DXMatrixIdentity(&world);
	D3DXMatrixScaling(&scaleMtx, size.x, size.y, size.z);
	D3DXMatrixRotationQuaternion(&rotMtx, &quatenionMtx);
	D3DXMatrixTranslation(&moveMtx, pos.x, pos.y, pos.z);

	//行列合成
	world *= scaleMtx * rotMtx * moveMtx;

	//行列をデバイスに設定
	return world;
}
