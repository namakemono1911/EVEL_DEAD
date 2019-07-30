#include "main.h"
#include "manager.h"
#include "camera.h"
#include "playerEdit.h"



PlayerEdit::PlayerEdit()
{
}


PlayerEdit::~PlayerEdit()
{
}

HRESULT PlayerEdit::init(void)
{
	mCamera = (Camera*)Scene::getTypeList(Scene::CAMERA).front();
	return S_OK;
}

void PlayerEdit::uninit(void)
{

}

void PlayerEdit::update(void)
{
	//���̓f�o�C�X���
	auto	*mouse = Manager::getMouse();
	auto	*key = Manager::getKeyboard();

	//���s�ړ�
	auto	vec = mCamera->getAt() - mCamera->getEye();
	auto	moveVec = Dvec3(0, 0, 0);
	if (key->getPress(DIK_W))		//�O
		moveVec = vec;
	if (key->getPress(DIK_S))		//���
		moveVec = vec * -1.f;
	if (key->getPress(DIK_A))		//��
		moveVec += vec3::DcrossProduct(vec, vec3(0.f, 1.f, 0.f));
	else if (key->getPress(DIK_D))	//�E
		moveVec += vec3::DcrossProduct(vec3(0.f, 1.f, 0.f), vec);
	if (key->getPress(DIK_LSHIFT))
		moveVec = Dvec3(0.f, -1.f, 0.f);
	if (key->getPress(DIK_SPACE))
		moveVec = Dvec3(0, 1, 0);

	if (moveVec != Dvec3(0, 0, 0))
		moveVec = vec3::Dnormalize(moveVec);
	mCamera->moveEye(moveVec, 1.f);

	//���_����
	float len = mCamera->getLen();
	vec2 mCameraAngle = mCamera->getAngle();
	if (mouse->getPress(MOUSE_RIGHT))
	{
		mCameraAngle.x += fmod(mouse->getMoving().x * mSens, PI);
		mCameraAngle.y += -mouse->getMoving().y * mSens;

		//if (mCameraAngle.y >= PI * 0.5f)			//�p
		//	mCameraAngle.y = PI * 0.5f;

		//if (mCameraAngle.y <= PI)		//��p
		//	mCameraAngle.y = PI;

		mCamera->setAngle(mCameraAngle);
		mTransform.rot = Dvec3(mCameraAngle.x, mCameraAngle.y, 0.f);

		//���ʍ��W
		Dvec3 a = mCamera->getAt();
		vec3 eye = mCamera->getEye();
		float len = mCamera->getLen();
		vec3 at(
			len * cosf(-mCameraAngle.y) * sinf(mCameraAngle.x + PI) + eye.x,
			len * sinf(-mCameraAngle.y) + eye.y,
			len * cosf(-mCameraAngle.y) * cosf(mCameraAngle.x + PI) + eye.z);
		mCamera->setPosAt(at);
	}
}