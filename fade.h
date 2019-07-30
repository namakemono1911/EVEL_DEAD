/*****************************************************************************
fade.cpp
Aythor	: 上野　匠
Data	: 2017_06_28
=============================================================================
Updata

*****************************************************************************/
#ifndef FADE_H
#define FADE_H

#include "outlaw2D.h"

//////////////////////////////////////////////////////////////////////////////
//前方宣言
//////////////////////////////////////////////////////////////////////////////
class Scene2D;
class Outlaw2D;

//////////////////////////////////////////////////////////////////////////////
//Fadeクラス宣言
//////////////////////////////////////////////////////////////////////////////
class Fade : public Outlaw2D
{
public:
	//列挙型定義
	typedef enum
	{
		FADE_NONE = 0,		//何も操作されていない
		FADE_IN,			//フェードイン中
		FADE_OUT			//フェードアウト中
	}FADE_MODE;

	Fade(){}
	~Fade(){}

	HRESULT init(void);
	void uninit(void);
	void update(void);
	void draw(void);

	//フェードインフェードアウト開始
	void fadeIn(int time);
	void fadeOut(int time);

	//セッター
	static Fade *create(D3DXCOLOR color = D3DXCOLOR(1.f, 1.f, 1.f, 1.f));

	//ゲッター
	FADE_MODE getFadeMode(void){return mMode;}

private:
	//プロトタイプ宣言
	void updateFadeIn(void);
	void updateFadeOut(void);

	//変数宣言
	D3DXCOLOR	mColor;		//目標のフェード色
	int			mTime;		//フェードにかかる時間
	int			mNow;		//現在時間
	FADE_MODE	mMode;		//フェードの状態
};

#endif // !FADE_H

