/*****************************************************************************
player.h
Aythor	: 上野　匠
Data	: 2017_06_15
=============================================================================
Updata

*****************************************************************************/
#ifndef PLAYER_H
#define PLAYER_H

#include "scene.h"

//////////////////////////////////////////////////////////////////////////////
//前方宣言
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
//プレイヤークラス
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
//プレイヤータイトルクラス
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
	//プロトタイプ宣言
	void opeTitle(void);

	//変数宣言
	Fade	*mFade;		//フェードのポインタ
	bool	mStart;		//スタートボタンが押されたかどうか
};

//////////////////////////////////////////////////////////////////////////////
//プレイヤーゲームクラス
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
	//プロトタイプ宣言
	void	opeCamera(void);
	void	hitCheckEnemy(void);

	//変数宣言
	PlayerState*	mState = NULL;
	Game			*mMode;		//モード情報
	Camera			*mCamera;	//カメラ情報
	Fade			*mFade;		//フェードのポインタ
	D3DXVECTOR3		mMoveVec;	//方向ベクトル
	float			mMove;		//移動速度
	float			mSens;		//カメラ感度
	float			mHeight;	//プレイヤーの身長
	float			mLen;		//コリジョン半径
	bool			mFadeStart;	//フェードが開始されてるかどうか
	Weapon*			mWeapon;	//武器
	int				mUpButton;
	int				mDownButton;
	int				mRightButton;
	int				mLeftButton;
	int				mDebugButton;
};

//////////////////////////////////////////////////////////////////////////////
//プレイヤーリザルトクラス
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
	//プロトタイプ宣言


	//変数宣言
	Fade	*mFade;		//フェードのポインタ
	bool	mNext;		//遷移ボタンが押されたか

};

#endif // !PLAYER_H
