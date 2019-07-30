/*****************************************************************************
main.cpp
Aythor	: 上野　匠
Data	: 2017_07_28
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include <dinput.h>
#include <tchar.h>
#include "renderer.h"
#include "manager.h"
#include "resource1.h"

//////////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
//////////////////////////////////////////////////////////////////////////////
ATOM	setRegister(HINSTANCE hInstance);
HWND	myWindow(HINSTANCE hInstance);
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//////////////////////////////////////////////////////////////////////////////
//グローバル変数
//////////////////////////////////////////////////////////////////////////////
HWND g_hWnd;
int g_nCountFPS = NULL;	//FPSカウンター

#ifdef _DEBUG	//_DEBUG
extern LRESULT ImGui_ImplDX9_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LPD3DXFONT g_pFont = NULL;	//フォントへのインターフェース
#endif //_DEBUG

//////////////////////////////////////////////////////////////////////////////
//関数名	: WinMain
//返り値	: 
//説明		: ウィンドウの設定
//////////////////////////////////////////////////////////////////////////////
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	setRegister(hInstance);			//レジスタクラス設定
	g_hWnd = myWindow(hInstance);	//ウィンドウ生成

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	ShowWindow(g_hWnd, SW_SHOWDEFAULT);
	UpdateWindow(g_hWnd);

	//マネージャー生成
	Manager	*manager = new Manager;
	if (FAILED(manager->init(hInstance, g_hWnd, TRUE)))
	{
		MessageBox(g_hWnd, "初期化失敗", "エラー", MB_RIGHT);
		return 0;
	}

	//ループ処理
	DWORD dwFrameCount = 0;
	DWORD dwCurrentTime = 0;
	DWORD dwExecLastTime = timeGetTime();
	DWORD dwFPSLastTime = timeGetTime();

	//メッセージループ
	for (;;)
	{
		//処理時間取得
		dwCurrentTime = timeGetTime();

		//FPS取得
		if ((dwCurrentTime - dwFPSLastTime) >= 500)
		{
			g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
			dwFPSLastTime = dwCurrentTime;
			dwFrameCount = 0;
		}

		if (dwCurrentTime - dwExecLastTime >= 1000 / 60)
		{
			//処理した時間取得
			dwExecLastTime = dwCurrentTime;

			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
			{

				//Windowsの処理
				if (msg.message == WM_QUIT)
				{
					break;
				}
				else
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}

			//Directxの処理
			manager->update();
			manager->draw();

			dwFrameCount++;
		}
	}

	UnregisterClass(_T("ImGui Example"), hInstance);

	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: setRegister
//返り値	: 
//説明		: レジスタの設定
//////////////////////////////////////////////////////////////////////////////
ATOM	setRegister(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	
	wcex.cbSize = sizeof(WNDCLASSEX);					//WNDCLASSEXのメモリサイズを指定
	wcex.style = CS_HREDRAW | CS_VREDRAW;				//表示するウィンドウのスタイルを設定
	wcex.lpfnWndProc = WndProc;							//ウィンドウプロシージャのアドレス（関数名）を指定する
	wcex.cbClsExtra = 0;								//通常は使用しないので"0"を指定
	wcex.cbWndExtra = 0;								//通常は使用しないので"0"を指定
	wcex.hInstance = hInstance;							//WinMainのパラメータのインスタンスハンドル
	wcex.hIcon = NULL;									//使用するアイコンを指定（Windowsが持っている
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);			//マウスカーソルを指定
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);	//ウィンドウのクライアント領域の背景色を指定
	wcex.lpszClassName = CLASS_NAME;					//ウィンドウクラスの名前
	wcex.hIconSm = NULL;								//小さいアイコンが指定された場合の情報を記述
	wcex.lpszMenuName = NULL;							//メニューバーの設定

#ifndef GAME
	wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);		//メニューバーの設定
#endif // !GAME


	//ウィンドウクラスの登録
	return RegisterClassEx(&wcex);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: myWindow
//返り値	: 
//説明		: ウィンドウの生成
//////////////////////////////////////////////////////////////////////////////
HWND	myWindow(HINSTANCE hInstance)
{
	//デスクトップのサイズ取得
	RECT cr = { 0, 0, (LONG)SCREEN_WIDTH, (LONG)SCREEN_HEIGHT };

#ifndef GAME
	cr = { 0, -10, (LONG)SCREEN_WIDTH, (LONG)SCREEN_HEIGHT };
#endif // !GAME

	DWORD style = WS_OVERLAPPEDWINDOW;
	AdjustWindowRect(&cr, style, FALSE);
	RECT dr;
	GetWindowRect(GetDesktopWindow(), &dr);

	int ww = cr.right - cr.left;				//ウィンドウの幅
	int wh = cr.bottom - cr.top;				//ウィンドウの高さ

	int dw = dr.right - dr.left;				//デスクトップの幅
	int dh = dr.bottom - dr.top;				//デスクトップの高さ

	int wx = ww > dw ? 0 : (dw - ww) / 2;		//デスクトップの表示位置X
	int wy = wh > dh ? 0 : (dh - wh) / 2;		//デスクトップの表示位置Y

	style = WS_OVERLAPPEDWINDOW ^ (WS_MAXIMIZEBOX | WS_THICKFRAME);

	return CreateWindowEx(0,		//拡張ウィンドウスタイル
		CLASS_NAME, WINDOW_NAME,	//ウィンドウクラスの名前
		style,						//◎ウィンドウスタイル
		wx,							//ウィンドウの左上X座標
		wy,							//ウィンドウの左上Y座標
		ww,							//ウィンドウの幅
		wh,							//ウィンドウの高さ
		NULL,						//親ウィンドウのハンドル
		NULL,						//メニューハンドルまたは子ウィンドウID
		hInstance,					//インスタンス
		NULL);						//ウィンドウ作成データ
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: WndProc
//返り値	: 
//説明		: ウィンドウプロシージャ
//			  (CALLBACK : Win32API関数を呼び出すときの規約
//			  hWnd		: ウィンドウのハンドル
//			  uMsg		: メッセージの識別子
//			  wParam	: メッセージの最初のパラメータ
//			  lParam	: メッセージの2番目のパラメータ
//////////////////////////////////////////////////////////////////////////////
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
#ifdef _DEBUG
	if (ImGui_ImplDX9_WndProcHandler(g_hWnd, msg, wParam, lParam))
		return true;
#endif // _DEBUG

	switch (msg)
	{
	case WM_SIZE:
		/*{
		auto d3dpp = Manager::getRenderer()->getWindowConfig();
		auto device = Manager::getRenderer()->getDevice();
		if (device != NULL && wParam != SIZE_MINIMIZED)
		{
		ImGui_ImplDX9_InvalidateDeviceObjects();
		d3dpp.BackBufferWidth = LOWORD(lParam);
		d3dpp.BackBufferHeight = HIWORD(lParam);
		HRESULT hr = device->Reset(&d3dpp);
		if (hr == D3DERR_INVALIDCALL)
		IM_ASSERT(0);
		ImGui_ImplDX9_CreateDeviceObjects();
		}
		}*/

	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
		break;

	case WM_CLOSE:
	{
		UINT messageResult = MessageBox(hWnd, "保存されていない内容は破棄されます", "警告", MB_OKCANCEL | MB_ICONWARNING);

		if (messageResult != IDOK)
			return 0;
		else
			DefWindowProc(hWnd, msg, wParam, lParam);
	}

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
		{
			ShowCursor(TRUE);
			auto ID = MessageBox(NULL, "終了しますか？", "終了メッセージ", MB_YESNO | MB_ICONEXCLAMATION);
			if (ID == IDYES)
			{
				DestroyWindow(hWnd);
			}
			else
			{
				ShowCursor(FALSE);
			}
		}
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: getWnd
//戻り値	: ウィンドウハンドル
//説明		: ウィンドウハンドル取得
//////////////////////////////////////////////////////////////////////////////
HWND getWnd(void)
{
	return g_hWnd;
}

