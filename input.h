/*****************************************************************************
input.cpp
Aythor	: 上野　匠
Data	: 2017_05_26
=============================================================================
Updata

*****************************************************************************/
#ifndef INPUT_H
#define INPUT_H
//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include <dinput.h>

//////////////////////////////////////////////////////////////////////////////
//定数定義
//////////////////////////////////////////////////////////////////////////////
#define NUM_MOUSE_MAX		(8)		// マウスの最大数
#define	NUM_KEY_MAX			(256)	// キーの最大数
#define	LIMIT_COUNT_REPEAT	(20)	// リピートカウントリミッター

#define MOUSE_LEFT			(0)		//左クリック
#define MOUSE_RIGHT			(1)		//右クリック
#define MOUSE_CENTER		(2)		//ホイールボタン

//////////////////////////////////////////////////////////////////////////////
//クラス定義
//////////////////////////////////////////////////////////////////////////////
class Input
{
public:
	Input() :mDIDevice(nullptr) {}
	~Input() {}

	virtual HRESULT init(HINSTANCE inst);
	virtual void	uninit(void);
	virtual HRESULT	update(void) = 0;

protected:
	static LPDIRECTINPUT8	mDinput;
	LPDIRECTINPUTDEVICE8 mDIDevice;
};

class	InputKeyboard :public Input
{
public:
	InputKeyboard(){}
	~InputKeyboard(){}
	HRESULT	init(HINSTANCE hInstance, HWND hWnd);
	void	uninit(void);
	HRESULT	update(void);
	bool getPress(int nKey);
	bool getTrigger(int nKey);
	bool getRepeat(int nKey);
	bool getRelease(int nKey);

private:
	BYTE	mKeyState[NUM_KEY_MAX];			// キーボードの入力情報ワーク
	BYTE	mKeyStateTrigger[NUM_KEY_MAX];	// キーボードのトリガー情報ワーク
	BYTE	mKeyStateRelease[NUM_KEY_MAX];	// キーボードのリリース情報ワーク
	BYTE	mKeyStateRepeat[NUM_KEY_MAX];		// キーボードのリピート情報ワーク
	int		mKeyStateRepeatCnt[NUM_KEY_MAX];	// キーボードのリピートカウンタ
};

class InputMouse : public Input
{
public:
	InputMouse();
	~InputMouse() {}

	HRESULT init(HINSTANCE inst, HWND wnd);
	void	uninit(void);
	HRESULT	update(void);

	BOOL	getPress(const int button);
	BOOL	getTrigger(const int button);
	BOOL	getRelease(const int button);
	LONG	getHweelX(void) {}
	LONG	getHweelY(void) {}
	LONG	getHweelZ(void) {}
	vec2	getPos(void) { return vec2((float)mPosMouse.x, (float)mPosMouse.y); }
	vec2	getMoving(void) { return vec2((float)mMouseState.lX, (float)mMouseState.lY); }
	LONG	getWheel(void) { return mMouseState.lZ;}
	void	fixing(bool flag);
	void	setCenter(void);
	//const POINT	*getPos(void){return &mPosMouse;}

private:
	DIMOUSESTATE2	mMouseState;			//マウス
	DIMOUSESTATE2	mMouseStateTrigger;		//トリガーの状態
	DIMOUSESTATE2	mMouseStateRelease;		//マウスを放したか
	POINT			mPosMouse;				//マウス座標
	bool			mFixing;				//trueで位置固定
};

#endif