/*****************************************************************************
mode.h
Aythor	: 上野　匠
Data	: 2017_06_28
=============================================================================
Updata

*****************************************************************************/
#ifndef MODE_H
#define MODE_H
//////////////////////////////////////////////////////////////////////////////
//インクルード
//////////////////////////////////////////////////////////////////////////////
#include "player.h"
#include "camera.h"
#include "stage.h"

//////////////////////////////////////////////////////////////////////////////
//前方宣言
//////////////////////////////////////////////////////////////////////////////
class Camera;
class Light;
class Player;
class PlayerTitle;
class PlayerGame;
class PlayerResult;
class Reticle;
class Stage;

//////////////////////////////////////////////////////////////////////////////
//構造体定義
//////////////////////////////////////////////////////////////////////////////
typedef enum
{
	TITLE_MODE = 0,
	GAME_MODE,
	RESULT_MODE,
	MAX_MODE,
	NONE_MODE,
}MODE_TYPE;

//////////////////////////////////////////////////////////////////////////////
//Modeクラス宣言
//////////////////////////////////////////////////////////////////////////////
class Mode
{
public:
	Mode(){};
	~Mode(){};

	virtual void init(void) = 0;
	virtual void uninit(void) = 0;
	virtual void update(void) = 0;
	virtual void draw(void) = 0;

	static Mode *create(Mode *mode);
	void	ChengeMode(void){mChenge = true;}

	MODE_TYPE getType(void){return mType;}

protected:
	MODE_TYPE	mType;		//現在のモード
	bool		mChenge;	//モードが変わるか
};

//////////////////////////////////////////////////////////////////////////////
//NullModeクラス宣言
//////////////////////////////////////////////////////////////////////////////
class NullMode : public Mode
{
public:
	NullMode(){};
	~NullMode(){};

	void init(void){}
	void uninit(void){}
	void update(void){}
	void draw(void){}

private:

};

//////////////////////////////////////////////////////////////////////////////
//Titleクラス宣言
//////////////////////////////////////////////////////////////////////////////
class Title : public Mode
{
public:
	Title(){};
	~Title(){};

	void init(void);
	void uninit(void);
	void update(void);
	void draw(void);

private:
	Player		*mPlayer;		//プレイヤー
};

//////////////////////////////////////////////////////////////////////////////
//Gameクラス宣言
//////////////////////////////////////////////////////////////////////////////
class Game : public Mode
{
public:
	Game(){};
	~Game(){};

	void init(void);
	void uninit(void);
	void update(void);
	void draw(void);

	static Player		*getPlayer(void) {return mPlayer;}
	static Light		*getLight(void) { return mLight; }
	Reticle				*getReticle(void){return mReticle;}

private:
	static Player	*mPlayer;		//プレイヤー
	static Light	*mLight;		//ライト
	static Stage	*mStage;		//ステージ
	Reticle			*mReticle;		//レティクル
};

//////////////////////////////////////////////////////////////////////////////
//Resultクラス宣言
//////////////////////////////////////////////////////////////////////////////
class Result : public Mode
{
public:
	Result() {};
	~Result() {};

	void init(void);
	void uninit(void);
	void update(void);
	void draw(void);

private:
	Player		*mPlayer;		//プレイヤー
};

#endif // !MODE_H
