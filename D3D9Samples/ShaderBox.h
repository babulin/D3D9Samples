#pragma once
#include "Base.h"

class ShaderBox {
public:
	float mWidth;
	float mHeight;
private:
	LPDIRECT3DDEVICE9 m_d3dDevice;				//D3D�豸

	LPD3DXCONSTANTTABLE mVSConstTable;			//������ӿ�
	LPD3DXCONSTANTTABLE mPSConstTable = NULL;	//������ӿ�
	LPDIRECT3DVERTEXSHADER9 mVertexShader;		//������ɫ���ӿ�
	LPDIRECT3DPIXELSHADER9 mPixelShader;		//������ɫ���ӿ�

	LPDIRECT3DVERTEXDECLARATION9 pVertexDecl;	//��������
public:
	ShaderBox(LPDIRECT3DDEVICE9 d3dDevice,int width,int height);
	void LoadVS(wchar_t file[], LPDIRECT3DVERTEXSHADER9 &mVShader,LPD3DXCONSTANTTABLE &mVSCTable);
	void VSShader();
	void PSShader();
	void DrawXYZ();
	void DrawVSShader();


};