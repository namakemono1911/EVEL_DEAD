/*****************************************************************************
modelData.h
Aythor	: ���@��
Data	: 2017_07_07
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include <string>
#include "main.h"
#include "modelData.h"
#include "directory.h"
#include "load.h"
#include "convenient.h"

/*
#####################################################################################################################
ModelData class
#####################################################################################################################
*/

//////////////////////////////////////////////////////////////////////////////
//�֐���	: ModelData::create
//�Ԃ�l	: 
//����		: ����
//////////////////////////////////////////////////////////////////////////////
ModelData * ModelData::create(ModelData *modelType, string fileName)
{
	modelType->mName = fileName;
	modelType->init();

	return modelType;
}


//////////////////////////////////////////////////////////////////////////////
//�֐���	: ModelData::readModelFile
//�Ԃ�l	: 
//����		: ���f���t�@�C����ǂݍ���
//////////////////////////////////////////////////////////////////////////////
void ModelData::readModelFile(sys::path path)
{
	if (path.extension().string() == ".x")
		Xmodel::setModelData(path);

	if (path.extension().string() == ".fbx")
	{

	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: ModelData::loadAllModel
//�Ԃ�l	: 
//����		: �f�B���N�g�����̑S�Ẵ��f���ǂݍ���
//////////////////////////////////////////////////////////////////////////////
void ModelData::loadAllModel(void)
{
	string currendDir = Directory::getCurrentDir("\\data\\model");
	auto pathList = Directory::fileAllReferenceInDirectory(currendDir, ".*");

#pragma omp parallel for
	for (auto it = pathList.begin(); it != pathList.end(); ++it)
		readModelFile(*it);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: ModelData::modelDataAllClear
//�Ԃ�l	: 
//����		: ���f���f�[�^�S�폜
//////////////////////////////////////////////////////////////////////////////
void ModelData::modelDataAllClear(void)
{
	Xmodel::allClear();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: ModelData::createModelData
//�Ԃ�l	: 
//����		: �f�B���N�g�����̑S�Ẵ��f���ǂݍ���
//////////////////////////////////////////////////////////////////////////////
ModelData *ModelData::createModelData(string fileName)
{
	if (fileName.find(".x") != UINT_MAX)
		return ModelData::create(new Xmodel, fileName);

	return new NullModel;
}

/*
#####################################################################################################################
Xmodel class
#####################################################################################################################
*/
map<string, XMODEL_DATA>		Xmodel::meshDataMap;

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Xmodel::init
//�Ԃ�l	: 
//����		: ������
//////////////////////////////////////////////////////////////////////////////
HRESULT Xmodel::init(void)
{
	if (meshDataMap.find(mName) == meshDataMap.end())
	{
		string text = "���݂��Ȃ����f���f�[�^�F" + mName;
		MessageBox(NULL, text.c_str(), "error", MB_OK);
		return E_FAIL;
	}

	mModelData = meshDataMap[mName.c_str()];
	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Xmodel::uninit
//�Ԃ�l	: 
//����		: �I��
//////////////////////////////////////////////////////////////////////////////
void Xmodel::uninit(void)
{
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Xmodel::draw
//�Ԃ�l	: 
//����		: �`��
//////////////////////////////////////////////////////////////////////////////
void Xmodel::draw(Dmtx matrix)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9	device = Renderer::getDevice();

#pragma omp parallel for
	for (int i = 0; i < (int)mModelData.numMat; i++)
	{
		//�s��ݒ�
		device->SetTransform(D3DTS_WORLD, &matrix);

		//�}�e���A���ݒ�
		device->SetMaterial(&mModelData.mat[i]);

		//�e�N�X�`���ǂݍ���
		device->SetTexture(0, mModelData.tex[i]);

		//���b�V���`��
		mModelData.mesh->DrawSubset(i);
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Xmodel::allClear
//�Ԃ�l	: 
//����		: ���f���f�[�^�S�폜
//////////////////////////////////////////////////////////////////////////////
void Xmodel::allClear(void)
{
	for (auto it = meshDataMap.begin(); it != meshDataMap.end(); ++it)
	{
		auto a = *it;
		if (meshDataMap[a.first].mesh != NULL)
		{
			meshDataMap[a.first].mesh->Release();
			meshDataMap[a.first].mesh = NULL;
		}
		
		//�e�N�X�`�����
		for (DWORD i = 0; i < meshDataMap[a.first].numMat; i++)
		{
			if (meshDataMap[a.first].tex[i] != NULL)
			{
				meshDataMap[a.first].tex[i]->Release();
				meshDataMap[a.first].tex[i] = NULL;
			}
		}

		//�e�N�X�`���|�C���^���
		delete[] meshDataMap[a.first].tex;
		delete[] meshDataMap[a.first].mat;
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Xmodel::setModelData
//�Ԃ�l	: 
//����		: �}�b�v�Ƀ��f�����o�^
//////////////////////////////////////////////////////////////////////////////
void Xmodel::setModelData(sys::path path)
{
	XMODEL_DATA			data; 
	LPD3DXBUFFER		buffer = NULL;		//�}�e���A�����
	HRESULT				hr;
	D3DMATERIAL9		matDef;
	D3DXMATERIAL		*mat;
	LPDIRECT3DDEVICE9	device = Renderer::getDevice();
	string				relativePath;

	//���΃p�X�ɕϊ�
	relativePath = path.generic_string();
	relativePath.erase(0, relativePath.find("data"));
	
	//���f���ǂݍ���
	hr = D3DXLoadMeshFromX(relativePath.c_str(),
		D3DXMESH_MANAGED,
		device,
		NULL,
		&buffer,
		NULL,
		&data.numMat,
		&data.mesh);

	if (FAILED(hr))
	{
		char message[192];
		sprintf(message, "%s�ǂݍ��݃G���[", path.filename().string().c_str());

		MessageBox(NULL, message, "error", MB_OK);
	}

	device->GetMaterial(&matDef);
	mat = (D3DXMATERIAL*)buffer->GetBufferPointer();

	//�}�e���A���ƃe�N�X�`�����I�m��
	data.mat = new D3DMATERIAL9[data.numMat];
	data.tex = new LPDIRECT3DTEXTURE9[data.numMat];

#pragma omp paralell for
	for (int i = 0; i < (int)data.numMat; i++)
	{
		data.mat[i] = mat[i].MatD3D;			//�}�e���A�����Z�b�g
		data.mat[i].Ambient = data.mat[i].Diffuse;	//����������
		data.tex[i] = NULL;						//�e�N�X�`��������

#pragma omp paralell
		{
			//�e�N�X�`���̓ǂݍ���
			if (mat[i].pTextureFilename != NULL && lstrlen(mat[i].pTextureFilename) > 0)
			{
				if (FAILED(D3DXCreateTextureFromFile(device, mat[i].pTextureFilename, &data.tex[i])))
				{
					string text = *mat[i].pTextureFilename + "���ǂݍ��߂܂���ł���";
					MessageBox(NULL, text.c_str(), "���f���e�N�X�`���G���[", MB_OK);
				}
			}
		}
	}

	//�}�e���A�������
	buffer->Release();
	buffer = NULL;

	meshDataMap[path.filename().string().c_str()] = data;
}