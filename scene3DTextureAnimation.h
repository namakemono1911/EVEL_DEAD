#pragma once
#include "scene3DState.h"

class Scene3DTextureAnimation : public Scene3DState
{
public:
	Scene3DTextureAnimation(Scene3D* s) : Scene3DState(s) {}
	~Scene3DTextureAnimation() {}

	void	init() override;
	void	update() override;
	static Scene3DTextureAnimation*	create(Scene3D* s, int numVertical, int numHorizonal, int interval);

public:
	Dvec2	calcTexturePos();

	int		mNumVertical;		//�c�̕�����
	int		mNumHorizonal;		//���̕�����
	int		mInterval;			//�A�j���[�V�����̊Ԋu
	int		mNumFrame;			//�t���[����
	int		mNumAnime;			//�A�j���[�V������
};

