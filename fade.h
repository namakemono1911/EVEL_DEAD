/*****************************************************************************
fade.cpp
Aythor	: ���@��
Data	: 2017_06_28
=============================================================================
Updata

*****************************************************************************/
#ifndef FADE_H
#define FADE_H

#include "outlaw2D.h"

//////////////////////////////////////////////////////////////////////////////
//�O���錾
//////////////////////////////////////////////////////////////////////////////
class Scene2D;
class Outlaw2D;

//////////////////////////////////////////////////////////////////////////////
//Fade�N���X�錾
//////////////////////////////////////////////////////////////////////////////
class Fade : public Outlaw2D
{
public:
	//�񋓌^��`
	typedef enum
	{
		FADE_NONE = 0,		//�������삳��Ă��Ȃ�
		FADE_IN,			//�t�F�[�h�C����
		FADE_OUT			//�t�F�[�h�A�E�g��
	}FADE_MODE;

	Fade(){}
	~Fade(){}

	HRESULT init(void);
	void uninit(void);
	void update(void);
	void draw(void);

	//�t�F�[�h�C���t�F�[�h�A�E�g�J�n
	void fadeIn(int time);
	void fadeOut(int time);

	//�Z�b�^�[
	static Fade *create(D3DXCOLOR color = D3DXCOLOR(1.f, 1.f, 1.f, 1.f));

	//�Q�b�^�[
	FADE_MODE getFadeMode(void){return mMode;}

private:
	//�v���g�^�C�v�錾
	void updateFadeIn(void);
	void updateFadeOut(void);

	//�ϐ��錾
	D3DXCOLOR	mColor;		//�ڕW�̃t�F�[�h�F
	int			mTime;		//�t�F�[�h�ɂ����鎞��
	int			mNow;		//���ݎ���
	FADE_MODE	mMode;		//�t�F�[�h�̏��
};

#endif // !FADE_H

