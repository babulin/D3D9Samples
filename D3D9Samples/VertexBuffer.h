#pragma once
#include "Base.h"

class VertexBuffer {
public:
	float mWidth;
	float mHeight;
private:
	LPDIRECT3DDEVICE9 m_d3dDevice;				//D3D�豸

	LPDIRECT3DVERTEXBUFFER9 m_d3dBuffer;		//���㻺����
	LPDIRECT3DINDEXBUFFER9 m_d3dIndex;			//����������
public:
	VertexBuffer(LPDIRECT3DDEVICE9 d3dDevice, int width, int height);
	void Init();
	HRESULT CreateVertex();
	HRESULT CreateIndices();
	void Draw();
	void DrawPrimitiveUP();
	void DrawIndexedPrimitiveUP();
};