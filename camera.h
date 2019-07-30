/*****************************************************************************
camera.h
Aythor	: ���@��
Data	: 2017_04_20
=============================================================================
Updata

*****************************************************************************/
#ifndef CAMERA_H
#define CAMERA_H

#include "scene.h"

//////////////////////////////////////////////////////////////////////////////
//�萔��`
//////////////////////////////////////////////////////////////////////////////
#define MAX_CAMERA	(4)

//////////////////////////////////////////////////////////////////////////////
//�N���X��`
//////////////////////////////////////////////////////////////////////////////
class Camera : public Scene
{
public:
	Camera();
	~Camera();
	HRESULT		init(D3DXVECTOR3 pos, D3DXVECTOR3 at, D3DXVECTOR3 up, float len);
	void		uninit() {}
	void		update(void);
	void		draw() {}

	static Camera	*create(D3DXVECTOR3 pos, D3DXVECTOR3 at, D3DXVECTOR3 up, float len);

	void	setPosEye(vec3 pos){mTransform.pos = vec3::conv(pos);}
	void	setPosAt(vec3 pos){mPosAt = vec3::conv(pos);}
	void	setAngle(vec2 angle){mAngle = vec2::conv(angle);}
	void	setAspect(float as)
	{
		mAspect = as;
		setCamera();
	}
	void	rollAt(vec3 angle) 
	{
		mPosAt = D3DXVECTOR3(
			mLen * angle.x + mTransform.pos.x,
			mLen * angle.y + mTransform.pos.y,
			mLen * angle.z + mTransform.pos.z);
	}
	void	moveEye(vec3 vec, float move)
	{
		mTransform.pos += D3DXVECTOR3(
			move * vec.x,
			move * vec.y,
			move * vec.z);
	}
	void setViewMtx(D3DXMATRIX mtx){mView = mtx;}
	void setFovy(float fovy){mFovy = fovy; setCamera();}

	D3DXMATRIX	getViewMtx(void);
	D3DXVECTOR3	getEye(void) {return mTransform.pos;}
	D3DXVECTOR3	getAt(void) {return mPosAt;}
	D3DXVECTOR2 getAngle(void) {return mAngle;}
	auto		getAngleAddr(void) {return &mAngle;}
	auto		getEyeAddr(void) {return &mTransform.pos;}
	auto		getAtAddr(void) {return &mPosAt;}
	auto		getLenAddr(void) {return &mLen;}
	float		getLen(void) {return mLen;}
	float		getAspect(void) {return mAspect;}
	float		getFovy(void){return mFovy;}

private:
	//�v���g�^�C�v�錾
	void	setCamera(void);

	D3DXMATRIX	mView;		//�J�����s��
	D3DXVECTOR3	mPosAt;		//�����_
	D3DXVECTOR3	mVecUp;		//�J�����̕���
	D3DXMATRIX	mProj;		//�v���W�F�N�V�����s��
	D3DXVECTOR2	mAngle;		//�J�����̊p�x
	float		mLen;		//���S����̋���
	float		mAspect;	//�A�X�y�N�g��
	float		mFovy;		//����p
};

#endif