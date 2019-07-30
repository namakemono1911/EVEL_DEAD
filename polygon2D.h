/*****************************************************************************
2Dpolygon.h
Aythor	: 上野　匠
Data	: 2017_05_11
=============================================================================
Updata

*****************************************************************************/
#ifndef POLYGON_H
#define POLYGON_H
//////////////////////////////////////////////////////////////////////////////
// 前方宣言
//////////////////////////////////////////////////////////////////////////////
class Scene2D;

//////////////////////////////////////////////////////////////////////////////
// クラス宣言
//////////////////////////////////////////////////////////////////////////////
class Polygon2D : public Scene2D
{
public:
	Polygon2D(UINT priolity = PRIME_FIRST):Scene2D(priolity){}
	~Polygon2D(){}

	HRESULT	init	( D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR2 texPos, D3DXVECTOR2 texSize );
	void	uninit	( void );
	void	update	( void );
	void	draw	( void );

	static Polygon2D *create	( D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR2 texPos, D3DXVECTOR2 texSize );

private:

};

#endif
