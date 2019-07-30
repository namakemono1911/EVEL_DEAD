/*****************************************************************************
right.h
Aythor	: ���@��
Data	: 2017_04_26
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "light.h"
#include "renderer.h"

//////////////////////////////////////////////////////////////////////////////
//�ÓI�����o�ϐ�������
//////////////////////////////////////////////////////////////////////////////
Light *Light::obj[MAX_LIGHT] = {NULL};
unsigned int	Light::mNum = 0;

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Light::init
//�Ԃ�l	: 
//����		: ���W�ݒ�
//////////////////////////////////////////////////////////////////////////////
void	Light::init	(D3DXVECTOR3 pos, D3DXVECTOR3 vecLight, D3DXCOLOR ambient, D3DXCOLOR diffuse, int num )
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9	device;

	//�f�o�C�X�擾
	device = Renderer::getDevice();

	//ID���
	mId = num;

	//���C�e�B���O������
	mLight.Type = D3DLIGHT_DIRECTIONAL;
	mLight.Diffuse = diffuse;					//���s�����̐F
	mLight.Ambient = ambient;					//�������̐F
	mLight.Position = pos;											//���C�g�̈ʒu
	//vecDir = D3DXVECTOR3(0.f, -300.f, 450.f);						//���s�����̌���
	D3DXVec3Normalize((D3DXVECTOR3*)&mLight.Direction, &vecLight);	//�x�N�g���̐��K��

	device->SetLight(mId, &mLight);									//�f�o�C�X��0�Ԗڂ̃��C�g��ݒ�
	device->LightEnable(mId, TRUE);									//0�ԃ��C�gON
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Light::setLight
//�Ԃ�l	: 
//����		: ������
//////////////////////////////////////////////////////////////////////////////
Light	*Light::setLight	(D3DXVECTOR3 pos, D3DXVECTOR3 vecLight, D3DXCOLOR ambient, D3DXCOLOR diffuse)
{
	for (int i = 0; i < MAX_LIGHT; i++)
	{
		if (obj[i] == NULL)
		{
			obj[i] = new Light;
			obj[i]->init(pos, vecLight, ambient, diffuse, i);
			mNum++;
			return obj[i];
		}
	}

	return NULL;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Light::setPos
//�Ԃ�l	: 
//����		: ���W�ݒ�
//////////////////////////////////////////////////////////////////////////////
void	Light::setPos	( D3DXVECTOR3 pos )
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9	device;		//�f�o�C�X���

	//�f�o�C�X���擾
	device = Renderer::getDevice();

	//���W�ݒ�
	mLight.Position = pos;

	//���C�g�ݒ�
	device->SetLight(mId, &mLight);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Light::release
//�Ԃ�l	: 
//����		: ���C�g�폜
//////////////////////////////////////////////////////////////////////////////
void Light::releaseAll(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9	device;
	device = Renderer::getDevice();

	for (int i = 0; i < MAX_LIGHT; i++)
	{
		if (obj[i] != NULL)
		{
			device->LightEnable(obj[i]->mId, false);								//mId�ԃ��C�gOff
			delete obj[i];
			obj[i] = NULL;
		}
	}
}
