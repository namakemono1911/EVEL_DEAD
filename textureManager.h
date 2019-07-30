/*****************************************************************************
textureManager.cpp
Aythor	: ���@��
Data	: 2017_02_14
=============================================================================
Updata

*****************************************************************************/
#ifndef TEXTURE_MANAGER
//////////////////////////////////////////////////////////////////////////////
//�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include <unordered_map>
#include "directory.h"


class TextureManager
{
public:
	TextureManager() {}
	~TextureManager() {}

	static HRESULT	loadAllTextureInDir();
	static auto		getTexture(string textureName) { return mTexture[textureName]; }
	static HRESULT	releaseAllTexture();

private:
	static HRESULT createTexture(sys::path path);

	static unordered_map<string, LPDIRECT3DTEXTURE9> mTexture;
};

#endif // !TEXTURE_MANAGER
