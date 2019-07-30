/*****************************************************************************
メッシュドーム描画
Aythor	: 上野　匠
Data	: 2016_12_23
=============================================================================
Updata

*****************************************************************************/
#ifndef	MESH_DOME_H
#define	MESH_DOME_H
//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include "mesh.h"

//////////////////////////////////////////////////////////////////////////////
//定数定義
//////////////////////////////////////////////////////////////////////////////
#define	MAX_DOME	(5)		//フィールドの最大数

//////////////////////////////////////////////////////////////////////////////
//構造体定義
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//クラス定義
//////////////////////////////////////////////////////////////////////////////
class Sky : public Mesh
{
public:
	//列挙型定義
	typedef	enum
	{
		SKY_TEX_001 = 0,
		SKY_TEX_MAX,			//テクスチャ総数
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
	
	//セッター
	void	setVal(D3DXVECTOR3 pos, D3DXVECTOR2 numTyle, D3DXCOLOR color, D3DXVECTOR3 rot, float len, SKY_TEX tex);

	static Sky		*create (D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR2 numTyle, D3DXCOLOR color, float len, SKY_TEX tex);
	static HRESULT	loadTex	();

private:
	//プロトタイプ宣言
	HRESULT	makeVtx(D3DXVECTOR2 numTyle);
	HRESULT	makeIdx(void);

	//変数宣言
	static LPDIRECT3DTEXTURE9	mTexBuf[SKY_TEX_MAX];		//テクスチャバッファ
	const static char	*mTexName[SKY_TEX_MAX];	//テクスチャ名
	D3DXVECTOR3	mPos;		//表示座標
	D3DXVECTOR2	mNumTyle;	//縦横何タイルか
	D3DXCOLOR	mColor;		//頂点色
	D3DXVECTOR3	mRot;		//ポリゴンの回転量
	float		mLen;		//半径
	SKY_TEX		mTex;		//テクスチャの種類
};

#endif