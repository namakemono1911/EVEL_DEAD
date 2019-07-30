/*****************************************************************************
collisionBall.cpp
Aythor	: 上野　匠
Data	: 2017_07_13
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include <list>
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "collisionBall.h"
#include "load.h"
#include "vec.h"
#include "sceneModel.h"

//////////////////////////////////////////////////////////////////////////////
//静的メンバ変数初期化
//////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
LPDIRECT3DTEXTURE9	CollisionBall::mTexBuf[2] = {NULL};
#endif // _DEBUG

//////////////////////////////////////////////////////////////////////////////
//関数名	: CollisionBall::init()
//返り値	: 
//説明		: 初期化処理
//////////////////////////////////////////////////////////////////////////////
HRESULT CollisionBall::init(void)
{
#ifdef _DEBUG
if (FAILED(
		D3DXCreateSphere(
			Renderer::getDevice(),			// 描画先のデバイス
			mLen,							// 半径。0.0fでも実はOK。マイナスはNG
			32,								// スライスの数。増やすときれいな球になるはず
			18,								// スタック数。増やすときれいな球になるはず
			&mMesh,							// 出力するメッシュ
			NULL)))							// あまり使わないらしいんでNULLにしといた
		return E_FAIL;

	mMat.Diffuse = DEFAULT_COLOR;
	mMat.Ambient = DEFAULT_COLOR;
	mMat.Specular = Dcolor(0, 0, 0, 0);
	mMat.Emissive = Dcolor(0, 0, 0, 0);
	mMat.Power = 0.f;
#endif // _DEBUG

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: CollisionBall::uninit()
//返り値	: 
//説明		: 終了
//////////////////////////////////////////////////////////////////////////////
void CollisionBall::uninit(void)
{
#ifdef _DEBUG
if (mMesh != NULL)
	{
		mMesh->Release();
		mMesh = NULL;
	}
#endif // _DEBUG
	
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: CollisionBall::update()
//返り値	: 
//説明		: 更新
//////////////////////////////////////////////////////////////////////////////
void CollisionBall::update(void)
{
	auto world = mPearents->getMatrix();
	auto parentPos = Dvec3(world._41, world._42, world._43);
	auto axisX = Dvec3(world._11, world._12, world._13) * mRelativePos.x;
	auto axisY = Dvec3(world._21, world._22, world._23) * mRelativePos.y;
	auto axisZ = Dvec3(world._31, world._32, world._33) * mRelativePos.z;
	mPos = axisX + axisY + axisZ + parentPos;

#ifdef _DEBUG
D3DXCreateSphere(
		Renderer::getDevice(),			// 描画先のデバイス
		mLen,							// 半径。0.0fでも実はOK。マイナスはNG
		32,								// スライスの数。増やすときれいな球になるはず
		18,								// スタック数。増やすときれいな球になるはず
		&mMesh,							// 出力するメッシュ
		NULL);							// あまり使わないらしいんでNULLにしといた
#endif // _DEBUG
}

#ifdef _DEBUG
//////////////////////////////////////////////////////////////////////////////
//関数名	: CollisionBall::draw()
//返り値	: 
//説明		: 描画
//////////////////////////////////////////////////////////////////////////////
void CollisionBall::draw(void)
{
	LPDIRECT3DDEVICE9 device = Renderer::getDevice();

	//ライトの影響off
	device->SetRenderState(D3DRS_LIGHTING, false);

	//行列設定
	setMtx();

	//テクスチャ設定
	device->SetMaterial(&mMat);

	mMesh->DrawSubset(0);

	//ライトの影響on
	device->SetRenderState(D3DRS_LIGHTING, true);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: CollisionBall::loadTex()
//返り値	: 
//説明		: 描画
//////////////////////////////////////////////////////////////////////////////
void CollisionBall::loadTex(void)
{
	//テクスチャの読み込み
	char *texName[2] = {
		"data/texture/ball000.png",
		"data/texture/ball001.png"
	};

	for (int i = 0; i < 2; i++)
	{
		if (FAILED(D3DXCreateTextureFromFile(Renderer::getDevice(), texName[i], &mTexBuf[i])))
		{
			char message[255];
			sprintf(message, "%sが読み込めませんでした", texName[i]);

			MessageBox(NULL, message, "テクスチャ読み込みエラー", MB_OK);
		}
	}
}
#endif // _DEBUG

void CollisionBall::assignmentTarget(FILE * fp)
{
	string order = "\0";
	while ((order = Load::findWord(fp)) != "}")
	{
		if (order == "pos")
			Load::operatorSelectFloat3(fp, mRelativePos);

		if (order == "len")
			Load::operatorSelectFloat(fp, &mLen);
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: CollisionBall::create()
//返り値	: 
//説明		: 描画
//////////////////////////////////////////////////////////////////////////////
CollisionBall * CollisionBall::create(Scene* pearent, Dvec3 pos, float len)
{
	CollisionBall *ball;

	ball = new CollisionBall;

	ball->mPearents = pearent;
	ball->mLen = len;
	ball->mRelativePos = pos;
	ball->mType = BALL;
	ball->init();

	return ball;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: CollisionBall::hitByPoint()
//返り値	: 
//説明		: 球と点の判定
//////////////////////////////////////////////////////////////////////////////
bool CollisionBall::hitByPoint(const Dvec3& pos)
{
	if (mLen <= (float)vec3::lenVector(pos - mPos))
		return true;
	return false;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: CollisionBall::hitByRay()
//返り値	: 
//説明		: 球と線の判定
//////////////////////////////////////////////////////////////////////////////
bool CollisionBall::hitByRay(Dvec3 *outCrossPos, Dvec3 *outAxis, Dvec3 pos, Dvec3 ray)
{
	Dvec3 normalRay;
	D3DXVec3Normalize(&normalRay, &Dvec3(ray - pos));
	auto dot = vec3::innerProduct(normalRay, mPos - pos);
	
	if (dot < 0)
	{
		if (D3DXVec3Length(&Dvec3(mPos - pos)) < mLen)
		{
			if (outCrossPos != NULL)
				*outCrossPos = pos + ray;

			if (outAxis != NULL)
				D3DXVec3Normalize(outAxis, &Dvec3(mPos - pos));

			return true;
		}
	}
	
	if (dot > D3DXVec3Length(&Dvec3(ray - pos)))
	{
		if (D3DXVec3Length(&Dvec3(ray - pos)) < mLen)
		{
			if (outCrossPos != NULL)
				*outCrossPos = pos;

			if (outAxis != NULL)
				D3DXVec3Normalize(outAxis, &Dvec3(mPos - pos));

			return true;
		}
	}
	else
	{
		auto cross = vec3::DcrossProduct(normalRay, mPos - pos);

		if (D3DXVec3Length(&cross) < mLen)
		{
			if (outCrossPos != NULL)
			{
				if (outCrossPos != NULL)
					*outCrossPos = cross;
				if (outAxis != NULL)
					D3DXVec3Normalize(outAxis, &Dvec3(cross - mPos));
			}
			SceneModel::create("box.x", cross * mLen + mPos);

			return true;
		}
	}

	if (outCrossPos != NULL)
		*outCrossPos = Dvec3(0, 0, 0);
	if (outAxis != NULL)
		*outAxis = Dvec3(0, 0, 0);

	return false;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: CollisionBall::create()
//返り値	: 
//説明		: 描画
//////////////////////////////////////////////////////////////////////////////
void CollisionBall::setMtx(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9	device;		//デバイス情報
	D3DXMATRIX	world;		//ワールド行列
	D3DXMATRIX	move;		//平行移動行列

	//デバイス取得
	device = Renderer::getDevice();

	//行列初期化
	D3DXMatrixIdentity(&world);

	//平行移動
	D3DXMatrixTranslation(&move,
		mPos.x,
		mPos.y,
		mPos.z);

	//行列合成
	world *= move;		//平行移動

	device->SetTransform(D3DTS_WORLD, &world);		//行列をデバイスに設定
}
