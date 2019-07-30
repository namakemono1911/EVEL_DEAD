/*****************************************************************************
scene.cpp
Aythor	: 上野　匠
Data	: 2017_05_10
=============================================================================
Updata

*****************************************************************************/
#ifndef _SCENE_H_
#define _SCENE_H_
//////////////////////////////////////////////////////////////////////////////
// インクルード
//////////////////////////////////////////////////////////////////////////////
#include <list>
#include <vector>
#include <string>
#include <map>
#include "transform.h"
#include "collision.h"
#include "collisionBall.h"
#include "collisionBox.h"

//////////////////////////////////////////////////////////////////////////////
// 定数定義
//////////////////////////////////////////////////////////////////////////////
#define	MAX_OBJ			(100)
#define PRIORITY		(5)
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//2Dポリゴン設定
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_NORMAL | D3DFVF_TEX1)	//3Dポリゴン設定

//////////////////////////////////////////////////////////////////////////////
// 構造体定義
//////////////////////////////////////////////////////////////////////////////
//2Dポリゴン描写用構造体
typedef struct
{
	Dvec3		 pos;		//座標
	float		 rhw;
	D3DCOLOR	 color;		//頂点色
	D3DXVECTOR2	tex;		//テクスチャ座標
}VERTEX2D;

//3Dポリゴン描画用構造体
typedef struct
{
	Dvec3		pos;		//座標
	Dvec3		nor;		//法線
	D3DCOLOR	color;		//頂点座標
	D3DXVECTOR2	tex;		//テクスチャ座標
}VERTEX3D;

//////////////////////////////////////////////////////////////////////////////
// オブジェクトクラス
//////////////////////////////////////////////////////////////////////////////
class Collision;
class Transform;

class	Scene
{
public:
	typedef enum
	{
		OBJECT = 0,
		FIELD,
		NONE,			//無し
		PLAYER,
		ZOMBIE,
		OTHER,
		CAMERA,
		UI,
		OBJ_TYPE_MAX
	}OBJ_TYPE;		//オブジェクトタイプ

	typedef enum
	{
		PRIME_FIRST = 0,
		PRIME_SECOND,
		PRIME_THIRD,
		PRIME_FORTH,
		PRIME_FIFTH,
		PRIME_MAX,
	}PRIME;

	Scene(UINT priolity = PRIME_THIRD);
	virtual	~Scene();

	virtual	HRESULT	init(void){return S_OK;}
	virtual	void	uninit(void) = 0;
	virtual	void	update(void) = 0;
	virtual	void	draw(void) = 0;

	static	void	uninitAll(void);
	static	void	updateAll(void);
	static	void	drawAll(void);
	static	void	releaseAll(void);
	void	release(void);

	//ゲッター
	static auto		getSceneList(int prime) { return mSceneList[prime]; }
	static list<Scene*>		getTypeList(OBJ_TYPE);
	OBJ_TYPE		getObjType(void);
	Transform		getTransform(void) { return mTransform; }
	Transform		*getTransformAdd(void) { return &mTransform; }
	auto			getPos(void) { return mTransform.pos; }
	auto			getPosAddr(void) { return &mTransform.pos; }
	auto			getRot(void) { return mTransform.rot; }
	auto			getRotAddr(void) { return &mTransform.rot; }
	auto			getSize(void){return mTransform.size;}
	auto			getSizeAddr(void) { return &mTransform.size; }
	const auto		getParent(void) { return mParent; }
	auto			getChildernList(void) { return &mChildren; }
	auto			getMatrix(void) { return mMatrix; }
	auto			getMyName(void) { return mMyName; }
	auto			getCollision(void) { return mCollision; }

	//セッター
	void			setObjType(OBJ_TYPE type);
	void			setTransform(Transform transform){mTransform = transform;}
	void			setPos(Dvec3 pos){mTransform.pos = pos;}
	void			setRot(Dvec3 rot){mTransform.rot = rot;}
	void			setSize(Dvec3 size){mTransform.size = size;}
	void			setChild(Scene* child);
	void			setCollision(Collision* col);
	void			setParent(Scene* pearent);
	void			setMatrix(DMtx matrix) { mMatrix = matrix; }
	void			matrixMulti(DMtx matrix) { mMatrix *= matrix; }

protected:
	//変数宣言
	Dmtx					mMatrix;				//行列
	Transform				mTransform;				//座標、回転、拡縮
	Scene*					mParent;				//親オブジェクト
	list<Scene*>			mChildren;				//子オブジェクト
	string					mMyName;				//オブジェクトの名前
	CollisionManager*		mCollision;				//コリジョンマネージャ

#ifdef _DEBUG
	string					mProcessTimeText;	//処理時間
	int						mNumFrame = 15;			//フレーム数
#endif // _DEBUG

private:
	//プロトタイプ宣言
	static void			RunUninitOneByOne(const list<Scene*> scene);
	static void			RunUpdateOneByOne(const list<Scene*> scene);
	static void			RunDrawOneByOne(const list<Scene*> scene);
	static void			RunEraseOneByOne(list<Scene*> &scene);
	static void			RunDrawCollision(const list<Scene*> scene);

	//変数宣言
	static	list<Scene*>	mSceneList[PRIME_MAX];	//各オブジェクトを保存

	int						mID;				//インデックスナンバー
	OBJ_TYPE				mType;				//オブジェクトタイプ
	bool					mDelete;			//削除フラグ

};

#endif
