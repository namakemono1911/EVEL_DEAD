/*****************************************************************************
meshField.h
Aythor	: 上野　匠
Data	: 2017_04_27
=============================================================================
Updata

*****************************************************************************/
#ifndef MESHFIELD_H
#define MESHFIELD_H
//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include <string>
#include <list>
#include <vector>
#include <map>
#include "scene.h"
#include "mesh.h"

//////////////////////////////////////////////////////////////////////////////
//定数定義
//////////////////////////////////////////////////////////////////////////////
#define	MAX_FIELD	(256)		//フィールドの最大数

//////////////////////////////////////////////////////////////////////////////
//前方宣言
//////////////////////////////////////////////////////////////////////////////
class Mesh;

//////////////////////////////////////////////////////////////////////////////
//クラス定義
//////////////////////////////////////////////////////////////////////////////
class Tyle
{
public:
	Tyle() { x = 0, y = 0; }
	Tyle(int refx, int refy) { x = refx; y = refy; }
	~Tyle() {}

	int		x;
	int		y;
};

class MeshField : public Mesh
{
public:
	MeshField(UINT priolity = PRIME_THIRD);
	~MeshField() {};

	//プロトタイプ宣言
	HRESULT	init(void);
	void	uninit(void);
	void	update(void);
	void	draw(void);

	static void	release(MeshField *point);

	//ゲッター
	static float	getHeight(const Dvec3 pos);
	static auto		getTextureMap(void) { return mNameList; }
	static auto		getTextureNameList(void){return mTexNameList;}
	static auto		getTextureIdFormMap(string texName){return mNameList[texName];}
	auto			getNumTyle(void){return mNumTyle;}
	auto			getNumTyleAd(void) { return &mNumTyle; }
	auto			getColorAddr(void) { return &mColor; }
	auto			getTyleSize(void){return mTyleSize;}
	auto			getTyleSizeAddr(void){return &mTyleSize;}
	auto			getTextureId(void){return mNumTexture;}
	auto			getTextureIdAddr(void) { return &mNumTexture; }

	//セッター
	void	setVal(D3DXVECTOR2 size, Tyle numTyle, int textureID, Dcolor color);
	void	setTyleSize(Dvec2 size){mTyleSize = size;}
	void	setNumTyle(Tyle tyle){mNumTyle = tyle;}
	void	setTextureId(UINT num){mNumTexture = num;}
	void	setColor(Dcolor color){mColor = color;}

	static MeshField	*create(Dvec3 pos, D3DXVECTOR2 size, Tyle numTyle, Dvec3 rot, D3DXCOLOR color, D3DXVECTOR2 texMove, int textureID);
	static MeshField	*create(MeshField field);
	static void			loadTex();

private:
	//プロトタイプ宣言
	HRESULT	makeVtx(Tyle numTyle, D3DXCOLOR color);
	HRESULT	makeIdx(Tyle numTyle);

	//変数宣言
	static LPDIRECT3DTEXTURE9	*mTex;			//テクスチャバッファ
	static vector<string>		mTexNameList;	//テクスチャ名リスト
	static map<string, UINT>	mNameList;		//名前リスト
	static list<MeshField*>		mFieldList;		//フィールドリスト

	Dvec3				*mVtxPos;		//頂点の位置情報
	Dvec2				mTyleSize;		//1タイルの大きさ
	Tyle				mNumTyle;		//縦横何タイルか
	Tyle				mSaveNumTyle;	//前回のタイル数保存	
	Dcolor				mColor;			//頂点色
	int					mNumTexture;	//使われているテクスチャのナンバー		
	bool				mDelete;		//削除フラグ
	D3DMATERIAL9		mMat;			//マテリアル情報
};

#endif