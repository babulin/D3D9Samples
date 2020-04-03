#pragma once
#include "Base.h"

class VertexBuffer {
public:
	float mWidth;
	float mHeight;
private:
	LPDIRECT3DDEVICE9 m_d3dDevice;				//D3D设备

	LPDIRECT3DVERTEXBUFFER9 m_d3dBuffer;		//顶点缓冲区
	LPDIRECT3DINDEXBUFFER9 m_d3dIndex;			//索引缓冲区

	LPD3DXCONSTANTTABLE mVSConstTable;			//常量表接口
	LPD3DXCONSTANTTABLE mPSConstTable = NULL;	//常量表接口
	LPDIRECT3DVERTEXSHADER9 mVertexShader;		//顶点着色器接口
	LPDIRECT3DPIXELSHADER9 mPixelShader;		//像素着色器接口

	LPDIRECT3DVERTEXDECLARATION9 pVertexDecl;	//顶点描述
public:
	VertexBuffer(LPDIRECT3DDEVICE9 d3dDevice, int width, int height);
	HRESULT CreateVertex();
	HRESULT CreateIndices();
	void Draw();
};