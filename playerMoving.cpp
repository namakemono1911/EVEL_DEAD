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

	//当たり判定
	for (const auto& scene : Scene::getTypeList(Scene::OBJECT))
		collisionSearch(scene->getCollision());

	mPlayer->setPos(mMoveVec * mPlayer->moveSpeed() + mPlayer->getPos());

	mCamera->setPosEye(mPlayer->getPos());

	viewpointOperation();
}

void PlayerMoving::setMoveVec(void)
{
	//方向ベクトル
	vec2 mCameraAngle = mCamera->getAngle();
	mMoveVec = Dvec3(0.f, 0.f, 0.f);
	Dvec3 vec = Dvec3(
		sinf(mCameraAngle.x),
		0.f,
		cosf(mCameraAngle.x));

	//移動操作
	if (mPlayer->isPushedUp())			//前
		mMoveVec = vec * -1.f;

	if (mPlayer->isPushedDown())		//後ろ
		mMoveVec = vec;

	if (mPlayer->isPushedLeft())		//左
		mMoveVec += vec3::DcrossProduct(vec3(0.f, 1.f, 0.f), vec);

	else if (mPlayer->isPushedRight())	//右
		mMoveVec += vec3::DcrossProduct(vec, vec3(0.f, 1.f, 0.f));

	if (mMoveVec != Dvec3(0, 0, 0))
		D3DXVec3Normalize(&mMoveVec, &mMoveVec);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Player::collisionSearch
//返り値	: 
//説明		: コリジョン探索
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
//関数名	: Player::processPerCollisionType
//返り値	: 
//説明		: コリジョンタイプごとに処理
//////////////////////////////////////////////////////////////////////////////
void PlayerMoving::processPerCollisionType(Collision * collision)
{
	if (collision->getType() == Collision::BOX)
		hitToCollisionBox((CollisionBox*)collision);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: Player::hitToCollisionBox
//返り値	: 
//説明		: 壁に当たった時の処理
//////////////////////////////////////////////////////////////////////////////
void PlayerMoving::hitToCollisionBox(CollisionBox * box)
{
	Dvec3	clossPos;
	Dvec3	axis;
	if (box->hitByRay(&clossPos, &axis, mPlayer->getPos(), mPlayer->getPos() + mMoveVec * 5.f))
		mMoveVec = box->faceScrachVec(mMoveVec, axis);
}
