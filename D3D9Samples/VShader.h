#pragma once
#include "Base.h"
#include "Device.h"
class VShader : public Device{
public:
	LPD3DXCONSTANTTABLE mVSConstTable;			//常量表接口
	LPD3DXCONSTANTTABLE mPSConstTable = NULL;	//常量表接口
	LPDIRECT3DVERTEXSHADER9 mVertexShader;		//顶点着色器接口
	LPDIRECT3DPIXELSHADER9 mPixelShader;		//像素着色器接口

	LPDIRECT3DVERTEXDECLARATION9 pVertexDecl;	//顶点描述
public:
	VShader(D3D9* d3d9);
	void LoadVS(wchar_t file[], LPDIRECT3DVERTEXSHADER9 &mVShader,LPD3DXCONSTANTTABLE &mVSCTable);
	void VSShader(const wchar_t file[], D3DVERTEXELEMENT9 element[]);
	void PSShader(wchar_t file[]);
	void DrawXYZ();
	void DrawVSShader();
};