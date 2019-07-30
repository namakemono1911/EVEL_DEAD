/*****************************************************************************
convenient.cpp
Aythor	: ���@��
Data	: 2017_08_18
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "transform.h"
#include "convenient.h"

//////////////////////////////////////////////////////////////////////////////
//�֐���	: getDirFile()
//
//����		: dirName	�f�B���N�g���p�X
//			: ext		�g���q
//
//�Ԃ�l	: �t�@�C�������X�g
//����		: �f�B���N�g�����̎w��g���q�t�@�C�����X�g�擾
//////////////////////////////////////////////////////////////////////////////
std::list<std::string> Conveni::getDirFile(const std::string dirName, const std::string ext)
{
	HANDLE	find;
	WIN32_FIND_DATA	findData;
	std::list<std::string>	fileName;

	std::string	search = dirName + "/*." + ext;

	find = FindFirstFile(search.c_str(), &findData);

	//�G���[���b�Z�[�W
	if (find == INVALID_HANDLE_VALUE)
	{
		std::string error = dirName + "�t�H���_���J���܂���ł����B";
		MessageBox(NULL, error.c_str(), "error", MB_OK);
		return std::list<std::string>();
	}

	//�t�@�C���T��
	while (FindNextFile(find, &findData))
	{
		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{

		}
		else
		{
			fileName.push_back(findData.cFileName);
		}
	}

	FindClose(find);
	return fileName;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: getCharPosition()
//
//����		: str		�Ώە�����
//			: target	�T����������
//
//�Ԃ�l	: �t�@�C�������X�g
//����		: �f�B���N�g�����̎w��g���q�t�@�C�����X�g�擾
//////////////////////////////////////////////////////////////////////////////
int Conveni::getCharPosition(const string str, const string target)
{
	for (int i = 0; str[i] != '\0'; i++)
		for (int j = 0; target[j] != '\0'; j++)
			if (str[i] == target[j])
				return i;

	return -1;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Conveni::setMatrix
//�Ԃ�l	: 
//����		: �ʏ�s����f�o�C�X�ɐݒ�
//////////////////////////////////////////////////////////////////////////////
Dmtx Conveni::setMatrix(Dvec3 pos, Dvec3 rot, Dvec3 size)
{
	//�ϐ��錾
	D3DXMATRIX	world;				//���[���h�s��
	D3DXMATRIX	scaleMtx;			//�X�P�[��
	D3DXMATRIX	rotMtx;				//��]�s��
	D3DXMATRIX	moveMtx;			//���s�ړ��s��

									//�s��ݒ�
	D3DXMatrixIdentity(&world);
	D3DXMatrixScaling(&scaleMtx, size.x, size.y, size.z);
	D3DXMatrixRotationYawPitchRoll(&rotMtx, rot.x, rot.y, rot.z);
	D3DXMatrixTranslation(&moveMtx, pos.x, pos.y, pos.z);

	//�s�񍇐�
	world *= scaleMtx * rotMtx * moveMtx;

	return world;
}

Dmtx Conveni::setMatrix(Transform trans)
{
	return setMatrix(trans.pos, trans.rot, trans.size);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Conveni::setQuatenionMatrixToDevice
//�Ԃ�l	: 
//����		: �N�H�[�^�j�I�����g�����s����f�o�C�X�ɐݒ�
//////////////////////////////////////////////////////////////////////////////
Dmtx Conveni::setQuatenionMatrix(Dvec3 pos, Dvec3 quatenion, Dvec3 size)
{
	//�ϐ��錾
	DMtx	world;
	DMtx	scaleMtx;
	DMtx	rotMtx;
	DMtx	moveMtx;
	DQuate	quatenionMtx(quatenion.x, quatenion.y, quatenion.z, 0);

	//�s��ݒ�
	D3DXMatrixIdentity(&world);
	D3DXMatrixScaling(&scaleMtx, size.x, size.y, size.z);
	D3DXMatrixRotationQuaternion(&rotMtx, &quatenionMtx);
	D3DXMatrixTranslation(&moveMtx, pos.x, pos.y, pos.z);

	//�s�񍇐�
	world *= scaleMtx * rotMtx * moveMtx;

	//�s����f�o�C�X�ɐݒ�
	return world;
}
