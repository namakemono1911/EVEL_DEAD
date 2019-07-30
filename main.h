/*****************************************************************************
main.h
Aythor	: 上野　匠
Data	: 2017_04_19
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include <Windows.h>
#include <time.h>
#include <stdio.h>
#include <d3dx9.h>
#include <windows.h>
#include <xaudio2.h>
#define	DisableLoad	(0x0800)
#include "vec.h"

//ライブラリリンク
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")		//システム時刻取得に必要
#pragma comment (lib, "dinput8.lib")	//入力装置ライブラリ

//////////////////////////////////////////////////////////////////////////////
//定数定義
//////////////////////////////////////////////////////////////////////////////
//#define MAP_EDITOR
//#define MOTION_EDITOR
//#define COLLISION_EDITOR
#define GAME

#define CLASS_NAME	"サンプル"		//ウィンドウのクラス名
#define WINDOW_NAME	"ウィンドウ"	//ウィンドウの名前
#define SCREEN_WIDTH	(1920 * 0.6)		//ウィンドウの高さ
#define SCREEN_HEIGHT	(1080 * 0.6)		//ウィンドウの幅

#define TIMER_INTERVAL	(1000/60)	//待ち時間

#define NUM_VERTEX		(4)			//頂点数
#define NUM_POLYGON		(2)			//ポリゴン数

#define PI				(3.141592f)	//円周率

//////////////////////////////////////////////////////////////////////////////
//構造体定義
//////////////////////////////////////////////////////////////////////////////
typedef D3DXCOLOR		Dcolor;
typedef D3DXMATRIX		Dmtx;
typedef D3DXQUATERNION	DQuate;
typedef D3DXMATRIX		DMtx;
using namespace std;

//////////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
//////////////////////////////////////////////////////////////////////////////
HWND getWnd(void);
int GetFPS(void);