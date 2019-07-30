/*****************************************************************************
scene3D.h
Aythor	: 上野　匠
Data	: 2017_04_20
=============================================================================
Updata

*****************************************************************************/
#ifndef SCENEMODEL_H
#define SCENEMODEL_H
//////////////////////////////////////////////////////////////////////////////
//ヘッダーインクルード
//////////////////////////////////////////////////////////////////////////////
#include "scene.h"
#include "modelData.h"
#include "motion.h"

//////////////////////////////////////////////////////////////////////////////
//前方宣言
//////////////////////////////////////////////////////////////////////////////
class ModelData;

//////////////////////////////////////////////////////////////////////////////
//クラス宣言
//////////////////////////////////////////////////////////////////////////////
class SceneModel : public Scene
{
public:
	SceneModel(UINT priolity = PRIME_THIRD):Scene(priolity) {}
	SceneModel(string fileName, UINT priolity = PRIME_THIRD):Scene(priolity)
	{
		mData = ModelData::createModelData(fileName);
	}

	~SceneModel() {}
	HRESULT	init	(void);
	void	uninit	(void);
	void	update	(void);
	void	draw	(void);

	//ゲッター
	Dvec3	getPos(void) { return mTransform.pos; }
	Dvec3	getSize(void) { return mTransform.size; }
	Dvec3	getRot(void) {return mTransform.rot;}
	Dvec3	*getPosAd(void){return &mTransform.pos;}
	Dvec3	*getSizeAd(void){return &mTransform.size;}
	Dvec3	*getRotAd(void){return &mTransform.rot;}
	HRESULT	loadModel(const char *fileName);
	string	getModelName(void){return mData->getModelName();}

	static SceneModel*	create(string modelName, Dvec3 pos = Dvec3(0, 0, 0));
	static map<string, Scene*> loadModelData(string fileName);

protected:
	//変数宣言
	ModelData					*mData;		//モデルデータ

private:

};

#endif