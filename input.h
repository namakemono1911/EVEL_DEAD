/*****************************************************************************
input.cpp
Aythor	: ���@��
Data	: 2017_05_26
=============================================================================
Updata

*****************************************************************************/
#ifndef INPUT_H
#define INPUT_H
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include <dinput.h>

//////////////////////////////////////////////////////////////////////////////
//�萔��`
//////////////////////////////////////////////////////////////////////////////
#define NUM_MOUSE_MAX		(8)		// �}�E�X�̍ő吔
#define	NUM_KEY_MAX			(256)	// �L�[�̍ő吔
#define	LIMIT_COUNT_REPEAT	(20)	// ���s�[�g�J�E���g���~�b�^�[

#define MOUSE_LEFT			(0)		//���N���b�N
#define MOUSE_RIGHT			(1)		//�E�N���b�N
#define MOUSE_CENTER		(2)		//�z�C�[���{�^��

//////////////////////////////////////////////////////////////////////////////
//�N���X��`
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
	BYTE	mKeyState[NUM_KEY_MAX];			// �L�[�{�[�h�̓��͏�񃏁[�N
	BYTE	mKeyStateTrigger[NUM_KEY_MAX];	// �L�[�{�[�h�̃g���K�[��񃏁[�N
	BYTE	mKeyStateRelease[NUM_KEY_MAX];	// �L�[�{�[�h�̃����[�X��񃏁[�N
	BYTE	mKeyStateRepeat[NUM_KEY_MAX];		// �L�[�{�[�h�̃��s�[�g��񃏁[�N
	int		mKeyStateRepeatCnt[NUM_KEY_MAX];	// �L�[�{�[�h�̃��s�[�g�J�E���^
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
	DIMOUSESTATE2	mMouseState;			//�}�E�X
	DIMOUSESTATE2	mMouseStateTrigger;		//�g���K�[�̏��
	DIMOUSESTATE2	mMouseStateRelease;		//�}�E�X���������
	POINT			mPosMouse;				//�}�E�X���W
	bool			mFixing;				//true�ňʒu�Œ�
};

#endif