/*****************************************************************************
scene3D.h
Aythor	: 上野　匠
Data	: 2017_04_20
=============================================================================
Updata

*****************************************************************************/
#ifndef SCENE3D_H
#define SCENE3D_H

#include "scene.h"

//////////////////////////////////////////////////////////////////////////////
//クラス定義
//////////////////////////////////////////////////////////////////////////////
class Scene3DState;

class Scene3D : public Scene
{
public:
	Scene3D(UINT priolity = PRIME_FORTH):Scene(priolity) {};
	~Scene3D() {};
	HRESULT	init	( void );
	void	uninit	( void );
	void	update	( void );
	void	draw	( void );
	
	static Scene3D*	create(Dvec3 pos, Dvec3 rot, Dvec3 size, LPDIRECT3DTEXTURE9 texture, Dvec2 texPos = Dvec2(0, 0),
		Dvec2 texSize = Dvec2(1, 1), Dcolor color = Dcolor(1, 1, 1, 1));
	static Scene3D*	create(Dvec3 topLeft, Dvec3 topRight, Dvec3 bottomLeft, Dvec3 bottomRight, Dvec3 pos, Dvec3 rot, Dvec3 size,
		LPDIRECT3DTEXTURE9 texture, Dvec2 texPos = Dvec2(0, 0),Dvec2 texSize = Dvec2(1, 1), Dcolor color = Dcolor(1, 1, 1, 1));

	auto	getTexturePos() { return mTexPos; }
	auto	getTextureSize() { return mTexSize; }

	void	setTexturePos(Dvec2 pos) { mTexPos = pos; }
	void	setTextureSize(Dvec2 size) { mTexSize = size; }
	void	setTexture(LPDIRECT3DTEXTURE9 texture) { mTex = texture; }
	void	setTextureInfo(Dvec2 texPos, Dvec2 texSize) { mTexPos = texPos; mTexSize = texSize; }
	void	setColor(Dcolor color) { mColor = color; }
	void	setRect(Dvec3 size);
	void	setTextureAnimation(int numVertical, int numHorizonal, int interval);
	void	setBillboard();

protected:
	list<Scene3DState*>		mStateList;				//ステートリスト

private:
	void	setVertexBuffer();

	LPDIRECT3DVERTEXBUFFER9	mVtx;					//頂点バッファ
	LPDIRECT3DTEXTURE9		mTex;					//テクスチャバッファ
	Dvec3					mRectPos[NUM_VERTEX];
	D3DXVECTOR2				mTexPos;				//テクスチャ座標
	D3DXVECTOR2				mTexSize;				//テクスチャサイズ
	Dcolor					mColor;					//頂点色
	float					mLen;					//長さ
	float					mAngle;					//対角
	float					mRot;					//角度
};

#endif