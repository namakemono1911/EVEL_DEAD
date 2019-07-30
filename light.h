/*****************************************************************************
right.h
Aythor	: 上野　匠
Data	: 2017_04_26
=============================================================================
Updata

*****************************************************************************/
#ifndef LIGHT_H
#define LIGHT_H
//////////////////////////////////////////////////////////////////////////////
//定数定義
//////////////////////////////////////////////////////////////////////////////
#define MAX_LIGHT	(5)		//ライトの総数

//////////////////////////////////////////////////////////////////////////////
//クラス宣言
//////////////////////////////////////////////////////////////////////////////
class Light
{
public:
	Light() {};
	~Light() {}
	static Light	*setLight	( D3DXVECTOR3 pos, D3DXVECTOR3 vecLight, D3DXCOLOR ambient, D3DXCOLOR diffuse );
	static void		releaseAll	(void);
	void	setPos	( D3DXVECTOR3 pos );

private:
	void	init	(D3DXVECTOR3 pos, D3DXVECTOR3 vecLight, D3DXCOLOR ambient, D3DXCOLOR diffuse, int num );

	static Light		*obj[MAX_LIGHT];	//生成ポインタ
	D3DLIGHT9			mLight;	//ライトの設定
	unsigned int		mId;	//自分のライト番号
	static unsigned int	mNum;	//ライトの総数
};

#endif