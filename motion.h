/*****************************************************************************
motion.h
Aythor	: 上野　匠
Data	: 2017_09_06
=============================================================================
Updata

*****************************************************************************/
#ifndef MOTION_H
#define MOTION_H

#include <list>
#include <vector>
#include <string>
#include <unordered_map>
#include "scene.h"

//////////////////////////////////////////////////////////////////////////////
// クラス宣言
//////////////////////////////////////////////////////////////////////////////
class Scene;

class Keyframe
{
public:

	Keyframe(){}
	~Keyframe(){}

	static	Keyframe	create(list<Scene*> partsList, int frameRate = 30);
	void				setPartsTransform(list<Scene*> partsList);
	void				setKeyValue(list<Scene*> partsList);
	void				setFrameRate(int rate) { mFrameRate = rate; }
	auto&				frameRate() { return mFrameRate; }
	void				setKey(string partsName, Transform trans) { mKey[partsName] = trans; }
	const auto&			getTransform(string partsName) { return mKey[partsName]; }
	auto				getKey() { return mKey; }

private:
	int						mFrameRate;			//フレームレート
	unordered_map<string, Transform>	mKey;				//各パーツごとの位置情報
};

class MotionData
{
public:
	enum PLAY_MODE
	{
		ONECE = 0,
		LOOP,
	};

	MotionData(){mMakeMotionPlay = false; mPlayMode = ONECE; mNumKeyframeList = 0;}
	~MotionData(){}

	void	init() { mMakeMotionPlay = true; mNumKeyframeList = 0;  }

	static MotionData			*create(string motionName, list<Scene*> partsList);
	static list<MotionData*>	loadMotionData(string fileDir);

	const auto&	getMotionName() { return mMotionName; }
	void		calcKeyframe(list<Scene*> partsList, int numFrame);
	void		calcMotion(Scene * part, unordered_map<string, Transform> key, unordered_map<string, Transform> nextKey, float rate);
	auto&		makeMotionPlay() { return mMakeMotionPlay; }
	const auto& getFrameRate() { return mKeyframeList[mNumKeyframeList].frameRate(); }
	const auto& getKeyframeListSize() { return mKeyframeList.size(); }
	void		addKeyframeList() { mNumKeyframeList++; }
	const auto& getPlayMode() { return mPlayMode; }
	auto&		numKeyframe() { return mNumKeyframeList; }

private:
	int					mPlayMode;			//再生モード
	string				mMotionName;		//モーションの名前
	UINT				mNumKeyframeList;	//何番目のキーフレームを再生するか
	vector<Keyframe>	mKeyframeList;		//キーフレームリスト
	bool				mMakeMotionPlay;	//モーションするかどうか

};

class MotionModel
{
public:
	MotionModel() { mMotionPlayback = NULL; }
	~MotionModel() {}

	static MotionModel	create(string flieName, Transform transform);
	static MotionModel	create(string fileName);

	void	playMotion(string motionName);
	bool	isMotion() { if (mMotionPlayback == NULL) return false; return mMotionPlayback->makeMotionPlay(); }
	void	pauseMotion() { if (mMotionPlayback == NULL) return; mMotionPlayback->makeMotionPlay() = false; }
	void	restartMotion() { if (mMotionPlayback == NULL) return; mMotionPlayback->makeMotionPlay() = true; }
	void	stopMotion();
	string	playingMotionName() { if (mMotionPlayback == NULL) return ""; return mMotionPlayback->getMotionName(); }

	void	loadModelData(string fileDir, Scene::OBJ_TYPE type);
	void	loadMotionData(string modelDir, string motionDir, Scene::OBJ_TYPE type = Scene::OBJECT);

	void	update(void);
	Scene	*findModelParts(string modelName);
	void	setParent(Scene* scene) { mMainParts->setParent(scene); }

	const auto&	getPartsList() { return mPartsList; }

private:
	void	setDefaultTransform(Scene *scene);

	unordered_map<string, Transform>	mDefaultPosture;	//デフォルト姿勢
	list<Scene*>			mPartsList;			//構成パーツリスト
	MotionData				*mMotionPlayback;	//再生するモーション
	list<MotionData*>		mMotionDataList;	//モーションデータリスト
	Scene*					mMainParts;			//モデルの親玉
	int						mNumFrame;			//現在のフレーム数
};

#endif // !MOTION_H