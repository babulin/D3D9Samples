#pragma once
#include "Base.h"

class Texture {
public:
	float mWidth;
	float mHeight;
private:
	LPDIRECT3DDEVICE9 m_d3dDevice;				//D3D…Ë±∏

	LPDIRECT3DTEXTURE9 mTextureBG1;				//Œ∆¿Ì - ±≥æ∞1
	LPDIRECT3DTEXTURE9 mTextureBG2;				//Œ∆¿Ì - ±≥æ∞2
	LPDIRECT3DTEXTURE9 mTextureBG3;				//Œ∆¿Ì - ±≥æ∞3
	LPDIRECT3DTEXTURE9 mTexture1x1;				//Œ∆¿Ì - 1x1
	LPDIRECT3DTEXTURE9 mTexture2x2;				//Œ∆¿Ì - 2x2
public:
	Texture(LPDIRECT3DDEVICE9 d3dDevice, int width, int height);
	void Init();
	HRESULT CreateTexture();
	HRESULT CreateTexture1x1();
	HRESULT CreateTexture2x2();
	void DrawPrimitiveUPUV1();
	void DrawIndexedPrimitiveUPUV2();
	void DrawIndexedPrimitiveUPUV2x2();
};