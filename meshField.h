/*****************************************************************************
meshField.h
Aythor	: ���@��
Data	: 2017_04_27
=============================================================================
Updata

*****************************************************************************/
#ifndef MESHFIELD_H
#define MESHFIELD_H
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include <string>
#include <list>
#include <vector>
#include <map>
#include "scene.h"
#include "mesh.h"

//////////////////////////////////////////////////////////////////////////////
//�萔��`
//////////////////////////////////////////////////////////////////////////////
#define	MAX_FIELD	(256)		//�t�B�[���h�̍ő吔

//////////////////////////////////////////////////////////////////////////////
//�O���錾
//////////////////////////////////////////////////////////////////////////////
class Mesh;

//////////////////////////////////////////////////////////////////////////////
//�N���X��`
//////////////////////////////////////////////////////////////////////////////
class Tyle
{
public:
	Tyle() { x = 0, y = 0; }
	Tyle(int refx, int refy) { x = refx; y = refy; }
	~Tyle() {}

	int		x;
	int		y;
};

class MeshField : public Mesh
{
public:
	MeshField(UINT priolity = PRIME_THIRD);
	~MeshField() {};

	//�v���g�^�C�v�錾
	HRESULT	init(void);
	void	uninit(void);
	void	update(void);
	void	draw(void);

	static void	release(MeshField *point);

	//�Q�b�^�[
	static float	getHeight(const Dvec3 pos);
	static auto		getTextureMap(void) { return mNameList; }
	static auto		getTextureNameList(void){return mTexNameList;}
	static auto		getTextureIdFormMap(string texName){return mNameList[texName];}
	auto			getNumTyle(void){return mNumTyle;}
	auto			getNumTyleAd(void) { return &mNumTyle; }
	auto			getColorAddr(void) { return &mColor; }
	auto			getTyleSize(void){return mTyleSize;}
	auto			getTyleSizeAddr(void){return &mTyleSize;}
	auto			getTextureId(void){return mNumTexture;}
	auto			getTextureIdAddr(void) { return &mNumTexture; }

	//�Z�b�^�[
	void	setVal(D3DXVECTOR2 size, Tyle numTyle, int textureID, Dcolor color);
	void	setTyleSize(Dvec2 size){mTyleSize = size;}
	void	setNumTyle(Tyle tyle){mNumTyle = tyle;}
	void	setTextureId(UINT num){mNumTexture = num;}
	void	setColor(Dcolor color){mColor = color;}

	static MeshField	*create(Dvec3 pos, D3DXVECTOR2 size, Tyle numTyle, Dvec3 rot, D3DXCOLOR color, D3DXVECTOR2 texMove, int textureID);
	static MeshField	*create(MeshField field);
	static void			loadTex();

private:
	//�v���g�^�C�v�錾
	HRESULT	makeVtx(Tyle numTyle, D3DXCOLOR color);
	HRESULT	makeIdx(Tyle numTyle);

	//�ϐ��錾
	static LPDIRECT3DTEXTURE9	*mTex;			//�e�N�X�`���o�b�t�@
	static vector<string>		mTexNameList;	//�e�N�X�`�������X�g
	static map<string, UINT>	mNameList;		//���O���X�g
	static list<MeshField*>		mFieldList;		//�t�B�[���h���X�g

	Dvec3				*mVtxPos;		//���_�̈ʒu���
	Dvec2				mTyleSize;		//1�^�C���̑傫��
	Tyle				mNumTyle;		//�c�����^�C����
	Tyle				mSaveNumTyle;	//�O��̃^�C�����ۑ�	
	Dcolor				mColor;			//���_�F
	int					mNumTexture;	//�g���Ă���e�N�X�`���̃i���o�[		
	bool				mDelete;		//�폜�t���O
	D3DMATERIAL9		mMat;			//�}�e���A�����
};

#endif