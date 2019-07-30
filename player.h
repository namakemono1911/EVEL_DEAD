/*****************************************************************************
player.h
Aythor	: ���@��
Data	: 2017_06_15
=============================================================================
Updata

*****************************************************************************/
#ifndef PLAYER_H
#define PLAYER_H

#include "scene.h"

//////////////////////////////////////////////////////////////////////////////
//�O���錾
//////////////////////////////////////////////////////////////////////////////
class Mode;
class Game;
class Manager;
class CollisionManager;
class Camera;
class Fade;
class Weapon;
class PlayerState;
class Input;
class InputKeyboard;
class InputMouse;

//////////////////////////////////////////////////////////////////////////////
//�v���C���[�N���X
//////////////////////////////////////////////////////////////////////////////
class Player : public Scene
{
public:
	Player(UINT priolity = PRIME_FIRST, OBJ_TYPE type = PLAYER) :Scene(priolity) { setObjType(type); }
	~Player(){}

	HRESULT	init(void) override { mMyName = "player"; return S_OK; }
	void	uninit(void) override {}
	void	update(void) override {}
	void	draw(void) override {}

	static Player	*create(Player *player);

protected:
};

//////////////////////////////////////////////////////////////////////////////
//�v���C���[�^�C�g���N���X
//////////////////////////////////////////////////////////////////////////////
class PlayerTitle : public Player
{
public:
	PlayerTitle(){}
	~PlayerTitle(){}

	HRESULT init(void);
	void uninit(void);
	void update(void);
	void draw(void) {};

private:
	//�v���g�^�C�v�錾
	void opeTitle(void);

	//�ϐ��錾
	Fade	*mFade;		//�t�F�[�h�̃|�C���^
	bool	mStart;		//�X�^�[�g�{�^���������ꂽ���ǂ���
};

//////////////////////////////////////////////////////////////////////////////
//�v���C���[�Q�[���N���X
//////////////////////////////////////////////////////////////////////////////
class PlayerGame : public Player
{
public:
	PlayerGame(){}
	~PlayerGame(){}

	HRESULT init(void);
	void uninit(void);
	void update(void);
	void draw(void) {}

	float	getHeight(void){return mHeight;}
	bool	isPushedUp(void);
	bool	isPushedDown(void);
	bool	isPushedRight(void);
	bool	isPushedLeft(void);
	bool	isPushedDebug(void);

	auto&	moveSpeed(void) { return mMove; }
	const auto&	getSens(void) { return mSens; }

	void	setState(PlayerState* p);

private:
	//�v���g�^�C�v�錾
	void	opeCamera(void);
	void	hitCheckEnemy(void);

	//�ϐ��錾
	PlayerState*	mState = NULL;
	Game			*mMode;		//���[�h���
	Camera			*mCamera;	//�J�������
	Fade			*mFade;		//�t�F�[�h�̃|�C���^
	D3DXVECTOR3		mMoveVec;	//�����x�N�g��
	float			mMove;		//�ړ����x
	float			mSens;		//�J�������x
	float			mHeight;	//�v���C���[�̐g��
	float			mLen;		//�R���W�������a
	bool			mFadeStart;	//�t�F�[�h���J�n����Ă邩�ǂ���
	Weapon*			mWeapon;	//����
	int				mUpButton;
	int				mDownButton;
	int				mRightButton;
	int				mLeftButton;
	int				mDebugButton;
};

//////////////////////////////////////////////////////////////////////////////
//�v���C���[���U���g�N���X
//////////////////////////////////////////////////////////////////////////////
class PlayerResult : public Player
{
public:
	PlayerResult(){}
	~PlayerResult(){}

	HRESULT init(void);
	void uninit(void);
	void update(void);
	void draw(void) {}

private:
	//�v���g�^�C�v�錾


	//�ϐ��錾
	Fade	*mFade;		//�t�F�[�h�̃|�C���^
	bool	mNext;		//�J�ڃ{�^���������ꂽ��

};

#endif // !PLAYER_H
