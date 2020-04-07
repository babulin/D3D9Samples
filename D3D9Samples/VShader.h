#pragma once
#include "Base.h"
#include "Device.h"
class VShader : public Device{
public:
	float mWidth;
	float mHeight;
private:
	LPDIRECT3DDEVICE9 m_d3dDevice;				//D3D�豸

	LPD3DXCONSTANTTABLE mVSConstTable;			//�������ӿ�
	LPD3DXCONSTANTTABLE mPSConstTable = NULL;	//�������ӿ�
	LPDIRECT3DVERTEXSHADER9 mVertexShader;		//������ɫ���ӿ�
	LPDIRECT3DPIXELSHADER9 mPixelShader;		//������ɫ���ӿ�

	LPDIRECT3DVERTEXDECLARATION9 pVertexDecl;	//��������
public:
	VShader(D3D9* d3d9);
	void LoadVS(wchar_t file[], LPDIRECT3DVERTEXSHADER9 &mVShader,LPD3DXCONSTANTTABLE &mVSCTable);
	void VSShader(wchar_t file[]);
	void PSShader(wchar_t file[]);
	void DrawXYZ();
	void DrawVSShader();
};