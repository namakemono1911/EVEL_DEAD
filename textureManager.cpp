/*****************************************************************************
textureManager.cpp
Aythor	: ���@��
Data	: 2017_02_14
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include <string>
#include "main.h"
#include "textureManager.h"
#include "renderer.h"

unordered_map<string, LPDIRECT3DTEXTURE9> TextureManager::mTexture;

//////////////////////////////////////////////////////////////////////////////
//�֐���	: TextureManager::loadAllTextureInDir
//�Ԃ�l	: 
//����		: �e�N�X�`���t�H���_�̃e�N�X�`���S�ēǂݍ���
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
//�֐���	: TextureManager::releaseAllTexture
//�Ԃ�l	: 
//����		: �e�N�X�`������S�Ĕj��
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
//�֐���	: TextureManager::createTexture
//�Ԃ�l	: 
//����		: �e�N�X�`�����쐬���ă}�b�v�ɓo�^
//////////////////////////////////////////////////////////////////////////////
HRESULT TextureManager::createTexture(sys::path path)
{
	auto relativePath = path.generic_string();
	relativePath.erase(0, relativePath.find("data"));

	if (FAILED(D3DXCreateTextureFromFile(Renderer::getDevice(), relativePath.c_str(), &mTexture[path.filename().string()])))
	{
		string text = relativePath + "���ǂݍ��߂܂���ł���";
		MessageBox(NULL, text.c_str(), "���f���e�N�X�`���G���[", MB_OK);
	}

	return S_OK;
}