#ifdef _DEBUG
//=============================================================================
// FPS取得
//=============================================================================
int GetFPS(void)
{
	return g_nCountFPS;
}
#endif

/*

                           Aperture Science

                           .,-:;//;:=,
                        .  :H@@@MM@M#H/.,+%:,
                     ,/X+  +M@@M@MM%=,-%HMMM@X/ ,
                   -+@MM;  $M@@MH+-,;XMMMM@MMMM@+-
                  ;@M@@M-  XM@X;. -+XXXXXHHH@M@M#@/.
                 ,%MM@@MH  ,@%=           .---=-=:=,.
                 =@#@@@MX  .,             -%HX$$%%%+;
                =-./@M@M$                  .;@MMMM@MM:
                X@/ -$MM/                    .+MM@@@M$
               ,@M@H: :@:                    . =X#@@@@-
               ,@@@MMX, .                    /H- ;@M@M=
               .H@@@@M@+,                    %MM+..%#$.
                /MMMM@MMH/.                   XM@MH; =;
                 /%+%$XHH@$=              , .H@@@@MX,
                  .=--------.           -%H.,@@@@@MX,
                  .%MM@@@HHHXX$$$%+- .:$MMX =M@@MM%.
                    =XMMM@MM@MM#H;,-+HMM@M+ /MMMX=
                      =%@M@M#@$-.=$@MM@@@M; %M%=
                        ,:+$+-,/H#MMMMMMM@= =
                              =++%%%%+/:-
*/