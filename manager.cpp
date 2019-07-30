/*****************************************************************************
manager.cpp
Aythor	: ���@��
Data	: 2017_05_11
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "ui.h"
#include "modelData.h"
#include "manager.h"
#include "textureManager.h"
#include "light.h"

//////////////////////////////////////////////////////////////////////////////
//�ÓI�����o�ϐ�������
//////////////////////////////////////////////////////////////////////////////
Renderer *Manager::mRenderer = NULL;
InputKeyboard *Manager::mKey = NULL;
InputMouse *Manager::mMouse = NULL;
Mode *Manager::mMode = new NullMode;
Fade *Manager::mFade = NULL;
CSound *Manager::mSound = NULL;
Ui	*Manager::mUi = NULL;

//////////////////////////////////////////////////////////////////////////////
//�֐���	: init
//�Ԃ�l	: 
//����		: ����������
//////////////////////////////////////////////////////////////////////////////
HRESULT	Manager::init	(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//�����_���[����
	mRenderer = new Renderer;
	mRenderer->init(hWnd, bWindow);

	//�T�E���h�ݒ�
	mSound = new CSound;
	mSound->Init(hWnd);

	//�L�[�{�[�h�ݒ�
	mKey = new InputKeyboard;
	mKey->init(hInstance, hWnd);

	//�}�E�X�ݒ�
	mMouse = new InputMouse;
	mMouse->init(hInstance, hWnd);


	//�e�N�X�`���ǂݍ���
	TextureManager::loadAllTextureInDir();

	//���f���ǂݍ���
	ModelData::loadAllModel();

	MeshField::loadTex();

	//���C�g�ݒ�
	Light::setLight(
		D3DXVECTOR3(0.f, 10.f, 10.f),
		D3DXVECTOR3(0.f, -0.5f, -1.f),
		D3DCOLOR_RGBA(255, 255, 255, 255),
		D3DCOLOR_RGBA(255, 255, 255, 255));

#ifdef GAME
	//�����z���I�u�W�F�N�g����
	mFade = Fade::create(D3DXCOLOR(0.f, 0.f, 0.f, 1.f));
	mMouse->fixing(true);				//�}�E�X�Œ�
	ShowCursor(false);					//�}�E�X��\��
	//�Q�[�����[�h�ݒ�
	mMode = Mode::create(new Game);
#endif // GAME

#ifdef MAP_EDITOR
	mUi = MapEditorUi::create();
#endif // MAP_EDITOR

#ifdef MOTION_EDITOR
	//UI�ݒ�
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
//�֐���	: uninit
//�Ԃ�l	: 
//����		: ����������
//////////////////////////////////////////////////////////////////////////////
void	Manager::uninit	( void )
{
	//�����_���[�I��
	mRenderer->uninit();
	delete mRenderer;
	mRenderer = NULL;

	//�e�N�X�`���j��
	TextureManager::releaseAllTexture();

	//�L�[�{�[�h�I��
	mKey->uninit();

	//�}�E�X�I��
	mMouse->uninit();

	//���f���f�[�^�I��
	ModelData::modelDataAllClear();

#ifdef GAME
	//�����z���I�u�W�F�N�g�I��
	mFade->uninit();
#endif // GAME

	//�T�E���h�I��
	mSound->Uninit();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: update
//�Ԃ�l	: 
//����		: ����������
//////////////////////////////////////////////////////////////////////////////
void	Manager::update	( void )
{
	//�L�[�{�[�h�X�V
	mKey->update();

	//�}�E�X
	mMouse->update();

	//���[�h���ƍX�V
	mMode->update();

	mRenderer->update();

#ifdef GAME
	//�����z���I�u�W�F�N�g�X�V
	mFade->update();
#endif // GAME


}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: draw
//�Ԃ�l	: 
//����		: ����������
//////////////////////////////////////////////////////////////////////////////
void	Manager::draw	( void )
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9	device = getDevice();

	//���C�g�̉e��off
	device->SetRenderState(D3DRS_LIGHTING, true);

	//�`��
	mRenderer->draw();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: setMode
//�Ԃ�l	: 
//����		: ���[�h�ݒ�
//////////////////////////////////////////////////////////////////////////////
void Manager::setMode(Mode * setMode)
{
	//���̃��[�h�I��
	mMode->uninit();
	delete mMode;

	//���̃��[�h������
	mMode = setMode;
	mMode->init();
}
