/*****************************************************************************
mode.h
Aythor	: ���@��
Data	: 2017_06_28
=============================================================================
Updata

*****************************************************************************/
#ifndef MODE_H
#define MODE_H
//////////////////////////////////////////////////////////////////////////////
//�C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "player.h"
#include "camera.h"
#include "stage.h"

//////////////////////////////////////////////////////////////////////////////
//�O���錾
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
//�\���̒�`
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
//Mode�N���X�錾
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
	MODE_TYPE	mType;		//���݂̃��[�h
	bool		mChenge;	//���[�h���ς�邩
};

//////////////////////////////////////////////////////////////////////////////
//NullMode�N���X�錾
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
//Title�N���X�錾
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
	Player		*mPlayer;		//�v���C���[
};

//////////////////////////////////////////////////////////////////////////////
//Game�N���X�錾
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
	static Player	*mPlayer;		//�v���C���[
	static Light	*mLight;		//���C�g
	static Stage	*mStage;		//�X�e�[�W
	Reticle			*mReticle;		//���e�B�N��
};

//////////////////////////////////////////////////////////////////////////////
//Result�N���X�錾
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
	Player		*mPlayer;		//�v���C���[
};

#endif // !MODE_H
