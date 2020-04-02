#pragma once
#include "Base.h"

class ShaderBox {
public:
	float mWidth;
	float mHeight;
private:
	LPDIRECT3DDEVICE9 m_d3dDevice;				//D3D设备

	LPD3DXCONSTANTTABLE mVSConstTable;			//常量表接口
	LPD3DXCONSTANTTABLE mPSConstTable = NULL;	//常量表接口
	LPDIRECT3DVERTEXSHADER9 mVertexShader;		//顶点着色器接口
	LPDIRECT3DPIXELSHADER9 mPixelShader;		//像素着色器接口

	LPDIRECT3DVERTEXDECLARATION9 pVertexDecl;	//顶点描述
public:
	ShaderBox(LPDIRECT3DDEVICE9 d3dDevice,int width,int height);
	void LoadVS(wchar_t file[], LPDIRECT3DVERTEXSHADER9 &mVShader,LPD3DXCONSTANTTABLE &mVSCTable);
	void VSShader();
	void PSShader();
	void DrawXYZ();
	void DrawVSShader();


};