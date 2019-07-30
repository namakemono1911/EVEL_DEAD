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

	int		mNumVertical;		//縦の分割数
	int		mNumHorizonal;		//横の分割数
	int		mInterval;			//アニメーションの間隔
	int		mNumFrame;			//フレーム数
	int		mNumAnime;			//アニメーション数
};

