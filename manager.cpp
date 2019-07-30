/*****************************************************************************
manager.cpp
Aythor	: 上野　匠
Data	: 2017_05_11
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "ui.h"
#include "modelData.h"
#include "manager.h"
#include "textureManager.h"
#include "light.h"

//////////////////////////////////////////////////////////////////////////////
//静的メンバ変数初期化
//////////////////////////////////////////////////////////////////////////////
Renderer *Manager::mRenderer = NULL;
InputKeyboard *Manager::mKey = NULL;
InputMouse *Manager::mMouse = NULL;
Mode *Manager::mMode = new NullMode;
Fade *Manager::mFade = NULL;
CSound *Manager::mSound = NULL;
Ui	*Manager::mUi = NULL;

//////////////////////////////////////////////////////////////////////////////
//関数名	: init
//返り値	: 
//説明		: 初期化処理
//////////////////////////////////////////////////////////////////////////////
HRESULT	Manager::init	(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//レンダラー生成
	mRenderer = new Renderer;
	mRenderer->init(hWnd, bWindow);

	//サウンド設定
	mSound = new CSound;
	mSound->Init(hWnd);

	//キーボード設定
	mKey = new InputKeyboard;
	mKey->init(hInstance, hWnd);

	//マウス設定
	mMouse = new InputMouse;
	mMouse->init(hInstance, hWnd);


	//テクスチャ読み込み
	TextureManager::loadAllTextureInDir();

	//モデル読み込み
	ModelData::loadAllModel();

	MeshField::loadTex();

	//ライト設定
	Light::setLight(
		D3DXVECTOR3(0.f, 10.f, 10.f),
		D3DXVECTOR3(0.f, -0.5f, -1.f),
		D3DCOLOR_RGBA(255, 255, 255, 255),
		D3DCOLOR_RGBA(255, 255, 255, 255));

#ifdef GAME
	//持ち越しオブジェクト生成
	mFade = Fade::create(D3DXCOLOR(0.f, 0.f, 0.f, 1.f));
	mMouse->fixing(true);				//マウス固定
	ShowCursor(false);					//マウス非表示
	//ゲームモード設定
	mMode = Mode::create(new Game);
#endif // GAME

#ifdef MAP_EDITOR
	mUi = MapEditorUi::create();
#endif // MAP_EDITOR

#ifdef MOTION_EDITOR
	//UI設定
	mUi = new MotionEditorUi;
#endif // MOTION_EDITOR

#ifdef COLLISION_EDITOR
	mUi = new CollisionEditorUi;
#endif // COLLISION_EDITOR

#ifdef MODEL_EDITOR
	mUi = new ModelEditorUi;
#endif // MODEL_EDITOR

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: uninit
//返り値	: 
//説明		: 初期化処理
//////////////////////////////////////////////////////////////////////////////
void	Manager::uninit	( void )
{
	//レンダラー終了
	mRenderer->uninit();
	delete mRenderer;
	mRenderer = NULL;

	//テクスチャ破棄
	TextureManager::releaseAllTexture();

	//キーボード終了
	mKey->uninit();

	//マウス終了
	mMouse->uninit();

	//モデルデータ終了
	ModelData::modelDataAllClear();

#ifdef GAME
	//持ち越しオブジェクト終了
	mFade->uninit();
#endif // GAME

	//サウンド終了
	mSound->Uninit();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: update
//返り値	: 
//説明		: 初期化処理
//////////////////////////////////////////////////////////////////////////////
void	Manager::update	( void )
{
	//キーボード更新
	mKey->update();

	//マウス
	mMouse->update();

	//モードごと更新
	mMode->update();

	mRenderer->update();

#ifdef GAME
	//持ち越しオブジェクト更新
	mFade->update();
#endif // GAME


}

//////////////////////////////////////////////////////////////////////////////
//関数名	: draw
//返り値	: 
//説明		: 初期化処理
//////////////////////////////////////////////////////////////////////////////
void	Manager::draw	( void )
{
	//変数宣言
	LPDIRECT3DDEVICE9	device = getDevice();

	//ライトの影響off
	device->SetRenderState(D3DRS_LIGHTING, true);

	//描画
	mRenderer->draw();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: setMode
//返り値	: 
//説明		: モード設定
//////////////////////////////////////////////////////////////////////////////
void Manager::setMode(Mode * setMode)
{
	//今のモード終了
	mMode->uninit();
	delete mMode;

	//次のモード初期化
	mMode = setMode;
	mMode->init();
}
