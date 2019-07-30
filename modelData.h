/*****************************************************************************
modelData.h
Aythor	: ���@��
Data	: 2017_07_07
=============================================================================
Updata

*****************************************************************************/
#ifndef MODEL_DATA_H
#define MODEL_DATA_H
//////////////////////////////////////////////////////////////////////////////
//�C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include <filesystem>
#include <map>
#include "renderer.h"
#include "scene.h"

//////////////////////////////////////////////////////////////////////////////
//�l�[���X�y�[�X
//////////////////////////////////////////////////////////////////////////////
namespace sys = std::tr2::sys;

//////////////////////////////////////////////////////////////////////////////
//�O���錾
//////////////////////////////////////////////////////////////////////////////
class Renderer;

//////////////////////////////////////////////////////////////////////////////
//�\���̒�`
//////////////////////////////////////////////////////////////////////////////
typedef struct
{
	LPD3DXMESH			mesh;		//���b�V�����C���^�[�t�F�[�X
	DWORD				numMat;		//�}�e���A�����
	D3DMATERIAL9		*mat;		//�}�e���A�����
	LPDIRECT3DTEXTURE9	*tex;		//�e�N�X�`�����C���^�[�t�F�[�X
}XMODEL_DATA;

//////////////////////////////////////////////////////////////////////////////
//ModelData�N���X�錾
//////////////////////////////////////////////////////////////////////////////
class ModelData
{
public:
	ModelData(){}
	~ModelData(){}

	virtual HRESULT	init(void) = 0;
	virtual void	uninit(void) = 0;
	virtual void	draw(const Dmtx matrix) = 0;
	static	void	loadAllModel(void); 
	static	void	modelDataAllClear(void);

	//�Q�b�^�[
	string		getModelName(void){return mName;}

	//�Z�b�^�[
	static ModelData	*createModelData(string fileName);

protected:
	static ModelData	*create(ModelData *ModelType, string fileName);
	static void			readModelFile(sys::path path);
	LPDIRECT3DTEXTURE9	*mTex;			//�e�N�X�`�����C���^�[�t�F�[�X
	string				mName;			//���f���̖��O
};
//////////////////////////////////////////////////////////////////////////////
//Xmodel�N���X�錾
//////////////////////////////////////////////////////////////////////////////
class NullModel : public ModelData
{
public:
	HRESULT	init(void){return E_FAIL;}
	void	uninit(void){}
	void	draw(const Dmtx matrix){Renderer::getDevice()->SetTransform(D3DTS_WORLD, &matrix);}
	void	allClear(void) {}
};

//////////////////////////////////////////////////////////////////////////////
//Xmodel�N���X�錾
//////////////////////////////////////////////////////////////////////////////
class Xmodel : public ModelData
{
public:
	Xmodel(){}
	~Xmodel(){}

	HRESULT	init(void);
	void	uninit(void);
	void	draw(const Dmtx matrix);
	static void	allClear(void);

	static void	setModelData(sys::path path);
	HRESULT getMesh(LPD3DXMESH *cloneMehs)
	{
		return mModelData.mesh->CloneMeshFVF(mModelData.mesh->GetOptions(), FVF_VERTEX_3D, Renderer::getDevice(), cloneMehs);
	}

private:
	//�v���g�^�C�v�錾
	static map<string, XMODEL_DATA>		meshDataMap;
	HRESULT loadModel(void);

	//�ϐ��錾
	XMODEL_DATA		mModelData;
};

#endif // !MODEL_DATA_H
