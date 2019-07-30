/*****************************************************************************
right.h
Aythor	: ���@��
Data	: 2017_04_26
=============================================================================
Updata

*****************************************************************************/
#ifndef LIGHT_H
#define LIGHT_H
//////////////////////////////////////////////////////////////////////////////
//�萔��`
//////////////////////////////////////////////////////////////////////////////
#define MAX_LIGHT	(5)		//���C�g�̑���

//////////////////////////////////////////////////////////////////////////////
//�N���X�錾
//////////////////////////////////////////////////////////////////////////////
class Light
{
public:
	Light() {};
	~Light() {}
	static Light	*setLight	( D3DXVECTOR3 pos, D3DXVECTOR3 vecLight, D3DXCOLOR ambient, D3DXCOLOR diffuse );
	static void		releaseAll	(void);
	void	setPos	( D3DXVECTOR3 pos );

private:
	void	init	(D3DXVECTOR3 pos, D3DXVECTOR3 vecLight, D3DXCOLOR ambient, D3DXCOLOR diffuse, int num );

	static Light		*obj[MAX_LIGHT];	//�����|�C���^
	D3DLIGHT9			mLight;	//���C�g�̐ݒ�
	unsigned int		mId;	//�����̃��C�g�ԍ�
	static unsigned int	mNum;	//���C�g�̑���
};

#endif