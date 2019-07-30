/*****************************************************************************
ui.h
Aythor	: ���@��
Data	: 2017_07_28
=============================================================================
Updata

*****************************************************************************/
#ifndef UI_H
#define UI_H
//////////////////////////////////////////////////////////////////////////////
//�C���N���[�h
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
//�l�[���X�y�[�X
//////////////////////////////////////////////////////////////////////////////
using namespace ImGui;
namespace sys = std::tr2::sys;

//////////////////////////////////////////////////////////////////////////////
//Ui�N���X�錾
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
		string		fieldName;			//�t�B�[���h�̖��O
		int			texture;			//�e�N�X�`��ID
		MeshField	*field;				//�t�B�[���h�|�C���^
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

	Stage*				mStage;				//�X�e�[�W���Ǘ�
	UINT				mNumObj;			//�o�Ă���I�u�W�F�N�g��
	UINT				mNumField;			//�o�Ă���t�B�[���h��
	vector<sys::path>	mNameList;			//�I�u�W�F�N�g�̖��O
	string				mAllTexInField;		//�t�B�[���h�̃e�N�X�`����

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
//	vector<sys::path>	mPathList;		//�t�@�C���p�X���X�g
//	MotionEdit		*mEditModel;		//�ҏW���郂�f��
//	ModelParts		*mDefauldPosture;	//�����p��
//	Keyframe		*mKeyToEdit;		//�ҏW����L�[�t���[��
//	Keyframe		mCopyKeyframe;		//�R�s�[����L�[�t���[��
//	UINT			mNumMotion;			//���ڂ̃��[�V������
//	list<string>	mNameList;			//�I�u�W�F�N�g�̖��O
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

	string			mSelectionFilename;	//�I�������t�@�C����
	list<Scene*>	objectList;	//�\������Ă���I�u�W�F�N�g���X�g
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
	vector<sys::path>	mModelFileNameList;		//�ǂݍ��܂�Ă��郂�f���t�@�C�����X�g
	vector<EDIT_DATA>	mModelList;				//�\������Ă��郂�f�����X�g

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
