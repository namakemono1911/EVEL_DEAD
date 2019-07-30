/*****************************************************************************
mesh.h
Aythor	: ���@��
Data	: 2017_05_18
=============================================================================
Updata

*****************************************************************************/
#ifndef MESH_H
#define MESH_H

#include "scene.h"

//////////////////////////////////////////////////////////////////////////////
//�O���錾
//////////////////////////////////////////////////////////////////////////////
class Scene;

//////////////////////////////////////////////////////////////////////////////
//�N���X��`
//////////////////////////////////////////////////////////////////////////////
class Mesh : public Scene
{
public:
	Mesh(UINT priolity = PRIME_THIRD):Scene(priolity){}
	~Mesh(){}

	HRESULT	init	( void );
	void	uninit	( void );
	void	update	( void );
	void	draw	( void );
	D3DXVECTOR3	getSize	( void ){return D3DXVECTOR3(0.f, 0.f, 0.f);}

	//�Z�b�^�[
	void	bindVtxBuf	(LPDIRECT3DVERTEXBUFFER9 vtx){mVtxBuf = vtx;}
	void	bindIdxBuf	(LPDIRECT3DINDEXBUFFER9	idx){mIdxBuf = idx;}
	void	loadTex		(const char *texName);
	void	bindTexBuf	(LPDIRECT3DTEXTURE9	tex){mTex = tex;}
	void	setNumVtx	(UINT numVtx){mNumVtx = numVtx;}
	void	setNumPrim	(UINT numPrim){mNumPrim = numPrim;}
	LPDIRECT3DVERTEXBUFFER9	makeVtxBuf	(const UINT numVtx);
	LPDIRECT3DINDEXBUFFER9	makeIdxBuf	(const UINT numIdx);
	void	setTexPos	(D3DXVECTOR2 texPos){mTexPos = texPos;}
	void	setRot(D3DXVECTOR3 rot){mTransform.rot = rot;}
	void	setAll		(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR color, D3DXVECTOR2 texPos, D3DXVECTOR2 texMove)
	{
		mTransform.pos = pos;
		mTransform.rot = rot;
		mColor = color;
		mTexPos = texPos;
		mTexMove = texMove;
	}

	//�Q�b�^�[
	LPDIRECT3DVERTEXBUFFER9	getVtxBuf	(void){return mVtxBuf;}
	D3DXVECTOR2		getTexPos	(void){return mTexPos;}
	D3DXVECTOR2		getTexMove	(void){return mTexMove;}
	UINT			getNumVtx	(void){return mNumVtx;}

private:
	//�v���g�^�C�v�錾
	void	setMtx	(LPDIRECT3DDEVICE9 device);

	LPDIRECT3DVERTEXBUFFER9		mVtxBuf;	//���_�o�b�t�@
	LPDIRECT3DINDEXBUFFER9		mIdxBuf;	//�C���f�b�N�X�o�b�t�@
	LPDIRECT3DTEXTURE9			mTex;		//�e�N�X�`��

	D3DXCOLOR		mColor;		//���_�F
	D3DXVECTOR2		mTexPos;	//�e�N�X�`�����W
	D3DXVECTOR2		mTexMove;	//�e�N�X�`���A�j���[�V�����̈ړ����x
	UINT			mNumVtx;	//�`�悷�钸�_��
	UINT			mNumPrim;	//�`�悷��ʂ̐�	
};

#endif