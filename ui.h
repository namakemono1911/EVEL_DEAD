/*****************************************************************************
ui.h
Aythor	: 上野　匠
Data	: 2017_07_28
=============================================================================
Updata

*****************************************************************************/
#ifndef UI_H
#define UI_H
//////////////////////////////////////////////////////////////////////////////
//インクルード
//////////////////////////////////////////////////////////////////////////////
#include <filesystem>
#include <string>
#include <vector>
#include <list>
#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "collision.h"
#include "collisionBox.h"
#include "object.h"
#include "mesh.h"
#include "meshField.h"
#include "stage.h"

//////////////////////////////////////////////////////////////////////////////
//ネームスペース
//////////////////////////////////////////////////////////////////////////////
using namespace ImGui;
namespace sys = std::tr2::sys;

//////////////////////////////////////////////////////////////////////////////
//Uiクラス宣言
//////////////////////////////////////////////////////////////////////////////
class Scene;
class SceneModel;
class MotionEdit;
class Camera;

class Ui : public Scene
{
public:
	Ui(){}
	~Ui(){}

	virtual HRESULT	init(void);
	virtual void	uninit(void) = 0;
	virtual void	update(void) = 0;
	virtual void	draw() {};
	virtual void	load() = 0;
	virtual void	save(HWND hWnd) = 0;

	void		setTransformDrag(Transform	*transform);
	void		cameraUi(void);

protected:
	Camera*	mCamera;
	float	floatDragRate;

private:

};

class MapEditorUi : public Ui
{
public:
	typedef struct
	{
		string		fieldName;			//フィールドの名前
		int			texture;			//テクスチャID
		MeshField	*field;				//フィールドポインタ
	}FIELD;
	MapEditorUi(){}
	~MapEditorUi(){}

	HRESULT	init(void);
	void	uninit(void) { Scene::releaseAll(); }
	void	update(void);
	void	load();
	void	save(HWND hWnd) override;
	void	reset();

	static MapEditorUi*		create();
	static FIELD	createMeshField(void);

	auto			getStageList(void) { return mStage; }

private:
	void		settingWindw(void);
	void		editWindow(void);
	void		editObj(void);
	void		editField(void);
	void		objectGenerationProcedure(void);
	Object*		createObj(string fileName);
	void		createObj(Object obj);

	Stage*				mStage;				//ステージを管理
	UINT				mNumObj;			//出ているオブジェクト数
	UINT				mNumField;			//出ているフィールド数
	vector<sys::path>	mNameList;			//オブジェクトの名前
	string				mAllTexInField;		//フィールドのテクスチャ名

};

//class MotionEditorUi : public Ui
//{
//public:
//	MotionEditorUi(){}
//	~MotionEditorUi(){}
//
//	HRESULT	init(void) override;
//	void	uninit(void) override;
//	void	update(void) override;
//	void	draw(void) { if (mEditModel != NULL) mEditModel->draw(); }
//	void	load() override;
//	void	save(HWND hWnd) override;
//
//	const auto&	getParts(void) { return mEditModel; }
//
//private:
//	void		editModelParts(void);
//	void		editKeyframe(void);
//	auto		createNewKeyframe(MotionData motionData);
//	MotionData	*createNewMotionData(string motionName);
//	void		seeAllMotionDataList(list<MotionData*> dataList);
//	void		keyframeSetting(MotionData *motionData, int id);
//	void		createKeyframeButton(MotionData *motionData);
//	void		playButton(MotionData motionData);
//	void		selectPlayModeCombo(MotionData *motionData);
//	void		followPartsChildren(list<Parts*> childrenList);
//
//	vector<sys::path>	mPathList;		//ファイルパスリスト
//	MotionEdit		*mEditModel;		//編集するモデル
//	ModelParts		*mDefauldPosture;	//初期姿勢
//	Keyframe		*mKeyToEdit;		//編集するキーフレーム
//	Keyframe		mCopyKeyframe;		//コピーするキーフレーム
//	UINT			mNumMotion;			//何個目のモーションか
//	list<string>	mNameList;			//オブジェクトの名前
//
//};

class CollisionEditorUi : public Ui
{
public:
	CollisionEditorUi(){}
	~CollisionEditorUi(){}

	HRESULT init();
	void	uninit();
	void	update();
	void	load();
	void	save(HWND hWnd) override;

	auto	getObjectList(void) { return objectList; }

private:
	list<Collision*>::iterator	selectCollisionEdit(Collision * col, list<Collision*>* colList, list<Collision*>::iterator colIt);
	void						editCollisionBox(CollisionBox* box);
	list<Collision*>::iterator	shawBoxEdit(CollisionBox* box, list<Collision*>* colList, list<Collision*>::iterator colIt);
	list<Collision*>::iterator	shawBallEdit(CollisionBall* ball, list<Collision*>* colList, list<Collision*>::iterator colIt);
	list<Collision*>::iterator	shouldShawBoxEdit(CollisionBox* box, list<Collision*>* colList, list<Collision*>::iterator colIt);
	list<Collision*>::iterator	shouldShawBallEdit(CollisionBall* ball, list<Collision*>* colList, list<Collision*>::iterator colIt);
	list<Collision*>::iterator	deleteCollision(Collision* col, list<Collision*>* colList, list<Collision*>::iterator colIt);
	void						editCollisionBall(CollisionBall* ball);

	string			mSelectionFilename;	//選択したファイル名
	list<Scene*>	objectList;	//表示されているオブジェクトリスト
	Stage*			mStage;	
};

class ModelEditorUi : public Ui
{
public:
	typedef struct
	{
		Scene*	scene;
		int		parentID;
	}EDIT_DATA;

	ModelEditorUi() {}
	~ModelEditorUi() {}

	HRESULT init();
	void	uninit();
	void	update();
	void	load();
	void	save(HWND hWnd) override;

	auto	getModelList(void) { return mModelList; }

private:
	vector<sys::path>	mModelFileNameList;		//読み込まれているモデルファイルリスト
	vector<EDIT_DATA>	mModelList;				//表示されているモデルリスト

	void			editModelAdd(string modelName);
	void			editModelAdd(Scene* scene);
	void			modelButton(void);
	void			setInfomationWindow(void);
	void			setEditModelDeleteButton(Scene* scene, int num);
	void			setParentCombo(Scene* scene, int& id);
	string			getDisplayModelNameList(void);
	void			setModelEditTool(Scene* scene, int& id, int arrayNum);
	void			setEditModelTree(int arrayNum);
	void			setEditWindow(void);
};
#endif // !UI_H
