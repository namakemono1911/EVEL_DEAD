/*****************************************************************************
renderer.cpp
Aythor	: 上野　匠
Data	: 2017_05_10
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "manager.h"
#include "fade.h"
#include "renderer.h"
#include "imgui.h"
#include "imgui_impl_dx9.h"

//////////////////////////////////////////////////////////////////////////////
//静的メンバ変数初期化
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3D9	Renderer::mD3D = NULL;
LPDIRECT3DDEVICE9 Renderer::mD3DDevice = NULL;

//////////////////////////////////////////////////////////////////////////////
//関数名	: init
//返り値	: 
//説明		: 初期化処理
//////////////////////////////////////////////////////////////////////////////
HRESULT	Renderer::init	( HWND hWnd, BOOL bWindow )
{
	//変数宣言
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	//Direct3Dインターフェイスの取得
	mD3D = Direct3DCreate9(D3D9b_SDK_VERSION);

	if (mD3D == NULL)
	{
		return E_FAIL;
	}

	if (FAILED(mD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//デバイスのプレゼントパラメーターの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = (UINT)SCREEN_WIDTH;
	d3dpp.BackBufferHeight = (UINT)SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	//Direct3Dデバイスの作成
	if (FAILED(mD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &mD3DDevice)))
	{
		//ハードウェアで描画できなかったら頂点処理がsoftware描画がhardwareで処理
		if (FAILED(mD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &mD3DDevice)))
		{
			//最終手段、全部softwareで処理
			if (FAILED(mD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &mD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//頂点フォーマットの設定
	mD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	mD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	mD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	mD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	mD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//mD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	//サンプラーステートの設定
	mD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	mD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	mD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);

	//テクスチャ設定
	mD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1 , D3DTA_TEXTURE);
	mD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP , D3DTOP_MODULATE);
	mD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2 , D3DTA_DIFFUSE);
	mD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	mD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	mD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

#ifdef _DEBUG
	// デバッグ情報表示用フォントの生成
	D3DXCreateFont(mD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);

	//imgui初期化
	ImGui_ImplDX9_CreateDeviceObjects();
	if (!ImGui_ImplDX9_Init(hWnd, mD3DDevice))
		return E_FAIL;
#endif

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: uninit
//返り値	: 
//説明		: 終了
//////////////////////////////////////////////////////////////////////////////
void	Renderer::uninit	( void )
{
#ifdef _DEBUG
	// 情報表示用フォントの破棄
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}

	ImGui_ImplDX9_Shutdown();
#endif

	//Direct3Dデバイスの解放
	if (mD3DDevice != NULL)
	{
		mD3DDevice->Release();
		mD3DDevice = NULL;
	}

	//Direct3Dインターフェイスの解放
	if (mD3D != NULL)
	{
		mD3D->Release();
		mD3D = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: update
//返り値	: 
//説明		: 更新
//////////////////////////////////////////////////////////////////////////////
void	Renderer::update	( void )
{
#ifdef _DEBUG
	ImGui_ImplDX9_NewFrame();
#endif // _DEBUG

	// ポリゴンの更新処理
	Scene::updateAll();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: draw
//返り値	: 
//説明		: 描画
//////////////////////////////////////////////////////////////////////////////
void	Renderer::draw	( void )
{
	// バックバッファ＆Ｚバッファのクリア
	mD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(192, 192, 255, 0), 1.0f, 0);

	// Direct3Dによる描画の開始
	if (SUCCEEDED(mD3DDevice->BeginScene()))
	{
		//ポリゴン描画
		Scene::drawAll();

#ifdef GAME
		//持ち越しオブジェクト描画
		Manager::getFade()->draw();
#endif // GAME


#ifdef _DEBUG
		// FPS表示
		drawFPS();

		ImGui::Render();
#endif

		// Direct3Dによる描画の終了
		mD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	mD3DDevice->Present(NULL, NULL, NULL, NULL);
}

#ifdef _DEBUG
//////////////////////////////////////////////////////////////////////////////
//関数名	: drawFPS
//返り値	: 
//説明		: 描画
//////////////////////////////////////////////////////////////////////////////
void Renderer::drawFPS(void)
{
	RECT rect = { 0, 0, (LONG)SCREEN_WIDTH, (LONG)SCREEN_HEIGHT };
	char str[256];
	int nCountFPS;

	// FPS取得
	nCountFPS = GetFPS();
	wsprintf(str, "FPS:%d\n", nCountFPS);

	// テキスト描画
	m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
#endif