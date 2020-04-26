#include "Texture.h"

Texture::Texture(D3D9* d3d9)
:Device(d3d9)
{
	 mTextureBG1 = nullptr;				//纹理 - 背景1
	 mTextureBG2 = nullptr;				//纹理 - 背景2
	 mTextureBG3 = nullptr;				//纹理 - 背景3
	 mTexture1x1 = nullptr;				//纹理 - 1x1
	 mTexture2x2 = nullptr;				//纹理 - 2x2
	 mTextureP1 = nullptr;				//纹理 - 图1
}

Texture::~Texture()
{
	mTextureBG1->Release();
	mTextureBG2->Release();
	mTextureBG3->Release();
	mTexture1x1->Release();
	mTexture2x2->Release();
	mTextureP1->Release();
}

void Texture::Init()
{
	CreateTexture();
	CreateTexture1x1();
	CreateTexture2x2();
}

HRESULT Texture::CreateTexture()
{
	//---------------------------------------------------------
	if (D3DXCreateTextureFromFile(m_d3dDevice, L"bg.bmp", &mTextureBG1) != D3D_OK) {
		MessageBox(NULL, L"纹理加载失败", L"小兔叽", MB_OK);
	}

	//---------------------------------------------------------
	if (D3DXCreateTextureFromFile(m_d3dDevice, L"bg1.bmp", &mTextureBG2) != D3D_OK) {
		MessageBox(NULL, L"纹理加载失败", L"小兔叽", MB_OK);
	}

	//---------------------------------------------------------
	if (D3DXCreateTextureFromFile(m_d3dDevice, L"bg2.bmp", &mTextureBG3) != D3D_OK) {
		MessageBox(NULL, L"纹理加载失败", L"小兔叽", MB_OK);
	}

	//---------------------------------------------------------
	if (D3DXCreateTextureFromFile(m_d3dDevice, L"p1.jpg", &mTextureP1) != D3D_OK) {
		MessageBox(NULL, L"纹理加载失败", L"小兔叽", MB_OK);
	}

	return S_OK;
}

HRESULT Texture::CreateTexture1x1()
{
	//---------------------------------------------------------
	//纹理1X1
	if (FAILED(m_d3dDevice->CreateTexture(1, 1, 0, D3DUSAGE_DYNAMIC, D3DFMT_A32B32G32R32F, D3DPOOL_DEFAULT, &mTexture1x1, nullptr))) {
		MessageBox(NULL, L"创建1x1纹理失败", L"小兔叽", MB_OK);
	}

	D3DSURFACE_DESC desc;
	mTexture1x1->GetLevelDesc(0, &desc);

	D3DLOCKED_RECT lockRect;
	mTexture1x1->LockRect(0, &lockRect, 0, 0);

	D3DXVECTOR4* Data = (D3DXVECTOR4*)lockRect.pBits;

	//赋值
	for (UINT h = 0; h < desc.Height; h++)
	{
		for (UINT w = 0; w < desc.Width; w++)
		{
			UINT index = h * lockRect.Pitch / 16 + w;
			Data[index] = COLORF_WHITE;
		}
	}

	mTexture1x1->UnlockRect(0);

	return S_OK;
}

HRESULT Texture::CreateTexture2x2()
{
	//---------------------------------------------------------
	//纹理2X2
	if (FAILED(m_d3dDevice->CreateTexture(2, 2, 0, D3DUSAGE_DYNAMIC, D3DFMT_A32B32G32R32F, D3DPOOL_DEFAULT, &mTexture2x2, nullptr))) {
		MessageBox(NULL, L"创建2x2纹理失败", L"小兔叽", MB_OK);
	}

	D3DSURFACE_DESC desc1;
	mTexture2x2->GetLevelDesc(0, &desc1);

	D3DLOCKED_RECT lockRect1;
	mTexture2x2->LockRect(0, &lockRect1, 0, 0);

	D3DXVECTOR4* Data1 = (D3DXVECTOR4*)lockRect1.pBits;

	//赋值
	D3DXVECTOR4 COLOR[4] = {
		COLORF_RED,
		COLORF_GREEN,
		COLORF_BLUE,
		COLORF_WHITE
	};

	for (UINT h = 0; h < desc1.Height; h++)
	{
		for (UINT w = 0; w < desc1.Width; w++)
		{
			UINT index = h * lockRect1.Pitch / 16 + w;
			Data1[index] = COLOR[h * 2 + w];
		}
	}

	mTexture2x2->UnlockRect(0);

	return S_OK;
}

void Texture::DrawPrimitiveUPUV1()
{
	m_d3dDevice->SetRenderState(D3DRS_LIGHTING, false);
	m_d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//0 1    //0 
	//  2    //3 2
	float x = 0.8f, y = 0.8f;
	float min = 0.0f,max = 1.0f;
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

void Texture::DrawIndexedPrimitiveUPUV2()
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
	m_d3dDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, ARRAYSIZE(indexBuffer), ARRAYSIZE(indexBuffer)/3, indexBuffer, D3DFMT_INDEX16, vertex, sizeof(UV2Vertex));
}

void Texture::DrawIndexedPrimitiveUPUV2x2()
{
	m_d3dDevice->SetRenderState(D3DRS_LIGHTING, false);
	m_d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//0 1    //0 
	//  2    //3 2
	float x = 0.8f, y = 0.8f;
	float min = 0.0f, max = 1.0f,min1 = 0.25f, max1 = 0.75f;
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
