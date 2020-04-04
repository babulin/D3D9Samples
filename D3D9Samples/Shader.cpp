#include "Shader.h"

Shader::Shader(LPDIRECT3DDEVICE9 d3dDevice, int width, int height):Texture(d3dDevice,width,height)
{

}

void Shader::Init()
{
	CreateTexture();
	CreateTexture1x1();
	CreateTexture2x2();
}

void Shader::DrawPrimitiveUPUV1()
{
	m_d3dDevice->SetRenderState(D3DRS_LIGHTING, false);
	m_d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//0 1    //0 
	//  2    //3 2
	float x = 0.8f, y = 0.8f;
	float min = 0.0f, max = 1.0f;
	UV1Vertex vertex[] = {
		{-x , y, 1.0f, COLOR_RED	,min,min},
		{ x , y, 1.0f, COLOR_GREEN	,max,min},
		{ x	,-y, 1.0f, COLOR_BLUE	,max,max},
		{-x	, y, 1.0f, COLOR_RED	,min,min},
		{ x	,-y, 1.0f, COLOR_BLUE	,max,max},
		{-x ,-y, 1.0f, COLOR_WHITE	,min,max},
	};

	//使用纹理
	m_d3dDevice->SetTexture(0, mTextureBG1);

	//绘制顶点缓存
	m_d3dDevice->SetFVF(UV1Vertex::FVF);
	m_d3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, vertex, sizeof(UV1Vertex));
}

void Shader::DrawIndexedPrimitiveUPUV2()
{
	m_d3dDevice->SetRenderState(D3DRS_LIGHTING, false);
	m_d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//0 1    //0 
	//  2    //3 2
	float x = 0.8f, y = 0.8f;
	float min = 0.0f, max = 1.0f;
	UV2Vertex vertex[] = {
		{-x , y, 1.0f, COLOR_RED	,min,min,min,min},
		{ x , y, 1.0f, COLOR_WHITE	,max,min,max,min},
		{ x	,-y, 1.0f, COLOR_WHITE	,max,max,max,max},
		{-x	, y, 1.0f, COLOR_RED	,min,min,min,min},
		{ x	,-y, 1.0f, COLOR_WHITE	,max,max,max,max},
		{-x ,-y, 1.0f, COLOR_WHITE	,min,max,min,max},
	};

	//使用纹理
	m_d3dDevice->SetTexture(0, mTextureBG1);
	m_d3dDevice->SetTexture(1, mTextureBG2);

	//纹理融合
	for (DWORD i = 0; i < 2; ++i)
	{
		// Color通道混合算法设置（纹理 * 当前）
		m_d3dDevice->SetTextureStageState(i, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		m_d3dDevice->SetTextureStageState(i, D3DTSS_COLORARG2, D3DTA_CURRENT);
		m_d3dDevice->SetTextureStageState(i, D3DTSS_COLOROP, D3DTOP_MODULATE);
		// Alpha通道混合算法设置（纹理 * 当前）
		m_d3dDevice->SetTextureStageState(i, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		m_d3dDevice->SetTextureStageState(i, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
		m_d3dDevice->SetTextureStageState(i, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	}

	//顶点格式
	m_d3dDevice->SetFVF(UV2Vertex::FVF);

	//绘制顶点缓存
	short indexBuffer[] = { 0,1,2,3,4,5 };
	m_d3dDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, ARRAYSIZE(indexBuffer), ARRAYSIZE(indexBuffer) / 3, indexBuffer, D3DFMT_INDEX16, vertex, sizeof(UV2Vertex));
}

void Shader::DrawIndexedPrimitiveUPUV2x2()
{
	m_d3dDevice->SetRenderState(D3DRS_LIGHTING, false);
	m_d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//0 1    //0 
	//  2    //3 2
	float x = 0.8f, y = 0.8f;
	float min = 0.0f, max = 1.0f, min1 = 0.25f, max1 = 0.75f;
	UV2Vertex vertex[] = {
		{-x , y, 1.0f, COLOR_WHITE	,min,min,min1,min1},
		{ x , y, 1.0f, COLOR_WHITE	,max,min,max1,min1},
		{ x	,-y, 1.0f, COLOR_WHITE	,max,max,max1,max1},
		{-x	, y, 1.0f, COLOR_WHITE	,min,min,min1,min1},
		{ x	,-y, 1.0f, COLOR_WHITE	,max,max,max1,max1},
		{-x ,-y, 1.0f, COLOR_WHITE	,min,max,min1,max1},
	};

	//使用纹理
	m_d3dDevice->SetTexture(0, mTextureBG1);
	m_d3dDevice->SetTexture(1, mTexture2x2);

	//纹理融合
	for (DWORD i = 0; i < 2; ++i)
	{
		// Color通道混合算法设置（纹理 * 当前）
		m_d3dDevice->SetTextureStageState(i, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		m_d3dDevice->SetTextureStageState(i, D3DTSS_COLORARG2, D3DTA_CURRENT);
		m_d3dDevice->SetTextureStageState(i, D3DTSS_COLOROP, D3DTOP_MODULATE);
		// Alpha通道混合算法设置（纹理 * 当前）
		m_d3dDevice->SetTextureStageState(i, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		m_d3dDevice->SetTextureStageState(i, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
		m_d3dDevice->SetTextureStageState(i, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	}

	//设置纹理采样
	m_d3dDevice->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_d3dDevice->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

	//顶点格式
	m_d3dDevice->SetFVF(UV2Vertex::FVF);

	//绘制顶点缓存
	short indexBuffer[] = { 0,1,2,3,4,5 };
	m_d3dDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, ARRAYSIZE(indexBuffer), ARRAYSIZE(indexBuffer) / 3, indexBuffer, D3DFMT_INDEX16, vertex, sizeof(UV2Vertex));
}
