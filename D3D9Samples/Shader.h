#pragma once
#include "Base.h"
#include "Texture.h"
#include "VShader.h"

class Shader :public Texture{
public:
	VShader* g_vshader;
	VShader* g_pshader;
public:
	Shader(D3D9* d3d9);
	~Shader();
	void Init();
	void DrawPrimitiveUPUV1();
	void DrawIndexedPrimitiveUPUV2();
	void DrawIndexedPrimitiveUPUV2x2();
	void DrawVSShader();


	//≤‚ ‘
	void SetMatrices();
	void DrawSquare();
};