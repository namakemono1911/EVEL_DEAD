/*****************************************************************************
meshField.cpp
Aythor	: ���@��
Data	: 2017_04_27
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "meshField.h"
#include "renderer.h"
#include "convenient.h"

//////////////////////////////////////////////////////////////////////////////
//�ÓI�����o�ϐ�������
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9	*MeshField::mTex = NULL;
map<string, UINT>	MeshField::mNameList;
list<MeshField*>	MeshField::mFieldList;
vector<string>		MeshField::mTexNameList;

//////////////////////////////////////////////////////////////////////////////
//�֐���	: MeshField()
//�Ԃ�l	: 
//����		: �R���X�g���N�^
//////////////////////////////////////////////////////////////////////////////
MeshField::MeshField(UINT priolity) :Mesh(priolity)
{
	//�����̃|�C���^�����X�g�ɒǉ�
	mFieldList.push_back(this);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: MeshField::init
//�Ԃ�l	: 
//����		: ������
//////////////////////////////////////////////////////////////////////////////
HRESULT MeshField::init(void)
{
	//�ϐ��錾
	mDelete = false;

	// Set the RGBA for diffuse reflection.
	mMat.Diffuse.r = 1.0f;
	mMat.Diffuse.g = 1.0f;
	mMat.Diffuse.b = 1.0f;
	mMat.Diffuse.a = 1.0f;

	// Set the RGBA for ambient reflection.
	mMat.Ambient.r = 1.0f;
	mMat.Ambient.g = 1.0f;
	mMat.Ambient.b = 1.0f;
	mMat.Ambient.a = 1.0f;

	// Set the color and sharpness of specular highlights.
	mMat.Specular.r = 1.0f;
	mMat.Specular.g = 1.0f;
	mMat.Specular.b = 1.0f;
	mMat.Specular.a = 1.0f;
	mMat.Power = 50.0f;

	// Set the RGBA for emissive color.
	mMat.Emissive.r = 0.0f;
	mMat.Emissive.g = 0.0f;
	mMat.Emissive.b = 0.0f;
	mMat.Emissive.a = 0.0f;

	mMyName = "meshField";

	return	S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: MeshField::uninit
//�Ԃ�l	: 
//����		: �I��
//////////////////////////////////////////////////////////////////////////////
void	MeshField::uninit(void)
{
	//���X�g�S�폜
	for (auto it = mFieldList.begin(); it != mFieldList.end();)
		it = mFieldList.erase(it);

	Mesh::uninit();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: MeshField::update
//�Ԃ�l	: 
//����		: �X�V
//////////////////////////////////////////////////////////////////////////////
void	MeshField::update(void)
{
	//�ϐ��錾
	VERTEX3D	*pVtx;		//���_���|�C���^
	int			x, z;		//x��z�̃��[�v
	int			num;		//�K�v�Ȓ��_��
	Dvec3	fullSize;	//�t�B�[���h�S�̂̃T�C�Y

	//=============================
	// �����_�K�v��
	//=============================
	num = (int)((mNumTyle.x + 1) * (mNumTyle.y + 1));

	//=============================
	// �e�N�X�`���A�j��
	//=============================
	bindTexBuf(mTex[mNumTexture]);
	setTexPos(D3DXVECTOR2(
		getTexPos().x + getTexMove().x,
		getTexPos().y + getTexMove().y));

	//=============================
	// ���_�o�b�t�@���ύX
	//=============================
	if (mNumTyle.x != mSaveNumTyle.x || mNumTyle.y != mSaveNumTyle.y)
	{
		makeVtx(mNumTyle, mColor);
		mSaveNumTyle = mNumTyle;
	}

	//=============================
	// ���_�o�b�t�@�o�^
	//=============================
	getVtxBuf()->Lock(0, 0, (void**)&pVtx, 0);

	//�S�̂̃T�C�Y�v�Z
	fullSize = Dvec3(
		mNumTyle.x * mTyleSize.x,
		0.f,
		mNumTyle.y * mTyleSize.y);

	for (z = 0; z < mNumTyle.y + 1; z++)
	{
		for (x = 0; x < mNumTyle.x + 1; x++)
		{
			//���_
			pVtx[0].pos = Dvec3(
				(mTyleSize.x * x) - (fullSize.x * 0.5f),
				0.f,
				-(mTyleSize.y * z) + (fullSize.z * 0.5f));

			//�e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(getTexPos().x + (float)x, getTexPos().y + (float)z);

			//���_�F
			pVtx->color = mColor;

			//�@���x�N�g��
			//if (x == 0 || x >= (int)mNumTyle.x ||
			//	z == 0 || z >= (int)mNumTyle.y)
			//{
			//	pVtx[0].nor = Dvec3(0.f, 1.f, 0.f);
			//}
			//else
			//{
			//	if ((int)mNumTyle.x * z + x == 10)
			//	{
			//		int i = 0;
			//		i++;
			//	}

			//	vec3 normal;	//�@��

			//	normal = vec3::crossProduct(pVtx[-((int)mNumTyle.x + 1)].pos, pVtx[(int)mNumTyle.x + 1].pos);
			//	normal = vec3::normalize(normal);
			//	normal.y = (float)fabs(normal.y);
			//	pVtx[0].nor = Dvec3(normal.x, normal.y, normal.z);
			//}

			//�|�C���^�ړ�
			pVtx++;
		}
	}

	getVtxBuf()->Unlock();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: MeshField::draw
//�Ԃ�l	: 
//����		: �X�V
//////////////////////////////////////////////////////////////////////////////
void	MeshField::draw(void)
{
	Renderer::getDevice()->SetMaterial(&mMat);
	Mesh::draw();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: MeshField::release
//�Ԃ�l	: 
//����		: ���X�g�폜
//////////////////////////////////////////////////////////////////////////////
void MeshField::release(MeshField * point)
{
	for (auto it = mFieldList.begin(); it != mFieldList.end();)
	{
		if (*it == point)
		{
			auto work = *it;
			work->Mesh::release();
			it = mFieldList.erase(it);
			break;
		}
		else
			++it;
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: MeshField::create
//�Ԃ�l	: 
//����		: �t�B�[���h�ݒ�
//////////////////////////////////////////////////////////////////////////////
MeshField	*MeshField::create(Dvec3 pos, D3DXVECTOR2 size, Tyle numTyle, Dvec3 rot, D3DXCOLOR color, D3DXVECTOR2 texMove, int textureID)
{
	//�ϐ��錾

	//MeshField����
	MeshField *field = new MeshField;

	//�ϐ����
	field->setVal(size, numTyle, textureID, color);
	field->setAll(pos, rot, color, D3DXVECTOR2(0.f, 0.f), texMove);
	field->mNumTyle = numTyle;
	field->mSaveNumTyle = numTyle;

	//������
	field->init();

	//�e�N�X�`���o�C���h
	field->bindTexBuf(mTex[textureID]);

	//���_�o�b�t�@�쐬
	field->makeVtx(numTyle, color);

	return field;
}

MeshField * MeshField::create(MeshField field)
{
	auto	meshField = new MeshField;
	*meshField = field;

	return meshField;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: MeshField::setVal
//�Ԃ�l	: 
//����		: �ϐ����
//////////////////////////////////////////////////////////////////////////////
void	MeshField::setVal(D3DXVECTOR2 size, Tyle numTyle, int textureID, Dcolor color)
{
	mTyleSize = size;
	mNumTyle = numTyle;
	mNumTexture = textureID;
	mColor = color;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: loadTex
//�Ԃ�l	: 
//����		: �e�N�X�`���ǂݍ���
//////////////////////////////////////////////////////////////////////////////
void	MeshField::loadTex(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9	device = Renderer::getDevice();

	//���O���X�g�쐬
	list<string> textureList = Conveni::getDirFile("data/texture/field", "*");

	mTex = new LPDIRECT3DTEXTURE9[textureList.size()];

	int i = 0;
	for (auto it = textureList.begin(); it != textureList.end(); ++it, i++)
	{
		string	textureDir = "data/texture/field/" + *it;
		mTexNameList.push_back(textureDir);
		mNameList[textureDir] = i;

		//�e�N�X�`���̓ǂݍ���
		if (FAILED(D3DXCreateTextureFromFile(device, textureDir.c_str(), &mTex[i])))
		{
			MessageBox(NULL, "�G���[", "field�G���[", MB_OK);
		}
	}

}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: makeVtx
//�Ԃ�l	: 
//����		: �|���S���`��ʒu�ݒ�
//////////////////////////////////////////////////////////////////////////////
HRESULT	MeshField::makeVtx(Tyle numTyle, D3DXCOLOR color)
{
	//�ϐ��錾
	VERTEX3D	*pVtx;		//���z�A�h���X�p�|�C���^
	Dvec3		pos;		//�`��ʒu
	int			x, z;		//x��z�̃��[�v
	int			num;		//�K�v�Ȓ��_��
	Dvec3		fullSize;	//�t�B�[���h�S�̂̃T�C�Y
	LPDIRECT3DVERTEXBUFFER9	vtx = NULL;	//���_�o�b�t�@

										//=============================
										// �����_�K�v��
										//=============================
	num = (int)((mNumTyle.x + 1) * (mNumTyle.y + 1));

	//�K�v�ȃv���~�e�B�u��
	UINT	numPtv;
	numPtv = (int)(mNumTyle.x * mNumTyle.y * 2 + (mNumTyle.y - 1) * 4);

	//�v���~�e�B�u���Z�b�g
	setNumPrim(numPtv);

	//���_�����ʒu��񐶐�
	mVtxPos = new Dvec3[num];

	//=============================
	// ���_�o�b�t�@�쐬
	//=============================
	if ((vtx = makeVtxBuf(num)) == NULL)
	{
		return E_FAIL;
	}

	//�S�̂̃T�C�Y�v�Z
	fullSize = Dvec3(
		mNumTyle.x * mTyleSize.x,
		0.f,
		mNumTyle.y * mTyleSize.y);

	//=============================
	// ���_���o�^
	//=============================
	vtx->Lock(0, 0, (void**)&pVtx, 0);

	for (z = 0; z < mNumTyle.y + 1; z++)
	{
		for (x = 0; x < mNumTyle.x + 1; x++)
		{
			//���_
			mVtxPos[((int)mNumTyle.x + 1) * z + x] =
				pVtx[0].pos = Dvec3(
				(mTyleSize.x * x) - (fullSize.x * 0.5f),
					0.f,
					-(mTyleSize.y * z) + (fullSize.z * 0.5f));

			//���_�F
			pVtx[0].color = color;

			//�@���x�N�g��
			pVtx[0].nor = Dvec3(0, 1, 0);
			//if (x == 0 || x == (int)mNumTyle.x - 1 ||
			//	z == 0 || z == (int)mNumTyle.y - 1)
			//{
			//	pVtx[0].nor = Dvec3(0.f, 1.f, 0.f);
			//}
			//else
			//{
			//	vec3 normal;	//�@��

			//	normal = vec3::crossProduct(pVtx[-((int)mNumTyle.x + 1)].pos, pVtx[(int)mNumTyle.x + 1].pos);
			//	normal = vec3::normalize(normal);
			//	pVtx[0].nor = Dvec3(normal.x, normal.y, normal.z);
			//}

			//�e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2((float)x, (float)z);

			//�|�C���^�ړ�
			pVtx++;
		}
	}

	vtx->Unlock();

	//���_�o�b�t�@�o�C���h
	bindVtxBuf(vtx);

	//=============================
	// �C���f�b�N�X�쐬
	//=============================
	makeIdx(numTyle);

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: makeIdx
//�Ԃ�l	: 
//����		: �|���S���`��ʒu�ݒ�
//////////////////////////////////////////////////////////////////////////////
HRESULT	MeshField::makeIdx(Tyle numTyle)
{
	//�ϐ��錾
	WORD		*pIdx;	//�C���f�b�N�X�ԍ�
	int			x, z;	//x��z��loop
	int			num;	//�K�v�ȃC���f�b�N�X��
	LPDIRECT3DINDEXBUFFER9	idx = NULL; //�C���f�b�N�X�o�b�t�@

										//=============================
										// �����_�K�v��
										//=============================
	num = (int)((numTyle.x + 1) * (numTyle.y * 2));
	num += (int)((numTyle.y - 1) * 2);

	//=============================
	// �C���f�b�N�X�쐬
	//=============================
	if ((idx = makeIdxBuf(num)) == NULL)
	{
		return E_FAIL;
	}

	//=============================
	// �C���f�b�N�X�o�^
	//=============================
	idx->Lock(0, 0, (void**)&pIdx, 0);

	for (z = 0; z < (int)mNumTyle.y; z++)
	{
		for (x = 0; x < (int)mNumTyle.x + 1; x++)
		{
			//�C���f�b�N�X�o�^
			pIdx[0] = (WORD)((mNumTyle.x + 1) * (z + 1) + x);
			pIdx[1] = (WORD)((mNumTyle.x + 1) * z + x);

			//�|�C���^�ړ�
			pIdx += 2;
		}

		//�k�ރ|���S��
		if (z < mNumTyle.y - 1)
		{
			//�C���f�b�N�X�o�^
			x--;
			pIdx[0] = ((WORD)mNumTyle.x + 1) * (WORD)z + (WORD)x;
			pIdx[1] = pIdx[0] + (WORD)mNumTyle.x + 2;

			//�|�C���^�ړ�
			pIdx += 2;
		}
	}

	idx->Unlock();

	//�C���f�b�N�X�o�b�t�@�o�C���h
	bindIdxBuf(idx);

	return	S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: MeshField::getHeight
//�Ԃ�l	: 
//����		: �t�B�[���h�̍����擾
//////////////////////////////////////////////////////////////////////////////
float	MeshField::getHeight(const Dvec3 pos)
{
	//�ϐ��錾
	vec3		work(pos);		//�Ώۂ̈ʒu
	vec3		vtx[4];			//���_���W

	for (auto it = mFieldList.begin(); it != mFieldList.end(); ++it)
	{
		auto ptr = *it;

		if (ptr->mNumTyle.x <= 1)
			break;

		for (int y = 0; y < (int)ptr->mNumTyle.x; y++)
		{
			for (int x = 0; x < (int)ptr->mNumTyle.y; x++)
			{
				vtx[0] = vec3(ptr->mVtxPos[((int)ptr->mNumTyle.x + 1) * y + x]);
				vtx[1] = vec3(ptr->mVtxPos[((int)ptr->mNumTyle.x + 1) * y + x + 1]);
				vtx[2] = vec3(ptr->mVtxPos[((int)ptr->mNumTyle.x + 1) * y + x + (int)ptr->mNumTyle.x + 2]);
				vtx[3] = vec3(ptr->mVtxPos[((int)ptr->mNumTyle.x + 1) * y + x + (int)ptr->mNumTyle.x + 1]);

				for (int face = 0; face < 2; face++)
				{
					if (face % 2 == 0 &&
						vec3::crossProduct(vtx[1], work, vtx[0]).y >= 0 &&
						vec3::crossProduct(vtx[2], work, vtx[1]).y >= 0 &&
						vec3::crossProduct(vtx[0], work, vtx[2]).y >= 0)
					{
						vec3 normal;	//�ʂ̖@���x�N�g��
						float test;

						normal = vec3::normalVec(vtx[0], vtx[1], vtx[2]);
						test = vtx[0].y - ((work.x - vtx[0].x) * normal.x + (work.z - vtx[0].z) * normal.z) / normal.y;
						return test;
					}

					if (face % 2 == 1 &&
						vec3::crossProduct(vtx[0], work, vtx[3]).y >= 0 &&
						vec3::crossProduct(vtx[2], work, vtx[0]).y >= 0 &&
						vec3::crossProduct(vtx[3], work, vtx[2]).y >= 0)
					{
						vec3 normal;	//�ʂ̖@���x�N�g��
						float check[3];
						float test;
						check[0] = vec3::normalVec(vtx[3], vtx[0], work).y;
						check[1] = vec3::normalVec(vtx[0], vtx[2], work).y;
						check[2] = vec3::normalVec(vtx[2], vtx[3], work).y;

						normal = vec3::normalVec(vtx[0], vtx[2], vtx[3]);
						test = vtx[0].y - ((work.x - vtx[0].x) * normal.x + (work.z - vtx[0].z) * normal.z) / normal.y;
						return test;
					}
				}
			}
		}
	}

	return 0;
}