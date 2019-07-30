/*****************************************************************************
manager.h
Aythor	: 上野　匠
Data	: 2017_05_11
=============================================================================
Updata

*****************************************************************************/
#ifndef MANAGER_H
#define MANAGER_H
//////////////////////////////////////////////////////////////////////////////
//インクルード
//////////////////////////////////////////////////////////////////////////////
#include "renderer.h"
#include "scene.h"
#include "input.h"
#include "sound.h"
#include "outlaw2D.h"
#include "fade.h"
#include "mode.h"

//////////////////////////////////////////////////////////////////////////////
//定数定義
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//前方宣言
//////////////////////////////////////////////////////////////////////////////
class Renderer;
class Input;
class InputKeyboard;
class InputMouse;
class Player;
class Mode;
class CSound;
class Ui;

//////////////////////////////////////////////////////////////////////////////
//クラス宣言
//////////////////////////////////////////////////////////////////////////////
class Manager
{
public:
	Manager(){}
	~Manager(){}

	HRESULT	init	(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void	uninit	(void);
	void	update	(void);
	void	draw	(void);

	//ゲッター
	static Renderer				*getRenderer(void){return mRenderer;}
	static LPDIRECT3DDEVICE9	getDevice(void){return mRenderer->getDevice();}
	static InputKeyboard		*getKeyboard(void){return mKey;}
	static InputMouse			*getMouse(void){return mMouse;}
	static Mode					*getMode(void){return mMode;}
	static Fade					*getFade(void){return mFade;}
	static CSound				*getSound(void){return mSound;}
	static Ui					*getUi(void) {return mUi;}

	//セッター
	static void	setMode(Mode *setMode);

private:
	static Renderer			*mRenderer;		//レンダラー
	static InputKeyboard	*mKey;			//キーボード
	static InputMouse		*mMouse;		//マウス
	static Mode				*mMode;			//モード
	static Fade				*mFade;			//シーン遷移後も持ち越されるオブジェクトデータ
	static CSound			*mSound;		//サウンド
	static Ui				*mUi;			//ui
};

#endif