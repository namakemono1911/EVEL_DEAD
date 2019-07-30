/*****************************************************************************
renderer.cpp
Aythor	: ���@��
Data	: 2017_05_10
=============================================================================
Updata

*****************************************************************************/
#ifndef RENDERER_H
#define RENDERER_H
//////////////////////////////////////////////////////////////////////////////
//�N���X��`
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

	static LPDIRECT3D9			mD3D;				//Direct3D�C���^�[�t�F�C�X
	static LPDIRECT3DDEVICE9	mD3DDevice;		//Direct3D�f�o�C�X�̃|�C���^

#ifdef _DEBUG
	LPD3DXFONT m_pFont;						// �t�H���g�ւ̃|�C���^
#endif
};

#endif
