/*****************************************************************************
textureManager.cpp
Aythor	: 上野　匠
Data	: 2017_02_14
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//ファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include <string>
#include "main.h"
#include "textureManager.h"
#include "renderer.h"

unordered_map<string, LPDIRECT3DTEXTURE9> TextureManager::mTexture;

//////////////////////////////////////////////////////////////////////////////
//関数名	: TextureManager::loadAllTextureInDir
//返り値	: 
//説明		: テクスチャフォルダのテクスチャ全て読み込み
//////////////////////////////////////////////////////////////////////////////
HRESULT TextureManager::loadAllTextureInDir()
{
	auto dir = Directory::getCurrentDir("\\data\\texture");
	auto pathList = Directory::fileAllReferenceInDirectory(dir, ".png\0.jpg");

	for (auto path : pathList)
	{
		if (FAILED(createTexture(path)))
			return E_FAIL;
	}

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: TextureManager::releaseAllTexture
//返り値	: 
//説明		: テクスチャ情報を全て破棄
//////////////////////////////////////////////////////////////////////////////
HRESULT TextureManager::releaseAllTexture()
{
	for (auto& texture : mTexture)
		if (texture.second != NULL)
			texture.second->Release();

	mTexture.clear();

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: TextureManager::createTexture
//返り値	: 
//説明		: テクスチャを作成してマップに登録
//////////////////////////////////////////////////////////////////////////////
HRESULT TextureManager::createTexture(sys::path path)
{
	auto relativePath = path.generic_string();
	relativePath.erase(0, relativePath.find("data"));

	if (FAILED(D3DXCreateTextureFromFile(Renderer::getDevice(), relativePath.c_str(), &mTexture[path.filename().string()])))
	{
		string text = relativePath + "が読み込めませんでした";
		MessageBox(NULL, text.c_str(), "モデルテクスチャエラー", MB_OK);
	}

	return S_OK;
}
