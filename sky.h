/*****************************************************************************
���b�V���h�[���`��
Aythor	: ���@��
Data	: 2016_12_23
=============================================================================
Updata

*****************************************************************************/
#ifndef	MESH_DOME_H
#define	MESH_DOME_H
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "mesh.h"

//////////////////////////////////////////////////////////////////////////////
//�萔��`
//////////////////////////////////////////////////////////////////////////////
#define	MAX_DOME	(5)		//�t�B�[���h�̍ő吔

//////////////////////////////////////////////////////////////////////////////
//�\���̒�`
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//�N���X��`
//////////////////////////////////////////////////////////////////////////////
class Sky : public Mesh
{
public:
	//�񋓌^��`
	typedef	enum
	{
		SKY_TEX_001 = 0,
		SKY_TEX_MAX,			//�e�N�X�`������
		SKY_TEX_NULL,			//null
	}SKY_TEX;

	Sky(UINT priolity = PRIME_THIRD):Mesh(priolity){}
	~Sky(){}

	HRESULT	init(void);
	void	uninit(void);
	void	update(void);
	void	draw(void);
	D3DXVECTOR3	getPos(void){return mPos;}
	D3DXVECTOR3	getSize(void){return D3DXVECTOR3(mNumTyle.x, mNumTyle.y, 0.f);}
	
	//�Z�b�^�[
	void	setVal(D3DXVECTOR3 pos, D3DXVECTOR2 numTyle, D3DXCOLOR color, D3DXVECTOR3 rot, float len, SKY_TEX tex);

	static Sky		*create (D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR2 numTyle, D3DXCOLOR color, float len, SKY_TEX tex);
	static HRESULT	loadTex	();

private:
	//�v���g�^�C�v�錾
	HRESULT	makeVtx(D3DXVECTOR2 numTyle);
	HRESULT	makeIdx(void);

	//�ϐ��錾
	static LPDIRECT3DTEXTURE9	mTexBuf[SKY_TEX_MAX];		//�e�N�X�`���o�b�t�@
	const static char	*mTexName[SKY_TEX_MAX];	//�e�N�X�`����
	D3DXVECTOR3	mPos;		//�\�����W
	D3DXVECTOR2	mNumTyle;	//�c�����^�C����
	D3DXCOLOR	mColor;		//���_�F
	D3DXVECTOR3	mRot;		//�|���S���̉�]��
	float		mLen;		//���a
	SKY_TEX		mTex;		//�e�N�X�`���̎��
};

#endif