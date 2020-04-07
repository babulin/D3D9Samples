#pragma once
#include "Base.h"
#include "Device.h"
class Texture :public Device{
protected:
	LPDIRECT3DTEXTURE9 mTextureBG1;				//Œ∆¿Ì - ±≥æ∞1
	LPDIRECT3DTEXTURE9 mTextureBG2;				//Œ∆¿Ì - ±≥æ∞2
	LPDIRECT3DTEXTURE9 mTextureBG3;				//Œ∆¿Ì - ±≥æ∞3
	LPDIRECT3DTEXTURE9 mTexture1x1;				//Œ∆¿Ì - 1x1
	LPDIRECT3DTEXTURE9 mTexture2x2;				//Œ∆¿Ì - 2x2
public:
	Texture(D3D9* d3d9);
	virtual void Init();
	HRESULT CreateTexture();
	HRESULT CreateTexture1x1();
	HRESULT CreateTexture2x2();
	virtual void DrawPrimitiveUPUV1();
	virtual void DrawIndexedPrimitiveUPUV2();
	virtual void DrawIndexedPrimitiveUPUV2x2();
};