/*****************************************************************************
collisionBox.cpp
Aythor	: 上野　匠
Data	: 2017_07_13
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "manager.h"
#include "collisionBox.h"
#include "load.h"

//////////////////////////////////////////////////////////////////////////////
//定数定義
//////////////////////////////////////////////////////////////////////////////
#define NUM_VTX_BOX		(20)		//箱を作るのに必要な頂点数

//////////////////////////////////////////////////////////////////////////////
//関数名	: CollisionBox::init()
//返り値	: 
//説明		: 生成
//////////////////////////////////////////////////////////////////////////////
HRESULT CollisionBox::init(void)
{
#ifdef _DEBUG
	//頂点バッファの設定
	if (FAILED(Manager::getDevice()->CreateVertexBuffer(
		sizeof(VERTEX3D) * NUM_VTX_BOX,	//頂点バッファサイズ
		D3DUSAGE_WRITEONLY,				//頂点バッファの使用方法
		FVF_VERTEX_3D,					//描画フォーマット
		D3DPOOL_MANAGED,				//メモリ管理方法
		&mVtx,							//頂点バッファ管理インターフェイス
		NULL)))
	{
		return E_FAIL;
	}

	mColor = DEFAULT_COLOR;

	setVtx();
#endif // _DEBUG

	return E_NOTIMPL;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: CollisionBox::uninit()
//返り値	: 
//説明		: 終了
//////////////////////////////////////////////////////////////////////////////
void CollisionBox::uninit(void)
{
#ifdef _DEBUG
	if (mVtx != NULL)
	{
		mVtx->Release();
		mVtx = NULL;
	}
#endif // _DEBUG
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: CollisionBox::update()
//返り値	: 
//説明		: 更新
//////////////////////////////////////////////////////////////////////////////
void CollisionBox::update(void)
{
	auto	world = mPearents->getMatrix();

	mAxis.x = vec3::normalize(vec3(world._11, world._12, world._13));
	mAxis.y = vec3::normalize(vec3(world._21, world._22, world._23));
	mAxis.z = vec3::normalize(vec3(world._31, world._32, world._33));

	//平行移動
	mRelativePos = Dvec3(world._41, world._42, world._43);
	mRelativePos += vec3::conv(mAxis.x * mPos.x);
	mRelativePos += vec3::conv(mAxis.y * mPos.y);
	mRelativePos += vec3::conv(mAxis.z * mPos.z);

	mAxisLen = vec3::conv(vec3(mSize) * mPearents->getSize() * 0.5f);

#ifdef _DEBUG
	setVtx();
#endif // _DEBUG
}

#ifdef _DEBUG
//////////////////////////////////////////////////////////////////////////////
//関数名	: CollisionBox::draw()
//返り値	: 
//説明		: 生成
//////////////////////////////////////////////////////////////////////////////
void CollisionBox::draw(void)
{
	LPDIRECT3DDEVICE9	device = Manager::getDevice();

	//ストリーム作成
	device->SetStreamSource(0, mVtx, 0, sizeof(VERTEX3D));

	//ライトの影響off
	device->SetRenderState(D3DRS_LIGHTING, false);

	//頂点フォーマットの設定
	device->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	device->SetTexture(0, NULL);

	//行列設定
	Dmtx matrix;
	D3DXMatrixIdentity(&matrix);
	device->SetTransform(D3DTS_WORLD, &matrix);

	//ポリゴンの描画
	device->DrawPrimitive
	(
		D3DPT_TRIANGLESTRIP,	//ポリゴンの種類
		0,						//オフセット(頂点数)
		NUM_POLYGON * 6 + 6		//ポリゴンの数
	);

	//ライトの影響on
	device->SetRenderState(D3DRS_LIGHTING, true);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: CollisionBox::setVtx()
//返り値	: 
//説明		: 生成
//////////////////////////////////////////////////////////////////////////////
void CollisionBox::setVtx(void)
{
	//変数宣言
	VERTEX3D	*vtx;
	auto		world = mPearents->getMatrix();
	Dvec3		size = Dvec3(world._11, world._22, world._33);

	Dvec3		lineX = vec3::conv(mAxis.x * mAxisLen.x);
	Dvec3		lineY = vec3::conv(mAxis.y * mAxisLen.y);
	Dvec3		lineZ = vec3::conv(mAxis.z * mAxisLen.z);

	mVtx->Lock(0, 0, (void**)&vtx, 0);

	//前面
	vtx[0].pos = -lineX + lineY - lineZ + mRelativePos;
	vtx[1].pos = lineX + lineY - lineZ + mRelativePos;
	vtx[2].pos = -lineX - lineY - lineZ + mRelativePos;
	vtx[3].pos = lineX - lineY - lineZ + mRelativePos;

	//底面
	vtx[4].pos = -lineX - lineY + lineZ + mRelativePos;
	vtx[5].pos = lineX - lineY + lineZ + mRelativePos;

	//背面
	vtx[6].pos = -lineX + lineY + lineZ + mRelativePos;
	vtx[7].pos = lineX + lineY + lineZ + mRelativePos;

	//上面
	vtx[8].pos = -lineX + lineY - lineZ + mRelativePos;
	vtx[9].pos = lineX + lineY - lineZ + mRelativePos;

	//右側面
	vtx[10].pos = lineX + lineY - lineZ + mRelativePos;
	vtx[11].pos = lineX + lineY + lineZ + mRelativePos;
	vtx[12].pos = lineX - lineY - lineZ + mRelativePos;
	vtx[13].pos = lineX - lineY + lineZ + mRelativePos;

	//縮退ポリゴン
	vtx[14].pos = lineX - lineY + lineZ + mRelativePos;
	vtx[15].pos = -lineX - lineY + lineZ + mRelativePos;

	//左側面
	vtx[16].pos = -lineX + lineY + lineZ + mRelativePos;
	vtx[17].pos = -lineX + lineY - lineZ + mRelativePos;
	vtx[18].pos = -lineX - lineY + lineZ + mRelativePos;
	vtx[19].pos = -lineX - lineY - lineZ + mRelativePos;

	//頂点色
	for (int i = 0; i < NUM_VTX_BOX; i++)
	{
		vtx[i].color = mColor;
	}

	mVtx->Unlock();
}
#endif // _DEBUG

//////////////////////////////////////////////////////////////////////////////
//関数名	: CollisionBox::calcWorldMtx()
//返り値	: 
//説明		: ワールド行列計算
//////////////////////////////////////////////////////////////////////////////
DMtx CollisionBox::calcWorldMtx(void)
{
	return mPearents->getMatrix();
}

void CollisionBox::assignmentTarget(FILE * fp)
{
	string order;
	while ((order = Load::findWord(fp)) != "}")
	{
		if (order == "pos")
			Load::operatorSelectFloat3(fp, (float*)&mPos);

		if (order == "rot")
			Load::operatorSelectFloat3(fp, (float*)&mRot);

		if (order == "size")
			Load::operatorSelectFloat3(fp, (float*)&mSize);
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: CollisionBox::create()
//返り値	: 
//説明		: 生成
//////////////////////////////////////////////////////////////////////////////
CollisionBox * CollisionBox::create(Scene *pearents, Dvec3 pos, Dvec3 size)
{
	CollisionBox	*box = new CollisionBox;

	box->mPearents = pearents;
	box->mPos = pos;
	box->mSize = size;
	box->mRot = Dvec3(0,0,0);
	box->mType = BOX;
	box->init();

	return box;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: CollisionBox::hitByRay()
//返り値	: 
//説明		: 線分がコリジョンボックスに当たっているか
//////////////////////////////////////////////////////////////////////////////
bool CollisionBox::hitByRay(Dvec3 *outCrossPos, Dvec3 *outAxis, Dvec3 pos, Dvec3 ray)
{
	//まずは球の判定で軽量化
	auto len = D3DXVec3Length(&Dvec3(ray - pos)) + D3DXVec3Length(&mAxisLen);
	if (len < D3DXVec3Length(&Dvec3(mRelativePos - pos)))
		return false;

	Dvec3	crossPos;
	Dvec3	axis;
	double	dotPos;
	double	dotRay;
	string	axisList[] = { "x", "y", "z", "-x", "-y", "-z" };

	for (UINT i = 0; i < sizeof(axisList) / sizeof(string); i++)
	{
		//内積取得
		axis = getDotPosAndRay(axisList[i], &dotPos, &dotRay, pos, ray);

		//交点計算
		if (rayIsIntersectioing(dotPos, dotRay))
			crossPos = getCrossPos(pos, ray, dotPos, dotRay);
		else
			continue;

		//判定
		if (hitFaceAndPoint(axisList[i], crossPos))
		{
#ifdef _DEBUG
			mColor = HIT_COLOR;
#endif // DEBUG

			if (outCrossPos != NULL)
				*outCrossPos = crossPos;

			if (outAxis != NULL)
				*outAxis = axis;

			return true;
		}
	}

#ifdef _DEBUG
	mColor = DEFAULT_COLOR;
#endif // DEBUG

	if (outCrossPos != NULL)
		*outCrossPos = Dvec3(0, 0, 0);

	if (outAxis != NULL)
		*outAxis = Dvec3(0, 0, 0);

	return false;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: CollisionBox::hitByPoint()
//返り値	: 
//説明		: 点がコリジョンボックスに当たっているか
//////////////////////////////////////////////////////////////////////////////
bool CollisionBox::hitByPoint(Dvec3 point)
{
	vec3	axisX = mAxis.x * mAxisLen.x;
	vec3	axisY = mAxis.y * mAxisLen.y;
	vec3	axisZ = mAxis.z * mAxisLen.z;
	vector<bool>	isHit(6, false);

	if (vec3::innerProduct(axisX + mRelativePos + mAxis.x, point, axisX + mRelativePos) <= 0)
		isHit[0] = true;

	if (vec3::innerProduct(axisY + mRelativePos + mAxis.y, point, axisY + mRelativePos) <= 0)
		isHit[1] = true;

	if (vec3::innerProduct(axisZ + mRelativePos + mAxis.z, point, axisZ + mRelativePos) <= 0)
		isHit[2] = true;

	if (vec3::innerProduct(axisX * -1 + mRelativePos - mAxis.x, point, axisX * -1 + mRelativePos) <= 0)
		isHit[3] = true;

	if (vec3::innerProduct(axisY * -1 + mRelativePos - mAxis.y, point, axisY * -1 + mRelativePos) <= 0)
		isHit[4] = true;

	if (vec3::innerProduct(axisZ * -1 + mRelativePos - mAxis.z, point, axisZ * -1 + mRelativePos) <= 0)
		isHit[5] = true;

#pragma omp parallel for
	for (UINT i = 0; i < isHit.size(); i++)
	{
		if (isHit[i] == false)
		{
#ifdef _DEBUG
			mColor = DEFAULT_COLOR;
#endif // DEBUG

			return false;
		}
	}

#ifdef _DEBUG
	mColor = HIT_COLOR;
#endif // DEBUG

	return true;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: CollisionBox::getCrossPos()
//返り値	: 
//説明		: 交差点の座標取得
//////////////////////////////////////////////////////////////////////////////
Dvec3 CollisionBox::getCrossPos(Dvec3 pos, Dvec3 ray, double dotPos, double dotRay)
{
	vec3	unit = ray - pos;
	double	ratio = abs(dotPos) / (abs(dotPos) + abs(dotRay));
	return Dvec3(pos.x + (unit.x * (float)ratio),
		pos.y + (unit.y * (float)ratio),
		pos.z + (unit.z * (float)ratio));
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: CollisionBox::getDotPosAndRay()
//返り値	: 
//説明		: ポジションと線の内積計算
//////////////////////////////////////////////////////////////////////////////
Dvec3 CollisionBox::getDotPosAndRay(string axis, double * dotPos, double * dotRay, vec3 pos, vec3 ray)
{
	vec3	axisX = mAxis.x * mAxisLen.x;
	vec3	axisY = mAxis.y * mAxisLen.y;
	vec3	axisZ = mAxis.z * mAxisLen.z;

	if (axis == "x" || axis == "X")
	{
		*dotPos = vec3::innerProduct(mAxis.x, pos - (axisX + mRelativePos));
		*dotRay = vec3::innerProduct(mAxis.x, ray - (axisX + mRelativePos));
		return vec3::conv(mAxis.x);
	}
	if (axis == "y" || axis == "Y")
	{
		*dotPos = vec3::innerProduct(mAxis.y, pos - (axisY + mRelativePos));
		*dotRay = vec3::innerProduct(mAxis.y, ray - (axisY + mRelativePos));
		return vec3::conv(mAxis.y);
	}
	if (axis == "z" || axis == "Z")
	{
		*dotPos = vec3::innerProduct(mAxis.z, pos - (axisZ + mRelativePos));
		*dotRay = vec3::innerProduct(mAxis.z, ray - (axisZ + mRelativePos));
		return vec3::conv(mAxis.z);
	}
	if (axis == "-x" || axis == "-X")
	{
		*dotPos = vec3::innerProduct(mAxis.x * -1, pos - (axisX * -1 + mRelativePos));
		*dotRay = vec3::innerProduct(mAxis.x * -1, ray - (axisX * -1 + mRelativePos));
		return vec3::conv(mAxis.x * -1);
	}
	if (axis == "-y" || axis == "-Y")
	{
		*dotPos = vec3::innerProduct(mAxis.y * -1, pos - (axisY * -1 + mRelativePos));
		*dotRay = vec3::innerProduct(mAxis.y * -1, ray - (axisY * -1 + mRelativePos));
		return vec3::conv(mAxis.y * -1);
	}
	if (axis == "-z" || axis == "-Z")
	{
		*dotPos = vec3::innerProduct(mAxis.z * -1, pos - (axisZ * -1 + mRelativePos));
		*dotRay = vec3::innerProduct(mAxis.z * -1, ray - (axisZ * -1 + mRelativePos));
		return vec3::conv(mAxis.z * -1);
	}

	return Dvec3(0.f, 0.f, 0.f);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: CollisionBox::rayIsIntersectioing()
//返り値	: 
//説明		: 線が交差しているかどうか
//////////////////////////////////////////////////////////////////////////////
bool CollisionBox::rayIsIntersectioing(double dotPos, double dotRay)
{
	if ((dotPos > 0 && dotRay <= 0))
		return true;

	return false;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: CollisionBox::hitFaceAndPoint()
//返り値	: 
//説明		: 面と点の判定
//////////////////////////////////////////////////////////////////////////////
bool CollisionBox::hitFaceAndPoint(string facePos, vec3 pos)
{
	vector<vec3>	rectPos = getRectPos(facePos);

	//中身が空なら終了
	if (rectPos.empty())
		return false;

	//各頂点との外積を計算
	vec3	c1 = vec3::crossProduct(pos, rectPos[1], rectPos[0]);
	vec3	c2 = vec3::crossProduct(pos, rectPos[2], rectPos[1]);
	vec3	c3 = vec3::crossProduct(pos, rectPos[3], rectPos[2]);
	vec3	c4 = vec3::crossProduct(pos, rectPos[0], rectPos[3]);

	//各頂点の内積を計算
	double	dot1 = vec3::innerProduct(c1, c2);
	double	dot2 = vec3::innerProduct(c1, c3);
	double	dot3 = vec3::innerProduct(c1, c4);

	//全ての内積が0以上なら平面の中にposがある
	if (dot1 > 0 && dot2 > 0 && dot3 > 0)
		return true;

	return false;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: CollisionBox::hitFaceAndPoint()
//返り値	: 
//説明		: 軸から面の4頂点取得
//////////////////////////////////////////////////////////////////////////////
vector<vec3> CollisionBox::getRectPos(string facePos)
{
	Dvec3		lineX = vec3::conv(mAxis.x * mAxisLen.x);
	Dvec3		lineY = vec3::conv(mAxis.y * mAxisLen.y);
	Dvec3		lineZ = vec3::conv(mAxis.z * mAxisLen.z);
	vector<vec3>	vtx(4);

	if (facePos == "x" || facePos == "X")
	{
		vtx[0] = lineX + lineY + lineZ + mRelativePos;
		vtx[1] = lineX + lineY - lineZ + mRelativePos;
		vtx[2] = lineX - lineY - lineZ + mRelativePos;
		vtx[3] = lineX - lineY + lineZ + mRelativePos;

		return vtx;
	}

	if (facePos == "y" || facePos == "Y")
	{
		vtx[0] = lineX + lineY + lineZ + mRelativePos;
		vtx[1] = lineX * -1 + lineY + lineZ + mRelativePos;
		vtx[2] = lineX * -1 + lineY - lineZ + mRelativePos;
		vtx[3] = lineX + lineY - lineZ + mRelativePos;

		return vtx;
	}

	if (facePos == "z" || facePos == "Z")
	{
		vtx[0] = lineX * -1 + lineY + lineZ + mRelativePos;
		vtx[1] = lineX + lineY + lineZ + mRelativePos;
		vtx[2] = lineX - lineY + lineZ + mRelativePos;
		vtx[3] = lineX * -1 - lineY + lineZ + mRelativePos;

		return vtx;
	}

	if (facePos == "-x" || facePos == "-X")
	{
		vtx[0] = lineX * -1 + lineY - lineZ + mRelativePos;
		vtx[1] = lineX * -1 + lineY + lineZ + mRelativePos;
		vtx[2] = lineX * -1 - lineY + lineZ + mRelativePos;
		vtx[3] = lineX * -1 - lineY - lineZ + mRelativePos;

		return vtx;
	}

	if (facePos == "-y" || facePos == "-Y")
	{
		vtx[0] = lineX - lineY + lineZ + mRelativePos;
		vtx[1] = lineX * -1 - lineY + lineZ + mRelativePos;
		vtx[2] = lineX * -1 - lineY - lineZ + mRelativePos;
		vtx[3] = lineX - lineY - lineZ + mRelativePos;

		return vtx;
	}

	if (facePos == "-z" || facePos == "-Z")
	{
		vtx[0] = lineX + lineY - lineZ + mRelativePos;
		vtx[1] = lineX * -1 + lineY - lineZ + mRelativePos;
		vtx[2] = lineX * -1 - lineY - lineZ + mRelativePos;
		vtx[3] = lineX - lineY - lineZ + mRelativePos;

		return vtx;
	}

	return vtx;
}