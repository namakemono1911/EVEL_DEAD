/*****************************************************************************
right.h
Aythor	: 上野　匠
Data	: 2017_04_26
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//ヘッダーインクルード
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "light.h"
#include "renderer.h"

//////////////////////////////////////////////////////////////////////////////
//静的メンバ変数初期化
//////////////////////////////////////////////////////////////////////////////
Light *Light::obj[MAX_LIGHT] = {NULL};
unsigned int	Light::mNum = 0;

//////////////////////////////////////////////////////////////////////////////
//関数名	: Light::init
//返り値	: 
//説明		: 座標設定
//////////////////////////////////////////////////////////////////////////////
void	Light::init	(D3DXVECTOR3 pos, D3DXVECTOR3 vecLight, D3DXCOLOR ambient, D3DXCOLOR diffuse, int num )
{
	//変数宣言
	LPDIRECT3DDEVICE9	device;

	//デバイス取得
	device = Renderer::getDevice();

	//ID代入
	mId = num;

	//ライティング初期化
	mLight.Type = D3DLIGHT_DIRECTIONAL;
	mLight.Diffuse = diffuse;					//平行光源の色
	mLight.Ambient = ambient;					//環境光源の色
	mLight.Position = pos;											//ライトの位置
	//vecDir = D3DXVECTOR3(0.f, -300.f, 450.f);						//平行光源の向き
	D3DXVec3Normalize((D3DXVECTOR3*)&mLight.Direction, &vecLight);	//ベクトルの正規化

	device->SetLight(mId, &mLight);									//デバイスに0番目のライトを設定
	device->LightEnable(mId, TRUE);									//0番ライトON
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Light::setLight
//返り値	: 
//説明		: 初期化
//////////////////////////////////////////////////////////////////////////////
Light	*Light::setLight	(D3DXVECTOR3 pos, D3DXVECTOR3 vecLight, D3DXCOLOR ambient, D3DXCOLOR diffuse)
{
	for (int i = 0; i < MAX_LIGHT; i++)
	{
		if (obj[i] == NULL)
		{
			obj[i] = new Light;
			obj[i]->init(pos, vecLight, ambient, diffuse, i);
			mNum++;
			return obj[i];
		}
	}

	return NULL;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Light::setPos
//返り値	: 
//説明		: 座標設定
//////////////////////////////////////////////////////////////////////////////
void	Light::setPos	( D3DXVECTOR3 pos )
{
	//変数宣言
	LPDIRECT3DDEVICE9	device;		//デバイス情報

	//デバイス情報取得
	device = Renderer::getDevice();

	//座標設定
	mLight.Position = pos;

	//ライト設定
	device->SetLight(mId, &mLight);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Light::release
//返り値	: 
//説明		: ライト削除
//////////////////////////////////////////////////////////////////////////////
void Light::releaseAll(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9	device;
	device = Renderer::getDevice();

	for (int i = 0; i < MAX_LIGHT; i++)
	{
		if (obj[i] != NULL)
		{
			device->LightEnable(obj[i]->mId, false);								//mId番ライトOff
			delete obj[i];
			obj[i] = NULL;
		}
	}
}
