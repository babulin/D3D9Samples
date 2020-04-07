#pragma once
#include "Base.h"
#include "Device.h"
#include "D3D9.h"

class VertexBuffer : public Device{
protected:
	LPDIRECT3DVERTEXBUFFER9 m_d3dBuffer;		//顶点缓冲区
	LPDIRECT3DINDEXBUFFER9 m_d3dIndex;			//索引缓冲区
public:
	VertexBuffer(D3D9* d3d9);
	void Init();
	HRESULT CreateVertex();
	HRESULT CreateIndices();
	void Draw();
	void DrawPrimitiveUP();
	void DrawIndexedPrimitiveUP();
};