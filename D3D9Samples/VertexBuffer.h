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

	LPD3DXCONSTANTTABLE mVSConstTable;			//������ӿ�
	LPD3DXCONSTANTTABLE mPSConstTable = NULL;	//������ӿ�
	LPDIRECT3DVERTEXSHADER9 mVertexShader;		//������ɫ���ӿ�
	LPDIRECT3DPIXELSHADER9 mPixelShader;		//������ɫ���ӿ�

	LPDIRECT3DVERTEXDECLARATION9 pVertexDecl;	//��������
public:
	VertexBuffer(LPDIRECT3DDEVICE9 d3dDevice, int width, int height);
	HRESULT CreateVertex();
	HRESULT CreateIndices();
	void Draw();
};