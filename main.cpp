/*****************************************************************************
main.cpp
Aythor	: ���@��
Data	: 2017_07_28
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include <dinput.h>
#include <tchar.h>
#include "renderer.h"
#include "manager.h"
#include "resource1.h"

//////////////////////////////////////////////////////////////////////////////
//�v���g�^�C�v�錾
//////////////////////////////////////////////////////////////////////////////
ATOM	setRegister(HINSTANCE hInstance);
HWND	myWindow(HINSTANCE hInstance);
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
//////////////////////////////////////////////////////////////////////////////
HWND g_hWnd;
int g_nCountFPS = NULL;	//FPS�J�E���^�[

#ifdef _DEBUG	//_DEBUG
extern LRESULT ImGui_ImplDX9_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LPD3DXFONT g_pFont = NULL;	//�t�H���g�ւ̃C���^�[�t�F�[�X
#endif //_DEBUG

//////////////////////////////////////////////////////////////////////////////
//�֐���	: WinMain
//�Ԃ�l	: 
//����		: �E�B���h�E�̐ݒ�
//////////////////////////////////////////////////////////////////////////////
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	setRegister(hInstance);			//���W�X�^�N���X�ݒ�
	g_hWnd = myWindow(hInstance);	//�E�B���h�E����

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	ShowWindow(g_hWnd, SW_SHOWDEFAULT);
	UpdateWindow(g_hWnd);

	//�}�l�[�W���[����
	Manager	*manager = new Manager;
	if (FAILED(manager->init(hInstance, g_hWnd, TRUE)))
	{
		MessageBox(g_hWnd, "���������s", "�G���[", MB_RIGHT);
		return 0;
	}

	//���[�v����
	DWORD dwFrameCount = 0;
	DWORD dwCurrentTime = 0;
	DWORD dwExecLastTime = timeGetTime();
	DWORD dwFPSLastTime = timeGetTime();

	//���b�Z�[�W���[�v
	for (;;)
	{
		//�������Ԏ擾
		dwCurrentTime = timeGetTime();

		//FPS�擾
		if ((dwCurrentTime - dwFPSLastTime) >= 500)
		{
			g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
			dwFPSLastTime = dwCurrentTime;
			dwFrameCount = 0;
		}

		if (dwCurrentTime - dwExecLastTime >= 1000 / 60)
		{
			//�����������Ԏ擾
			dwExecLastTime = dwCurrentTime;

			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
			{

				//Windows�̏���
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

			//Directx�̏���
			manager->update();
			manager->draw();

			dwFrameCount++;
		}
	}

	UnregisterClass(_T("ImGui Example"), hInstance);

	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: setRegister
//�Ԃ�l	: 
//����		: ���W�X�^�̐ݒ�
//////////////////////////////////////////////////////////////////////////////
ATOM	setRegister(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	
	wcex.cbSize = sizeof(WNDCLASSEX);					//WNDCLASSEX�̃������T�C�Y���w��
	wcex.style = CS_HREDRAW | CS_VREDRAW;				//�\������E�B���h�E�̃X�^�C����ݒ�
	wcex.lpfnWndProc = WndProc;							//�E�B���h�E�v���V�[�W���̃A�h���X�i�֐����j���w�肷��
	wcex.cbClsExtra = 0;								//�ʏ�͎g�p���Ȃ��̂�"0"���w��
	wcex.cbWndExtra = 0;								//�ʏ�͎g�p���Ȃ��̂�"0"���w��
	wcex.hInstance = hInstance;							//WinMain�̃p�����[�^�̃C���X�^���X�n���h��
	wcex.hIcon = NULL;									//�g�p����A�C�R�����w��iWindows�������Ă���
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);			//�}�E�X�J�[�\�����w��
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);	//�E�B���h�E�̃N���C�A���g�̈�̔w�i�F���w��
	wcex.lpszClassName = CLASS_NAME;					//�E�B���h�E�N���X�̖��O
	wcex.hIconSm = NULL;								//�������A�C�R�����w�肳�ꂽ�ꍇ�̏����L�q
	wcex.lpszMenuName = NULL;							//���j���[�o�[�̐ݒ�

#ifndef GAME
	wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);		//���j���[�o�[�̐ݒ�
#endif // !GAME


	//�E�B���h�E�N���X�̓o�^
	return RegisterClassEx(&wcex);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: myWindow
//�Ԃ�l	: 
//����		: �E�B���h�E�̐���
//////////////////////////////////////////////////////////////////////////////
HWND	myWindow(HINSTANCE hInstance)
{
	//�f�X�N�g�b�v�̃T�C�Y�擾
	RECT cr = { 0, 0, (LONG)SCREEN_WIDTH, (LONG)SCREEN_HEIGHT };

#ifndef GAME
	cr = { 0, -10, (LONG)SCREEN_WIDTH, (LONG)SCREEN_HEIGHT };
#endif // !GAME

	DWORD style = WS_OVERLAPPEDWINDOW;
	AdjustWindowRect(&cr, style, FALSE);
	RECT dr;
	GetWindowRect(GetDesktopWindow(), &dr);

	int ww = cr.right - cr.left;				//�E�B���h�E�̕�
	int wh = cr.bottom - cr.top;				//�E�B���h�E�̍���

	int dw = dr.right - dr.left;				//�f�X�N�g�b�v�̕�
	int dh = dr.bottom - dr.top;				//�f�X�N�g�b�v�̍���

	int wx = ww > dw ? 0 : (dw - ww) / 2;		//�f�X�N�g�b�v�̕\���ʒuX
	int wy = wh > dh ? 0 : (dh - wh) / 2;		//�f�X�N�g�b�v�̕\���ʒuY

	style = WS_OVERLAPPEDWINDOW ^ (WS_MAXIMIZEBOX | WS_THICKFRAME);

	return CreateWindowEx(0,		//�g���E�B���h�E�X�^�C��
		CLASS_NAME, WINDOW_NAME,	//�E�B���h�E�N���X�̖��O
		style,						//���E�B���h�E�X�^�C��
		wx,							//�E�B���h�E�̍���X���W
		wy,							//�E�B���h�E�̍���Y���W
		ww,							//�E�B���h�E�̕�
		wh,							//�E�B���h�E�̍���
		NULL,						//�e�E�B���h�E�̃n���h��
		NULL,						//���j���[�n���h���܂��͎q�E�B���h�EID
		hInstance,					//�C���X�^���X
		NULL);						//�E�B���h�E�쐬�f�[�^
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: WndProc
//�Ԃ�l	: 
//����		: �E�B���h�E�v���V�[�W��
//			  (CALLBACK : Win32API�֐����Ăяo���Ƃ��̋K��
//			  hWnd		: �E�B���h�E�̃n���h��
//			  uMsg		: ���b�Z�[�W�̎��ʎq
//			  wParam	: ���b�Z�[�W�̍ŏ��̃p�����[�^
//			  lParam	: ���b�Z�[�W��2�Ԗڂ̃p�����[�^
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
		UINT messageResult = MessageBox(hWnd, "�ۑ�����Ă��Ȃ����e�͔j������܂�", "�x��", MB_OKCANCEL | MB_ICONWARNING);

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
			auto ID = MessageBox(NULL, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO | MB_ICONEXCLAMATION);
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
//�֐���	: getWnd
//�߂�l	: �E�B���h�E�n���h��
//����		: �E�B���h�E�n���h���擾
//////////////////////////////////////////////////////////////////////////////
HWND getWnd(void)
{
	return g_hWnd;
}

#ifdef _DEBUG
//=============================================================================
// FPS�擾
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