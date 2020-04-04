#pragma once
#include "Base.h"
#include "Texture.h"

class Shader :public Texture{

public:
	Shader(LPDIRECT3DDEVICE9 d3dDevice, int width, int height);
	void Init();
	void DrawPrimitiveUPUV1();
	void DrawIndexedPrimitiveUPUV2();
	void DrawIndexedPrimitiveUPUV2x2();
};