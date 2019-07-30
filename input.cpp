/*****************************************************************************
input.cpp
Aythor	: ���@��
Data	: 2017_05_26
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "input.h"

//////////////////////////////////////////////////////////////////////////////
//�ÓI�����o�ϐ�������
//////////////////////////////////////////////////////////////////////////////
LPDIRECTINPUT8		Input::mDinput = NULL;

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Input::init
//�Ԃ�l	: 
//����		: ������
//////////////////////////////////////////////////////////////////////////////
HRESULT	Input::init(HINSTANCE inst)
{
	HRESULT hr = S_FALSE;

	//DirectInput�I�u�W�F�N�g�̍쐬
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
//�֐���	: Input::uninit
//�Ԃ�l	: 
//����		: �I������
//////////////////////////////////////////////////////////////////////////////
void	Input::uninit(void)
{
	//�f�o�C�X�I�u�W�F�N�g�̉��
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
//�֐���	: InputKeyboard::initKeyboard
//�Ԃ�l	: 
//����		: �L�[�{�[�h�̍X�V
//////////////////////////////////////////////////////////////////////////////
HRESULT InputKeyboard::init(HINSTANCE hInstance, HWND hWnd)
{
	//���͏����̏�����
	Input::init(hInstance);

	// ���͏����̏�����
	if (FAILED(Input::init(hInstance)))
	{
		MessageBox(hWnd, "DirectInput�I�u�W�F�N�g�����˂��I", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �f�o�C�X�̍쐬
	if (FAILED(mDinput->CreateDevice(GUID_SysKeyboard, &mDIDevice, NULL)))
	{
		MessageBox(hWnd, "�L�[�{�[�h���˂��I", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(mDIDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	if (FAILED(mDIDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̋������[�h��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	mDIDevice->Acquire();

	return	S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: InputKeyboard::uninitKeyboard
//�Ԃ�l	: 
//����		: �L�[�{�[�h�̍X�V
//////////////////////////////////////////////////////////////////////////////
void InputKeyboard::uninit(void)
{
	if (mDIDevice != NULL)
	{// ���̓f�o�C�X(�L�[�{�[�h)�̊J��
	 // �L�[�{�[�h�ւ̃A�N�Z�X�����J��(���͐���I��)
		mDIDevice->Unacquire();

		mDIDevice->Release();
		mDIDevice = NULL;
	}

	Input::uninit();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: InputKeyboard::updateKeyboard
//�Ԃ�l	: 
//����		: �L�[�{�[�h�̍X�V
//////////////////////////////////////////////////////////////////////////////
HRESULT InputKeyboard::update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];

	// �f�o�C�X����f�[�^���擾
	if (SUCCEEDED(mDIDevice->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for (int nCnKey = 0; nCnKey < NUM_KEY_MAX; nCnKey++)
		{
			//�L�[�g���K�[���̎擾
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

			// �L�[�v���X����ۑ�
			mKeyState[nCnKey] = aKeyState[nCnKey];
		}
	}
	else
	{
		// �L�[�{�[�h�ւ̃A�N�Z�X�����擾
		mDIDevice->Acquire();
	}

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: InputKeyboard::getPress
//�Ԃ�l	: 
//����		: �L�[�{�[�h�������ꂽ��
//////////////////////////////////////////////////////////////////////////////
bool InputKeyboard::getPress(int nKey)
{
	return (mKeyState[nKey] & 0x80) ? true : false;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: InputKeyboard::getTrigger
//�Ԃ�l	: 
//����		: �L�[�{�[�h�������ꂽ��
//////////////////////////////////////////////////////////////////////////////
bool InputKeyboard::getTrigger(int nKey)
{
	return (mKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: InputKeyboard::getRepeat
//�Ԃ�l	: 
//����		: �L�[�{�[�h�������ꂽ��
//////////////////////////////////////////////////////////////////////////////
bool InputKeyboard::getRepeat(int nKey)
{
	return (mKeyStateRepeat[nKey] & 0x80) ? true : false;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: InputKeyboard::getRelease
//�Ԃ�l	: 
//����		: �L�[�{�[�h�������ꂽ��
//////////////////////////////////////////////////////////////////////////////
bool InputKeyboard::getRelease(int nKey)
{
	return (mKeyStateRelease[nKey] & 0x80) ? true : false;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: InputMouse::InputMouse
//�Ԃ�l	: 
//����		: �R���X�g���N�^
//////////////////////////////////////////////////////////////////////////////
InputMouse::InputMouse()
{
	ZeroMemory(&mMouseState, sizeof(mMouseState));
	ZeroMemory(&mMouseStateTrigger, sizeof(mMouseStateTrigger));
	ZeroMemory(&mMouseStateRelease, sizeof(mMouseStateRelease));
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: InputMouse::init
//�Ԃ�l	: 
//����		: ����������
//////////////////////////////////////////////////////////////////////////////
HRESULT InputMouse::init(HINSTANCE inst, HWND wnd)
{
	HRESULT hr;

	//���͏����̏�����
	Input::init(inst);

	//�f�o�C�X�I�u�W�F�N�g���쐬
	hr = mDinput->CreateDevice(GUID_SysMouse, &mDIDevice, NULL);
	if (FAILED(hr) || mDIDevice == NULL)
	{
		MessageBox(wnd, "�}�E�X���Ȃ���", "�G���[", MB_ICONWARNING);
		return hr;
	}

	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(mDIDevice->SetDataFormat(&c_dfDIMouse2)))
	{
		MessageBox(wnd, "�L�[�{�[�h�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return E_FAIL;
	}

	//�������[�h��ݒ�i�t�H�A�O���E���h&��r�����[�h�j
	hr = mDIDevice->SetCooperativeLevel(
		wnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if (FAILED(hr))
	{
		MessageBox(wnd, "�}�E�X�̋������[�h���ݒ�ł��܂���ł���", "error", MB_ICONWARNING);
		return hr;
	}

	//�f�o�C�X�̐ݒ�
	DIPROPDWORD	dipdw;

	dipdw.diph.dwSize = sizeof(dipdw);
	dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = DIPROPAXISMODE_REL;

	hr = mDIDevice->SetProperty(DIPROP_AXISMODE, &dipdw.diph);

	//�}�E�X�ւ̃A�N�Z�X���擾
	mDIDevice->Acquire();

	return hr;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: InputMouse::uninit
//�Ԃ�l	: 
//����		: �I������
//////////////////////////////////////////////////////////////////////////////
void	InputMouse::uninit(void)
{
	//���͏����̉��
	Input::uninit();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: InputMouse::update
//�Ԃ�l	: 
//����		: �X�V
//////////////////////////////////////////////////////////////////////////////
HRESULT	InputMouse::update(void)
{
	HRESULT	hr;
	DIMOUSESTATE2	mouseState;

	if (!mDIDevice)
	{
		return S_FALSE;
	}

	//�f�o�C�X����f�[�^�擾
	hr = mDIDevice->GetDeviceState(sizeof(mouseState), &mouseState);
	if (SUCCEEDED(hr))
	{
		//�}�E�X�Œ�
		if (mFixing == true)
		{
			POINT	pos;	//�}�E�X���W
			RECT	winPos;	//�E�B���h�E�Y���W

							//���݂̃}�E�X���W�擾
			GetCursorPos(&pos);
			ScreenToClient(GetFocus(), &pos);

			mMouseState.lX = pos.x - mPosMouse.x;
			mMouseState.lY = pos.y - mPosMouse.y;

			GetWindowRect(GetFocus(), &winPos);
			SetCursorPos(winPos.left + (int)SCREEN_WIDTH / 2, winPos.top + (int)SCREEN_HEIGHT / 2);
		}

		//�}�E�X�g���K�[
		mMouseStateTrigger.lX = ((mMouseState.lX ^ mMouseState.lX) & mouseState.lX);
		mMouseStateTrigger.lY = ((mMouseState.lY ^ mMouseState.lY) & mouseState.lY);
		mMouseStateTrigger.lZ = ((mMouseState.lZ ^ mMouseState.lZ) & mouseState.lZ);

		//�}�E�X�����[�X
		mMouseStateRelease.lX = ((mMouseState.lX ^ mMouseState.lX) & mMouseState.lX);
		mMouseStateRelease.lY = ((mMouseState.lY ^ mMouseState.lY) & mMouseState.lY);
		mMouseStateRelease.lX = ((mMouseState.lZ ^ mMouseState.lZ) & mMouseState.lZ);

		//��ԍX�V
		for (int i = 0; i < 8; i++)
		{
			mMouseStateTrigger.rgbButtons[i] =
				((mMouseState.rgbButtons[i] ^ mouseState.rgbButtons[i]) & mouseState.rgbButtons[i]);

			mMouseStateRelease.rgbButtons[i] =
				((mMouseState.rgbButtons[i] ^ mouseState.rgbButtons[i]) & mMouseState.rgbButtons[i]);
		}

		mMouseState = mouseState;

		//�X�N���[�����W�擾
		GetCursorPos(&mPosMouse);
	}
	else
	{
		mDIDevice->Acquire();
	}

	return hr;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: InputMouse::getPressMouse
//�Ԃ�l	: 
//����		: �}�E�X�̃v���X��Ԏ擾
//////////////////////////////////////////////////////////////////////////////
BOOL InputMouse::getPress(const int button)
{
	return (mMouseState.rgbButtons[button] & 0x80) ? true : false;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: InputMouse::getTriggerMouse
//�Ԃ�l	: 
//����		: �}�E�X�̃g���K�[��Ԏ擾
//////////////////////////////////////////////////////////////////////////////
BOOL InputMouse::getTrigger(const int button)
{
	return (mMouseStateTrigger.rgbButtons[button] & 0x80) ? true : false;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: InputMouse::getRleaseMouse
//�Ԃ�l	: 
//����		: �}�E�X�̃����[�X��Ԏ擾
//////////////////////////////////////////////////////////////////////////////
BOOL InputMouse::getRelease(const int button)
{
	return (mMouseStateRelease.rgbButtons[button] & 0x80) ? true : false;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: InputMouse::fixing
//�Ԃ�l	: 
//����		: �}�E�X�̍��W�Œ�
//////////////////////////////////////////////////////////////////////////////
void InputMouse::fixing(bool flag)
{
	//�ϐ��錾
	POINT Mpos;

	//�}�E�X�Œ�ɐݒ�
	mFixing = flag;

	if (mFixing == true)
	{
		//�}�E�X�ړ�
		setCenter();

		//���݂̃}�E�X���W�擾
		GetCursorPos(&Mpos);
		ScreenToClient(GetFocus(), &Mpos);
		mPosMouse.x = Mpos.x;
		mPosMouse.y = Mpos.y;
	}
	else
	{
		//�}�E�X�ړ��l������
		mMouseState.lX = 0;
		mMouseState.lY = 0;
		mMouseState.lZ = 0;
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: InputMouse::setCenter
//�Ԃ�l	: 
//����		: �}�E�X���E�B���h�E�̒����Ɉړ�
//////////////////////////////////////////////////////////////////////////////
void InputMouse::setCenter(void)
{
	//�ϐ��錾
	RECT	WinPos;		//�f�X�N�g�b�v��̃E�C���h�E�̍��W

	GetWindowRect(GetFocus(), &WinPos);
	SetCursorPos((int)WinPos.left + (int)SCREEN_WIDTH / 2, (int)WinPos.top + (int)SCREEN_HEIGHT / 2);
}
