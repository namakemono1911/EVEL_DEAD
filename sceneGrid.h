/*****************************************************************************
sceneGrid.h
Aythor	: 上野　匠
Data	: 2017_07_26
=============================================================================
Updata

*****************************************************************************/
#ifndef SCENE_GRIT_H
#define	SCENE_GRIT_H
//////////////////////////////////////////////////////////////////////////////
//SceneGrid class
//////////////////////////////////////////////////////////////////////////////
class SceneGrid : public Scene
{
public:
	SceneGrid(){}
	~SceneGrid(){}

	HRESULT	init(void);
	void	uninit(void);
	void	update(void);
	void	draw(void);

	void	setLine(Dvec3 startPos, Dvec3 endPos) { mStartPos = startPos; mEndPos = endPos; }

	static SceneGrid *create(Dvec3 startPos, Dvec3 endPos);

private:
	LPDIRECT3DVERTEXBUFFER9		mVtx;	//頂点バッファ
	Dvec3	mStartPos;
	Dvec3	mEndPos;
};

#endif // !SCENE_GRIT_H
