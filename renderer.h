/*****************************************************************************
renderer.cpp
Aythor	: 上野　匠
Data	: 2017_05_10
=============================================================================
Updata

*****************************************************************************/
#ifndef RENDERER_H
#define RENDERER_H
//////////////////////////////////////////////////////////////////////////////
//クラス定義
//////////////////////////////////////////////////////////////////////////////
class Renderer
{
public:
	Renderer() {}
	~Renderer() {}
	HRESULT	init	( HWND hWnd, BOOL bWindow );
	void	uninit	( void );
	void	update	( void );
	void	draw	( void );

	static LPDIRECT3DDEVICE9	getDevice	( void ){ return mD3DDevice;}

private:
#ifdef _DEBUG
	void drawFPS(void);
#endif

	static LPDIRECT3D9			mD3D;				//Direct3Dインターフェイス
	static LPDIRECT3DDEVICE9	mD3DDevice;		//Direct3Dデバイスのポインタ

#ifdef _DEBUG
	LPD3DXFONT m_pFont;						// フォントへのポインタ
#endif
};

#endif
