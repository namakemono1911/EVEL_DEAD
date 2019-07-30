/*****************************************************************************
object.h
Aythor	: 上野　匠
Data	: 2017_08_13
=============================================================================
Updata

*****************************************************************************/
#ifndef OBJECT_H
#define OBJECT_H
//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include "sceneModel.h"
#include "transform.h"

//////////////////////////////////////////////////////////////////////////////
//前方宣言
//////////////////////////////////////////////////////////////////////////////
class Scene;
//class SceneModel;
class Collision;
class CollisionBall;

//////////////////////////////////////////////////////////////////////////////
//Shelfクラス
//////////////////////////////////////////////////////////////////////////////
class Object : public SceneModel
{
public:
	Object() {}
	~Object() {}

	HRESULT	init(void);
	void	uninit(void);
	void	update(void);
	void	draw(void);

	static Object	*create(std::string fileName);

	Dvec3	getPos(void) { return mTransform.pos; }
	Dvec3	getSize(void) { return mTransform.size; }

	Dvec3	*getPosAd(void) { return &mTransform.pos; }
	Dvec3	*getSizeAd(void) { return &mTransform.size; }
	Dvec3	*getRotAd(void) { return &mTransform.rot; }

private:

};
#endif // !OBJECT_H
