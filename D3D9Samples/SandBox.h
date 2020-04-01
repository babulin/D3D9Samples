#pragma once
#include "Base.h"

struct D3Vertex
{
	float x, y, z;
	DWORD color;
	static const DWORD FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
};

struct UVVertex
{
	float x, y, z;
	DWORD color;
	float u, v;
	float u1, v1;
	static const DWORD FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX2;
};

struct UV2Vertex
{
	float x, y, z;
	DWORD color;
	float u, v;
	float u1, v1;
	float u2, v2;
	static const DWORD FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX3;
};

struct RHWVertex
{
	float x, y, z, rhw;
	DWORD color;
	float u, v;
	float u1, v1;
	static const DWORD FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX2;
};

class SandBox {
public:
	float mWidth;
	float mHeight;
private:
	LPDIRECT3DDEVICE9 m_d3dDevice;			//D3D�豸
	LPDIRECT3DVERTEXBUFFER9 m_d3dBuffer;	//���㻺����
	LPDIRECT3DINDEXBUFFER9 m_d3dIndex;		//����������
	LPDIRECT3DTEXTURE9 m_Texture;			//���� - ͼƬ1
	LPDIRECT3DTEXTURE9 m_Texture1;			//���� - ͼƬ2
	LPDIRECT3DTEXTURE9 m_Texture2;			//���� - ͼƬ3
	LPDIRECT3DTEXTURE9 m_Texture_1x1;		//���� - 1x1��ɫ
	LPDIRECT3DTEXTURE9 m_Texture_2x2;		//���� - 2x2��ɫ
	LPDIRECT3DTEXTURE9 m_TextureHum;		//���� - ����1
	LPDIRECT3DTEXTURE9 m_Hum;				//���� - ����2

	LPD3DXCONSTANTTABLE mVSConstTable;//������ӿ�
	LPD3DXCONSTANTTABLE mPSConstTable = NULL;
	LPDIRECT3DVERTEXSHADER9 mVertexShader;//������ɫ���ӿ�
	LPDIRECT3DPIXELSHADER9 mPixelShader;//������ɫ���ӿ�
public:
	SandBox(LPDIRECT3DDEVICE9 m_d3dDevice);
	virtual HRESULT Init();
	virtual HRESULT SetIndices();
	void SetTexture();
	void SetHumTexture();
	void SetTexture2X2();
	virtual void Draw();
	void DrawUp();
	void DrawIndexedUp();
	void DrawIndexedUpTexture();
	void DrawIndexedUpHumTexture();
	void DrawIndexedUpHumTextureShader();

	void VSShader();
	void PSShader();
	void RunCSO();

	virtual void SetUpMatrices();

};