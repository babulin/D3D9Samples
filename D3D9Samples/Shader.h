#pragma once
#include "Base.h"
#include "Texture.h"

class Shader :public Texture{

public:
	Shader(D3D9* d3d9);
	void Init();
	void DrawPrimitiveUPUV1();
	void DrawIndexedPrimitiveUPUV2();
	void DrawIndexedPrimitiveUPUV2x2();
};