#pragma once
#include "Base.h"

class Texture {
public:
	float mWidth;
	float mHeight;
protected:
	LPDIRECT3DDEVICE9 m_d3dDevice;				//D3D�豸

	LPDIRECT3DTEXTURE9 mTextureBG1;				//���� - ����1
	LPDIRECT3DTEXTURE9 mTextureBG2;				//���� - ����2
	LPDIRECT3DTEXTURE9 mTextureBG3;				//���� - ����3
	LPDIRECT3DTEXTURE9 mTexture1x1;				//���� - 1x1
	LPDIRECT3DTEXTURE9 mTexture2x2;				//���� - 2x2
public:
	Texture(LPDIRECT3DDEVICE9 d3dDevice, int width, int height);
	virtual void Init();
	HRESULT CreateTexture();
	HRESULT CreateTexture1x1();
	HRESULT CreateTexture2x2();
	virtual void DrawPrimitiveUPUV1();
	virtual void DrawIndexedPrimitiveUPUV2();
	virtual void DrawIndexedPrimitiveUPUV2x2();
};