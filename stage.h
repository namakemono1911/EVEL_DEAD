/*****************************************************************************
stage.cpp
Aythor	: 上野　匠
Data	: 2017_11_19
=============================================================================
Updata

*****************************************************************************/
#ifndef STAGE_H
#define	STAGE_H
//////////////////////////////////////////////////////////////////////////////
// ヘッダーインクルード
//////////////////////////////////////////////////////////////////////////////
class Scene;
class MeshField;

class Stage : public Scene
{
public:
	Stage() {}
	~Stage() {}

	HRESULT	init(void);
	void	uninit(void);
	void	update(void);
	void	draw(void);

	void	loadMapFile(string mapFileName);
	bool	saveMap(string saveDir);
	static Stage*	create(void);
	static Stage*	create(string fileDir);
	
	auto	getObjectList(void) { return &mObjectList; }
	auto	getFieldList(void) { return &mFieldList; }
	
	Scene*	objectPlacement(string fileName);
	Scene*	objectSetting(string objectName);
	void	fieldSetting(MeshField* field);

private:
	void	saveObject(FILE* fp);
	void	saveField(FILE* fp);		
	void	objectAssignmentTarget(FILE* fp, string order, Scene* scene);
	void	fieldAssignmentTarget(FILE* fp, string order, MeshField* field);
	void	stageAssignmentTarget(FILE* fp, string order);
	void	objectInstructionSearch(FILE* fp, Scene* scene);
	void	fieldInstructionSearch(FILE* fp, MeshField* field);
	void	stageInstructionSearch(FILE* fp);
	auto	setObject(FILE* fp);
	auto	setField(FILE* fp);
	void	setStage(FILE* fp);
	void	settingBranch(FILE* fp, string statement);

	list<Scene*>		mObjectList;		//オブジェクトリスト
	list<MeshField*>	mFieldList;		//フィールドリスト
};

#endif // !MAP_H
