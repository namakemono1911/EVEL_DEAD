/*****************************************************************************
manager.h
Aythor	: ���@��
Data	: 2017_05_11
=============================================================================
Updata

*****************************************************************************/
#ifndef MANAGER_H
#define MANAGER_H
//////////////////////////////////////////////////////////////////////////////
//�C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "renderer.h"
#include "scene.h"
#include "input.h"
#include "sound.h"
#include "outlaw2D.h"
#include "fade.h"
#include "mode.h"

//////////////////////////////////////////////////////////////////////////////
//�萔��`
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//�O���錾
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
//�N���X�錾
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

	//�Q�b�^�[
	static Renderer				*getRenderer(void){return mRenderer;}
	static LPDIRECT3DDEVICE9	getDevice(void){return mRenderer->getDevice();}
	static InputKeyboard		*getKeyboard(void){return mKey;}
	static InputMouse			*getMouse(void){return mMouse;}
	static Mode					*getMode(void){return mMode;}
	static Fade					*getFade(void){return mFade;}
	static CSound				*getSound(void){return mSound;}
	static Ui					*getUi(void) {return mUi;}

	//�Z�b�^�[
	static void	setMode(Mode *setMode);

private:
	static Renderer			*mRenderer;		//�����_���[
	static InputKeyboard	*mKey;			//�L�[�{�[�h
	static InputMouse		*mMouse;		//�}�E�X
	static Mode				*mMode;			//���[�h
	static Fade				*mFade;			//�V�[���J�ڌ�������z�����I�u�W�F�N�g�f�[�^
	static CSound			*mSound;		//�T�E���h
	static Ui				*mUi;			//ui
};

#endif