/*****************************************************************************
renderer.cpp
Aythor	: ���@��
Data	: 2017_05_10
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "manager.h"
#include "fade.h"
#include "renderer.h"
#include "imgui.h"
#include "imgui_impl_dx9.h"

//////////////////////////////////////////////////////////////////////////////
//�ÓI�����o�ϐ�������
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3D9	Renderer::mD3D = NULL;
LPDIRECT3DDEVICE9 Renderer::mD3DDevice = NULL;

//////////////////////////////////////////////////////////////////////////////
//�֐���	: init
//�Ԃ�l	: 
//����		: ����������
//////////////////////////////////////////////////////////////////////////////
HRESULT	Renderer::init	( HWND hWnd, BOOL bWindow )
{
	//�ϐ��錾
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	//Direct3D�C���^�[�t�F�C�X�̎擾
	mD3D = Direct3DCreate9(D3D9b_SDK_VERSION);

	if (mD3D == NULL)
	{
		return E_FAIL;
	}

	if (FAILED(mD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�̃v���[���g�p�����[�^�[�̐ݒ�
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

	//Direct3D�f�o�C�X�̍쐬
	if (FAILED(mD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &mD3DDevice)))
	{
		//�n�[�h�E�F�A�ŕ`��ł��Ȃ������璸�_������software�`�悪hardware�ŏ���
		if (FAILED(mD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &mD3DDevice)))
		{
			//�ŏI��i�A�S��software�ŏ���
			if (FAILED(mD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &mD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//���_�t�H�[�}�b�g�̐ݒ�
	mD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	mD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	mD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	mD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	mD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//mD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	//�T���v���[�X�e�[�g�̐ݒ�
	mD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	mD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	mD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);

	//�e�N�X�`���ݒ�
	mD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1 , D3DTA_TEXTURE);
	mD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP , D3DTOP_MODULATE);
	mD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2 , D3DTA_DIFFUSE);
	mD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	mD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	mD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

#ifdef _DEBUG
	// �f�o�b�O���\���p�t�H���g�̐���
	D3DXCreateFont(mD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);

	//imgui������
	ImGui_ImplDX9_CreateDeviceObjects();
	if (!ImGui_ImplDX9_Init(hWnd, mD3DDevice))
		return E_FAIL;
#endif

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: uninit
//�Ԃ�l	: 
//����		: �I��
//////////////////////////////////////////////////////////////////////////////
void	Renderer::uninit	( void )
{
#ifdef _DEBUG
	// ���\���p�t�H���g�̔j��
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}

	ImGui_ImplDX9_Shutdown();
#endif

	//Direct3D�f�o�C�X�̉��
	if (mD3DDevice != NULL)
	{
		mD3DDevice->Release();
		mD3DDevice = NULL;
	}

	//Direct3D�C���^�[�t�F�C�X�̉��
	if (mD3D != NULL)
	{
		mD3D->Release();
		mD3D = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: update
//�Ԃ�l	: 
//����		: �X�V
//////////////////////////////////////////////////////////////////////////////
void	Renderer::update	( void )
{
#ifdef _DEBUG
	ImGui_ImplDX9_NewFrame();
#endif // _DEBUG

	// �|���S���̍X�V����
	Scene::updateAll();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: draw
//�Ԃ�l	: 
//����		: �`��
//////////////////////////////////////////////////////////////////////////////
void	Renderer::draw	( void )
{
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	mD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(192, 192, 255, 0), 1.0f, 0);

	// Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(mD3DDevice->BeginScene()))
	{
		//�|���S���`��
		Scene::drawAll();

#ifdef GAME
		//�����z���I�u�W�F�N�g�`��
		Manager::getFade()->draw();
#endif // GAME


#ifdef _DEBUG
		// FPS�\��
		drawFPS();

		ImGui::Render();
#endif

		// Direct3D�ɂ��`��̏I��
		mD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	mD3DDevice->Present(NULL, NULL, NULL, NULL);
}

#ifdef _DEBUG
//////////////////////////////////////////////////////////////////////////////
//�֐���	: drawFPS
//�Ԃ�l	: 
//����		: �`��
//////////////////////////////////////////////////////////////////////////////
void Renderer::drawFPS(void)
{
	RECT rect = { 0, 0, (LONG)SCREEN_WIDTH, (LONG)SCREEN_HEIGHT };
	char str[256];
	int nCountFPS;

	// FPS�擾
	nCountFPS = GetFPS();
	wsprintf(str, "FPS:%d\n", nCountFPS);

	// �e�L�X�g�`��
	m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
#endif