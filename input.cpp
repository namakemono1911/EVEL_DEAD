/*****************************************************************************
input.cpp
Aythor	: 上野　匠
Data	: 2017_05_26
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "input.h"

//////////////////////////////////////////////////////////////////////////////
//静的メンバ変数初期化
//////////////////////////////////////////////////////////////////////////////
LPDIRECTINPUT8		Input::mDinput = NULL;

//////////////////////////////////////////////////////////////////////////////
//関数名	: Input::init
//返り値	: 
//説明		: 初期化
//////////////////////////////////////////////////////////////////////////////
HRESULT	Input::init(HINSTANCE inst)
{
	HRESULT hr = S_FALSE;

	//DirectInputオブジェクトの作成
	if (!mDinput)
	{
		hr = DirectInput8Create(inst,
			DIRECTINPUT_VERSION,
			IID_IDirectInput8,
			(void**)&mDinput, NULL);
	}

	return hr;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Input::uninit
//返り値	: 
//説明		: 終了処理
//////////////////////////////////////////////////////////////////////////////
void	Input::uninit(void)
{
	//デバイスオブジェクトの解放
	if (mDIDevice)
	{
		mDIDevice->Unacquire();
		mDIDevice->Release();
		mDIDevice = NULL;
	}

	if (mDinput)
	{
		mDinput->Release();
		mDinput = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: InputKeyboard::initKeyboard
//返り値	: 
//説明		: キーボードの更新
//////////////////////////////////////////////////////////////////////////////
HRESULT InputKeyboard::init(HINSTANCE hInstance, HWND hWnd)
{
	//入力処理の初期化
	Input::init(hInstance);

	// 入力処理の初期化
	if (FAILED(Input::init(hInstance)))
	{
		MessageBox(hWnd, "DirectInputオブジェクトが作れねぇ！", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// デバイスの作成
	if (FAILED(mDinput->CreateDevice(GUID_SysKeyboard, &mDIDevice, NULL)))
	{
		MessageBox(hWnd, "キーボードがねぇ！", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// データフォーマットを設定
	if (FAILED(mDIDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		MessageBox(hWnd, "キーボードのデータフォーマットを設定できませんでした。", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	if (FAILED(mDIDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		MessageBox(hWnd, "キーボードの協調モードを設定できませんでした。", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
	mDIDevice->Acquire();

	return	S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: InputKeyboard::uninitKeyboard
//返り値	: 
//説明		: キーボードの更新
//////////////////////////////////////////////////////////////////////////////
void InputKeyboard::uninit(void)
{
	if (mDIDevice != NULL)
	{// 入力デバイス(キーボード)の開放
	 // キーボードへのアクセス権を開放(入力制御終了)
		mDIDevice->Unacquire();

		mDIDevice->Release();
		mDIDevice = NULL;
	}

	Input::uninit();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: InputKeyboard::updateKeyboard
//返り値	: 
//説明		: キーボードの更新
//////////////////////////////////////////////////////////////////////////////
HRESULT InputKeyboard::update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];

	// デバイスからデータを取得
	if (SUCCEEDED(mDIDevice->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for (int nCnKey = 0; nCnKey < NUM_KEY_MAX; nCnKey++)
		{
			//キートリガー情報の取得
			mKeyStateTrigger[nCnKey] = (mKeyState[nCnKey] ^ aKeyState[nCnKey]) & aKeyState[nCnKey];
			mKeyStateRelease[nCnKey] = (mKeyState[nCnKey] ^ aKeyState[nCnKey]) & mKeyState[nCnKey];


			if (aKeyState[nCnKey] & 0x80)
			{
				if (mKeyStateRepeatCnt[nCnKey] < LIMIT_COUNT_REPEAT)
				{
					mKeyStateRepeatCnt[nCnKey]++;

					if (mKeyState[nCnKey] == 1 || mKeyStateRepeatCnt[nCnKey] >= LIMIT_COUNT_REPEAT)
					{
						mKeyStateRepeat[nCnKey] = aKeyState[nCnKey];
					}
				}
				else
				{
					mKeyStateRepeat[nCnKey] = 0;
				}
			}
			else
			{
				mKeyStateRepeat[nCnKey] = 0;
				mKeyStateRepeatCnt[nCnKey] = 0;
			}

			// キープレス情報を保存
			mKeyState[nCnKey] = aKeyState[nCnKey];
		}
	}
	else
	{
		// キーボードへのアクセス権を取得
		mDIDevice->Acquire();
	}

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: InputKeyboard::getPress
//返り値	: 
//説明		: キーボードが押されたら
//////////////////////////////////////////////////////////////////////////////
bool InputKeyboard::getPress(int nKey)
{
	return (mKeyState[nKey] & 0x80) ? true : false;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: InputKeyboard::getTrigger
//返り値	: 
//説明		: キーボードが押されたら
//////////////////////////////////////////////////////////////////////////////
bool InputKeyboard::getTrigger(int nKey)
{
	return (mKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: InputKeyboard::getRepeat
//返り値	: 
//説明		: キーボードが押されたら
//////////////////////////////////////////////////////////////////////////////
bool InputKeyboard::getRepeat(int nKey)
{
	return (mKeyStateRepeat[nKey] & 0x80) ? true : false;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: InputKeyboard::getRelease
//返り値	: 
//説明		: キーボードが押されたら
//////////////////////////////////////////////////////////////////////////////
bool InputKeyboard::getRelease(int nKey)
{
	return (mKeyStateRelease[nKey] & 0x80) ? true : false;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: InputMouse::InputMouse
//返り値	: 
//説明		: コンストラクタ
//////////////////////////////////////////////////////////////////////////////
InputMouse::InputMouse()
{
	ZeroMemory(&mMouseState, sizeof(mMouseState));
	ZeroMemory(&mMouseStateTrigger, sizeof(mMouseStateTrigger));
	ZeroMemory(&mMouseStateRelease, sizeof(mMouseStateRelease));
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: InputMouse::init
//返り値	: 
//説明		: 初期化処理
//////////////////////////////////////////////////////////////////////////////
HRESULT InputMouse::init(HINSTANCE inst, HWND wnd)
{
	HRESULT hr;

	//入力処理の初期化
	Input::init(inst);

	//デバイスオブジェクトを作成
	hr = mDinput->CreateDevice(GUID_SysMouse, &mDIDevice, NULL);
	if (FAILED(hr) || mDIDevice == NULL)
	{
		MessageBox(wnd, "マウスがないよ", "エラー", MB_ICONWARNING);
		return hr;
	}

	//データフォーマットを設定
	if (FAILED(mDIDevice->SetDataFormat(&c_dfDIMouse2)))
	{
		MessageBox(wnd, "キーボードのデータフォーマットを設定できませんでした。", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	//協調モードを設定（フォアグラウンド&非排他モード）
	hr = mDIDevice->SetCooperativeLevel(
		wnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if (FAILED(hr))
	{
		MessageBox(wnd, "マウスの協調モードが設定できませんでした", "error", MB_ICONWARNING);
		return hr;
	}

	//デバイスの設定
	DIPROPDWORD	dipdw;

	dipdw.diph.dwSize = sizeof(dipdw);
	dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = DIPROPAXISMODE_REL;

	hr = mDIDevice->SetProperty(DIPROP_AXISMODE, &dipdw.diph);

	//マウスへのアクセス権取得
	mDIDevice->Acquire();

	return hr;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: InputMouse::uninit
//返り値	: 
//説明		: 終了処理
//////////////////////////////////////////////////////////////////////////////
void	InputMouse::uninit(void)
{
	//入力処理の解放
	Input::uninit();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: InputMouse::update
//返り値	: 
//説明		: 更新
//////////////////////////////////////////////////////////////////////////////
HRESULT	InputMouse::update(void)
{
	HRESULT	hr;
	DIMOUSESTATE2	mouseState;

	if (!mDIDevice)
	{
		return S_FALSE;
	}

	//デバイスからデータ取得
	hr = mDIDevice->GetDeviceState(sizeof(mouseState), &mouseState);
	if (SUCCEEDED(hr))
	{
		//マウス固定
		if (mFixing == true)
		{
			POINT	pos;	//マウス座標
			RECT	winPos;	//ウィンドウズ座標

							//現在のマウス座標取得
			GetCursorPos(&pos);
			ScreenToClient(GetFocus(), &pos);

			mMouseState.lX = pos.x - mPosMouse.x;
			mMouseState.lY = pos.y - mPosMouse.y;

			GetWindowRect(GetFocus(), &winPos);
			SetCursorPos(winPos.left + (int)SCREEN_WIDTH / 2, winPos.top + (int)SCREEN_HEIGHT / 2);
		}

		//マウストリガー
		mMouseStateTrigger.lX = ((mMouseState.lX ^ mMouseState.lX) & mouseState.lX);
		mMouseStateTrigger.lY = ((mMouseState.lY ^ mMouseState.lY) & mouseState.lY);
		mMouseStateTrigger.lZ = ((mMouseState.lZ ^ mMouseState.lZ) & mouseState.lZ);

		//マウスリリース
		mMouseStateRelease.lX = ((mMouseState.lX ^ mMouseState.lX) & mMouseState.lX);
		mMouseStateRelease.lY = ((mMouseState.lY ^ mMouseState.lY) & mMouseState.lY);
		mMouseStateRelease.lX = ((mMouseState.lZ ^ mMouseState.lZ) & mMouseState.lZ);

		//状態更新
		for (int i = 0; i < 8; i++)
		{
			mMouseStateTrigger.rgbButtons[i] =
				((mMouseState.rgbButtons[i] ^ mouseState.rgbButtons[i]) & mouseState.rgbButtons[i]);

			mMouseStateRelease.rgbButtons[i] =
				((mMouseState.rgbButtons[i] ^ mouseState.rgbButtons[i]) & mMouseState.rgbButtons[i]);
		}

		mMouseState = mouseState;

		//スクリーン座標取得
		GetCursorPos(&mPosMouse);
	}
	else
	{
		mDIDevice->Acquire();
	}

	return hr;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: InputMouse::getPressMouse
//返り値	: 
//説明		: マウスのプレス状態取得
//////////////////////////////////////////////////////////////////////////////
BOOL InputMouse::getPress(const int button)
{
	return (mMouseState.rgbButtons[button] & 0x80) ? true : false;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: InputMouse::getTriggerMouse
//返り値	: 
//説明		: マウスのトリガー状態取得
//////////////////////////////////////////////////////////////////////////////
BOOL InputMouse::getTrigger(const int button)
{
	return (mMouseStateTrigger.rgbButtons[button] & 0x80) ? true : false;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: InputMouse::getRleaseMouse
//返り値	: 
//説明		: マウスのリリース状態取得
//////////////////////////////////////////////////////////////////////////////
BOOL InputMouse::getRelease(const int button)
{
	return (mMouseStateRelease.rgbButtons[button] & 0x80) ? true : false;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: InputMouse::fixing
//返り値	: 
//説明		: マウスの座標固定
//////////////////////////////////////////////////////////////////////////////
void InputMouse::fixing(bool flag)
{
	//変数宣言
	POINT Mpos;

	//マウス固定に設定
	mFixing = flag;

	if (mFixing == true)
	{
		//マウス移動
		setCenter();

		//現在のマウス座標取得
		GetCursorPos(&Mpos);
		ScreenToClient(GetFocus(), &Mpos);
		mPosMouse.x = Mpos.x;
		mPosMouse.y = Mpos.y;
	}
	else
	{
		//マウス移動値初期化
		mMouseState.lX = 0;
		mMouseState.lY = 0;
		mMouseState.lZ = 0;
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: InputMouse::setCenter
//返り値	: 
//説明		: マウスをウィンドウの中央に移動
//////////////////////////////////////////////////////////////////////////////
void InputMouse::setCenter(void)
{
	//変数宣言
	RECT	WinPos;		//デスクトップ上のウインドウの座標

	GetWindowRect(GetFocus(), &WinPos);
	SetCursorPos((int)WinPos.left + (int)SCREEN_WIDTH / 2, (int)WinPos.top + (int)SCREEN_HEIGHT / 2);
}
