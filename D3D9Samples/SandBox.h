#pragma once
#include "Base.h"

class SandBox {
public:
	float mWidth;
	float mHeight;
private:
	LPDIRECT3DDEVICE9 m_d3dDevice;			//D3D设备
	LPDIRECT3DVERTEXBUFFER9 m_d3dBuffer;	//顶点缓冲区
	LPDIRECT3DINDEXBUFFER9 m_d3dIndex;		//索引缓冲区
	LPDIRECT3DTEXTURE9 m_Texture;			//纹理 - 图片1
	LPDIRECT3DTEXTURE9 m_Texture1;			//纹理 - 图片2
	LPDIRECT3DTEXTURE9 m_Texture2;			//纹理 - 图片3
	LPDIRECT3DTEXTURE9 m_Texture_1x1;		//纹理 - 1x1白色
	LPDIRECT3DTEXTURE9 m_Texture_2x2;		//纹理 - 2x2四色
	LPDIRECT3DTEXTURE9 m_TextureHum;		//纹理 - 人物1
	LPDIRECT3DTEXTURE9 m_Hum;				//纹理 - 人物2

	LPD3DXCONSTANTTABLE mVSConstTable;//常量表接口
	LPD3DXCONSTANTTABLE mPSConstTable = NULL;
	LPDIRECT3DVERTEXSHADER9 mVertexShader;//顶点着色器接口
	LPDIRECT3DPIXELSHADER9 mPixelShader;//像素着色器接口

	LPDIRECT3DVERTEXDECLARATION9 pVertexDecl = NULL;
	LPD3DXMESH pMeshTeapot = NULL;
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
	void PSShader01();
	void RunCSO();

	virtual void SetUpMatrices();

};