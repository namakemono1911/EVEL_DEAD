#include "main.h"
#include "manager.h"
#include "mode.h"
#include "scene.h"
#include "player.h"
#include "playerMoving.h"
#include "playerNeutral.h"
#include "playerDebug.h"

void PlayerMoving::update()
{
	if (!mPlayer->isPushedUp() && !mPlayer->isPushedDown() &&
		!mPlayer->isPushedRight() && !mPlayer->isPushedLeft())
	{
		mPlayer->setState(new PlayerNeutral(mPlayer));
		return;
	}

	if (mPlayer->isPushedDebug())
	{
		mPlayer->setState(new PlayerDebug(mPlayer));
		return;
	}
	setMoveVec();

	//�����蔻��
	for (const auto& scene : Scene::getTypeList(Scene::OBJECT))
		collisionSearch(scene->getCollision());

	mPlayer->setPos(mMoveVec * mPlayer->moveSpeed() + mPlayer->getPos());

	mCamera->setPosEye(mPlayer->getPos());

	viewpointOperation();
}

void PlayerMoving::setMoveVec(void)
{
	//�����x�N�g��
	vec2 mCameraAngle = mCamera->getAngle();
	mMoveVec = Dvec3(0.f, 0.f, 0.f);
	Dvec3 vec = Dvec3(
		sinf(mCameraAngle.x),
		0.f,
		cosf(mCameraAngle.x));

	//�ړ�����
	if (mPlayer->isPushedUp())			//�O
		mMoveVec = vec * -1.f;

	if (mPlayer->isPushedDown())		//���
		mMoveVec = vec;

	if (mPlayer->isPushedLeft())		//��
		mMoveVec += vec3::DcrossProduct(vec3(0.f, 1.f, 0.f), vec);

	else if (mPlayer->isPushedRight())	//�E
		mMoveVec += vec3::DcrossProduct(vec, vec3(0.f, 1.f, 0.f));

	if (mMoveVec != Dvec3(0, 0, 0))
		D3DXVec3Normalize(&mMoveVec, &mMoveVec);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Player::collisionSearch
//�Ԃ�l	: 
//����		: �R���W�����T��
//////////////////////////////////////////////////////////////////////////////
void PlayerMoving::collisionSearch(CollisionManager * colManager)
{
	if (colManager == NULL)
		return;

	Dvec3 clossPos;
	Dvec3 axis;
	if (colManager->hitByRayAll(&clossPos, &axis, mPlayer->getPos(), mPlayer->getPos() + mMoveVec * 5.f))
		mMoveVec = Collision::faceScrachVec(mMoveVec, axis);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Player::processPerCollisionType
//�Ԃ�l	: 
//����		: �R���W�����^�C�v���Ƃɏ���
//////////////////////////////////////////////////////////////////////////////
void PlayerMoving::processPerCollisionType(Collision * collision)
{
	if (collision->getType() == Collision::BOX)
		hitToCollisionBox((CollisionBox*)collision);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: Player::hitToCollisionBox
//�Ԃ�l	: 
//����		: �ǂɓ����������̏���
//////////////////////////////////////////////////////////////////////////////
void PlayerMoving::hitToCollisionBox(CollisionBox * box)
{
	Dvec3	clossPos;
	Dvec3	axis;
	if (box->hitByRay(&clossPos, &axis, mPlayer->getPos(), mPlayer->getPos() + mMoveVec * 5.f))
		mMoveVec = box->faceScrachVec(mMoveVec, axis);
}
