#include "SandBox.h"
#include<iostream>
#include<fstream>
using std::ofstream;
using std::ios;

SandBox::SandBox(LPDIRECT3DDEVICE9 p_d3dDevice)
{
	m_d3dDevice = p_d3dDevice;
}

HRESULT SandBox::Init()
{
	//创建顶点缓存
	float x = 0.5f, y = 0.5f;
	D3Vertex vertex[] = {
		{ -x, -y, 1.0f	, 0xffffffff, }, // x, y, z, rhw, color
		{ -x, y	, 1.0f	, 0x00ffffff, },
		{ x	, y	, 1.0f	, 0xff00ffff, },
		{ x	, -y, 1.0f	, 0xffff00ff, },
	};

	if (FAILED(m_d3dDevice->CreateVertexBuffer(sizeof(vertex), 0, D3Vertex::FVF, D3DPOOL_DEFAULT, &m_d3dBuffer, NULL))) {
		return E_FAIL;
	}

	void* pvertexes = NULL;
	if (FAILED(m_d3dBuffer->Lock(0, sizeof(vertex), (void**)&pvertexes, 0))) {
		return E_FAIL;
	}

	memcpy(pvertexes, vertex, sizeof(vertex));

	m_d3dBuffer->Unlock();

	return S_OK;
}

HRESULT SandBox::SetIndices()
{
	//创建索引缓存
	short indexBuffer[6] = { 0,1,3,1,2,3 };
	if (FAILED(m_d3dDevice->CreateIndexBuffer(sizeof(indexBuffer), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_d3dIndex, NULL)))
	{
		return E_FAIL;
	}

	void* indexs = NULL;
	if (FAILED(m_d3dIndex->Lock(0, sizeof(indexBuffer), (void**)&indexs, 0))) {
		return E_FAIL;
	}

	memcpy(indexs, indexBuffer, sizeof(indexBuffer));

	m_d3dIndex->Unlock();

	return S_OK;
}

void SandBox::SetTexture()
{
	//---------------------------------------------------------
	if (D3DXCreateTextureFromFile(m_d3dDevice, L"bg.bmp", &m_Texture) != D3D_OK) {
		MessageBox(NULL, L"纹理加载失败", L"小兔叽", MB_OK);
	}

	//FILE* fp;
	//fopen_s(&fp, "bg.bmp", "r");
	//fseek(fp, 0, SEEK_END);
	//size_t size = ftell(fp);

	//fseek(fp, 0, SEEK_END);
	//D3DXCreateTextureFromFileInMemory(m_d3dDevice, fp, size, &m_Texture);
	//fclose(fp);

	//---------------------------------------------------------
	if (D3DXCreateTextureFromFile(m_d3dDevice, L"bg1.bmp", &m_Texture1) != D3D_OK) {
		MessageBox(NULL, L"纹理加载失败", L"小兔叽", MB_OK);
	}

	//---------------------------------------------------------
	if (D3DXCreateTextureFromFile(m_d3dDevice, L"bg2.bmp", &m_Texture2) != D3D_OK) {
		MessageBox(NULL, L"纹理加载失败", L"小兔叽", MB_OK);
	}
	//---------------------------------------------------------
	//纹理1X1
	if (FAILED(m_d3dDevice->CreateTexture(1, 1, 0, D3DUSAGE_DYNAMIC, D3DFMT_A32B32G32R32F, D3DPOOL_DEFAULT, &m_Texture_1x1, nullptr))) {
		MessageBox(NULL, L"创建1x1纹理失败", L"小兔叽", MB_OK);
	}

	D3DSURFACE_DESC desc;
	m_Texture_1x1->GetLevelDesc(0, &desc);

	D3DLOCKED_RECT lockRect;
	m_Texture_1x1->LockRect(0, &lockRect, 0, 0);

	D3DXVECTOR4* Data = (D3DXVECTOR4*)lockRect.pBits;

	//赋值
	for (UINT h = 0; h < desc.Height; h++)
	{
		for (UINT w = 0; w < desc.Width;w++)
		{
			UINT index = h * lockRect.Pitch / 16 + w;
			Data[index] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}

	m_Texture_1x1->UnlockRect(0);
}

void SandBox::SetTexture2X2() {
	//---------------------------------------------------------
	//纹理2X2
	if (FAILED(m_d3dDevice->CreateTexture(2, 2, 0, D3DUSAGE_DYNAMIC, D3DFMT_A32B32G32R32F, D3DPOOL_DEFAULT, &m_Texture_2x2, nullptr))) {
		MessageBox(NULL, L"创建2x2纹理失败", L"小兔叽", MB_OK);
	}

	D3DSURFACE_DESC desc1;
	m_Texture_2x2->GetLevelDesc(0, &desc1);

	D3DLOCKED_RECT lockRect1;
	m_Texture_2x2->LockRect(0, &lockRect1, 0, 0);

	D3DXVECTOR4* Data1 = (D3DXVECTOR4*)lockRect1.pBits;

	//赋值
	D3DXVECTOR4 COLOR[4] = {
		D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f),
		D3DXVECTOR4(1.0f, 0.0f, 1.0f, 1.0f),
		D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f),
		D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f)
	};
	for (UINT h = 0; h < desc1.Height; h++)
	{
		for (UINT w = 0; w < desc1.Width; w++)
		{
			UINT index = h * lockRect1.Pitch / 16 + w;
			Data1[index] = COLOR[h * 2 + w];
		}
	}

	m_Texture_2x2->UnlockRect(0);
}

void SandBox::SetHumTexture()
{
	//---------------------------------------------------------
	//人物纹理
	if (D3DXCreateTextureFromFile(m_d3dDevice, L"h2.bmp", &m_TextureHum) != D3D_OK) {
		MessageBox(NULL, L"纹理加载失败", L"小兔叽", MB_OK);
	}

	D3DSURFACE_DESC hum;
	m_TextureHum->GetLevelDesc(0, &hum);

	//D3DLOCKED_RECT lockHum;
	//m_TextureHum->LockRect(0, &lockHum, 0, 0);

	//DWORD* Data = (DWORD*)lockHum.pBits;

	////赋值
	//for (UINT h = 0; h < hum.Height; h++)
	//{
	//	for (UINT w = 0; w < hum.Width; w++)
	//	{
	//		UINT index = h * lockHum.Pitch / 4 + w;
	//		DWORD color = Data[index];
	//		D3DCOLORVALUE* cl = (D3DCOLORVALUE*)&color;
	//		if (cl->r != 0) {
	//			int i = 0;
	//		}
	//		if (color == 0x00000000)
	//		{
	//			Data[index] = D3DCOLOR_ARGB(0, 0xff, 0xff, 0xff);
	//		}
	//		//Data[index] = D3DCOLOR_ARGB(0xff, cl->rgbRed, cl->rgbGreen, cl->rgbBlue);
	//	}
	//}

	//m_TextureHum->UnlockRect(0);


	//创建一个新的纹理
	m_d3dDevice->CreateTexture(hum.Width, hum.Height, 0, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_Hum, NULL);

	IDirect3DSurface9* m_srcSurface;
	IDirect3DSurface9* m_dstSurface;
	m_TextureHum->GetSurfaceLevel(0, &m_srcSurface);
	m_Hum->GetSurfaceLevel(0, &m_dstSurface);

	D3DXLoadSurfaceFromSurface(
		m_dstSurface,
		NULL, NULL,
		m_srcSurface,
		NULL, NULL,
		D3DX_FILTER_LINEAR,
		D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff)
	);

	//处理
	D3DSURFACE_DESC hum2;
	m_Hum->GetLevelDesc(0, &hum2);

	D3DLOCKED_RECT lockHum2;
	m_Hum->LockRect(0, &lockHum2, 0, 0);

	DWORD* Data2 = (DWORD*)lockHum2.pBits;

	//赋值
	for (UINT h = 0; h < hum2.Height; h++)
	{
		for (UINT w = 0; w < hum2.Width; w++)
		{
			UINT index = h * lockHum2.Pitch / 4 + w;
			RGBQUAD* cl = (RGBQUAD*)&Data2[index];
			if (cl->rgbRed != 0) {
				int i = 0;
			}
			if (cl->rgbRed == 0 && cl->rgbGreen == 0 && cl->rgbBlue == 0)
			{
				Data2[index] = D3DCOLOR_ARGB(0x0, 0xff, 0, 0);
			}
			//Data2[index] = D3DCOLOR_ARGB(0x55, cl->rgbRed, cl->rgbGreen, cl->rgbBlue);
			//Data[index] = D3DCOLOR_ARGB(0xff, cl->rgbRed, cl->rgbGreen, cl->rgbBlue);
		}
	}

	m_Hum->UnlockRect(0);
}

void SandBox::Draw()
{
	SetUpMatrices();

	m_d3dDevice->SetRenderState(D3DRS_LIGHTING, false);
	m_d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//绘制顶点缓存
	m_d3dDevice->SetStreamSource(0, m_d3dBuffer, 0, sizeof(D3Vertex));
	m_d3dDevice->SetFVF(D3Vertex::FVF);
	//6个点

	//m_d3dDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);

	m_d3dDevice->SetIndices(m_d3dIndex);
	m_d3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 6, 0, 2);
}

void SandBox::DrawUp()
{
	SetUpMatrices();

	m_d3dDevice->SetRenderState(D3DRS_LIGHTING, false);
	m_d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//创建顶点缓存
	DWORD color1 = D3DCOLOR_ARGB(255, 255, 0, 0);
	DWORD color2 = D3DCOLOR_ARGB(255, 0, 255, 0);
	DWORD color3 = D3DCOLOR_ARGB(255, 0, 0, 255);
	DWORD color4 = D3DCOLOR_ARGB(255, 255, 255, 255);

	float x = 0.5f, y = 0.5f;
	D3Vertex vertex[] = {
		{ -x, -y	, 1.0f	, color1 }, // x, y, z, rhw, color
		{ -x, y	, 1.0f	, color2 },
		//{ 0.8f	, -0.8f	, 1.0f	, color3 },
		{ x	, y	, 1.0f	, color4 },
		{ x	, y	, 1.0f	, color4 },
		{ x	, -y	, 1.0f	, color3 },
		{ -x, -y	, 1.0f	, color1 },
		//{ -0.8f	, 0.8f	, 1.0f	, color2 },
	};

	//绘制顶点缓存
	m_d3dDevice->SetFVF(D3Vertex::FVF);
	m_d3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, vertex,sizeof(D3Vertex));
}

void SandBox::DrawIndexedUp()
{
	SetUpMatrices();

	m_d3dDevice->SetRenderState(D3DRS_LIGHTING, false);
	m_d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//创建顶点缓存
	float max = 0.75f, min = 0.25f;
	float x = 0.5f, y = 0.5f;
	UVVertex vertex[] = {
		{ -x, -y	, 1.0f	,0xffffffff,0.0f ,1.0f,min ,max }, // x, y, z, rhw, color
		{ -x, y	, 1.0f	,0xffffffff,0.0f ,0.0f,min ,min },
		{ x	, y	, 1.0f	,0xffffffff,1.0f ,0.0f,max ,min },
		{ x	, -y	, 1.0f	,0xffffffff,1.0f ,1.0f,max ,max },
	};

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


	//使用纹理
	m_d3dDevice->SetTexture(0, m_Texture_1x1);
	m_d3dDevice->SetTexture(1, m_Texture_2x2);

	m_d3dDevice->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_d3dDevice->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

	//绘制顶点缓存
	m_d3dDevice->SetFVF(UVVertex::FVF);
	short indexBuffer[6] = { 0,1,3,1,2,3 };
	m_d3dDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, 4, 2, indexBuffer, D3DFMT_INDEX16, vertex,sizeof(UVVertex));
}

void SandBox::DrawIndexedUpTexture()
{
	SetUpMatrices();

	m_d3dDevice->SetRenderState(D3DRS_LIGHTING, false);
	m_d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//创建顶点缓存
	float max = 1.0f, min = 0.0f;
	float x = 1.2f, y = 0.9f;
	UV2Vertex vertex[] = {
		{ -x, -y, 1.0f	,0xffffffff,min ,max,min ,max,min ,max }, // x, y, z, rhw, color
		{ -x, y	, 1.0f	,0xffffffff,min ,min,min ,min,min ,min },
		{ x	, y	, 1.0f	,0xffffffff,max ,min,max ,min,max ,min },
		{ x	, -y, 1.0f	,0xffffffff,max ,max,max ,max,max ,max },
	};

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

	// Color通道混合算法设置（纹理 * 当前）
	int n = 2;
	m_d3dDevice->SetTextureStageState(n, D3DTSS_COLORARG1, D3DTA_CURRENT);
	m_d3dDevice->SetTextureStageState(n, D3DTSS_COLORARG2, D3DTA_TEXTURE);
	m_d3dDevice->SetTextureStageState(n, D3DTSS_COLOROP, D3DTOP_ADD);
	// Alpha通道混合算法设置（纹理 * 当前）
	m_d3dDevice->SetTextureStageState(n, D3DTSS_ALPHAARG1, D3DTA_CURRENT);
	m_d3dDevice->SetTextureStageState(n, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
	m_d3dDevice->SetTextureStageState(n, D3DTSS_ALPHAOP, D3DTOP_ADD);


	//使用纹理
	m_d3dDevice->SetTexture(0, m_Texture);
	m_d3dDevice->SetTexture(1, m_Texture1);
	m_d3dDevice->SetTexture(2, m_Texture2);

	//m_d3dDevice->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	//m_d3dDevice->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

	//绘制顶点缓存
	m_d3dDevice->SetFVF(UV2Vertex::FVF);
	short indexBuffer[6] = { 0,1,3,1,2,3 };
	m_d3dDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, 4, 2, indexBuffer, D3DFMT_INDEX16, vertex, sizeof(UV2Vertex));
}

void SandBox::DrawIndexedUpHumTexture()
{
	//着色器
	Shader();

	SetUpMatrices();

	m_d3dDevice->SetRenderState(D3DRS_LIGHTING, false);
	m_d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//绘制前要开启融合运算
	m_d3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	//设定融合因子，采用默认值
	m_d3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//创建顶点缓存
	float max = 1.0f, min = 0.0f;
	float x = 0.4f, y = 0.5f;
	UV2Vertex vertex[] = {
		{ -x, -y, 1.0f	,0xffffffff,min ,max,min ,max,min ,max }, // x, y, z, rhw, color
		{ -x, y	, 1.0f	,0xffffffff,min ,min,min ,min,min ,min },
		{ x	, y	, 1.0f	,0xffffffff,max ,min,max ,min,max ,min },
		{ x	, -y, 1.0f	,0xffffffff,max ,max,max ,max,max ,max },
	};


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

	// Color通道混合算法设置（纹理 * 当前）
	int n = 2;
	m_d3dDevice->SetTextureStageState(n, D3DTSS_COLORARG1, D3DTA_CURRENT);
	m_d3dDevice->SetTextureStageState(n, D3DTSS_COLORARG2, D3DTA_TEXTURE);
	m_d3dDevice->SetTextureStageState(n, D3DTSS_COLOROP, D3DTOP_ADD);
	// Alpha通道混合算法设置（纹理 * 当前）
	m_d3dDevice->SetTextureStageState(n, D3DTSS_ALPHAARG1, D3DTA_CURRENT);
	m_d3dDevice->SetTextureStageState(n, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
	m_d3dDevice->SetTextureStageState(n, D3DTSS_ALPHAOP, D3DTOP_ADD);


	//使用纹理
	m_d3dDevice->SetTexture(0, m_TextureHum);
	//m_d3dDevice->SetTexture(1, m_TextureHum);
	//m_d3dDevice->SetTexture(2, m_TextureHum);

	//m_d3dDevice->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	//m_d3dDevice->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

	//绘制顶点缓存
	m_d3dDevice->SetFVF(UV2Vertex::FVF);
	short indexBuffer[6] = { 0,1,3,1,2,3 };
	m_d3dDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, 4, 2, indexBuffer, D3DFMT_INDEX16, vertex, sizeof(UV2Vertex));
}

void SandBox::Shader()
{
	//创建着色器
	LPD3DXBUFFER shader = 0;
	LPD3DXBUFFER errorBuffer = 0;

	HRESULT hr = D3DXCompileShaderFromFile(L"PixelShader.hlsl", 0, 0, "main", "ps_3_0", D3DXSHADER_DEBUG, &shader, &errorBuffer, &mConstantTable);
	if (errorBuffer)
	{
		MessageBox(NULL, (LPCWSTR)errorBuffer->GetBufferPointer(), 0, 0);
		errorBuffer->Release();
	}

	if (FAILED(hr))
	{
		MessageBox(NULL, L"D3DXCompileShaderFromFile - failed", 0, 0);
		return;
	}


	hr = m_d3dDevice->CreatePixelShader((DWORD*)shader->GetBufferPointer(), &mPixelShader);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"CreatePixelShader - failed", 0, 0);
		return;
	}

	shader->Release();

	//hATex = mConstantTable->GetConstantByName(0, "ATex");
	//hBTex = mConstantTable->GetConstantByName(0, "BTex");
	//UINT count;
	//mConstantTable->GetConstantDesc(hATex, &ATex, &count);
	//mConstantTable->GetConstantDesc(hBTex, &BTex, &count);

	//mConstantTable->SetDefaults(m_d3dDevice);

}

void SandBox::DrawIndexedUpHumTextureShader()
{
	//SetUpMatrices();

	m_d3dDevice->SetRenderState(D3DRS_LIGHTING, false);
	m_d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//绘制前要开启融合运算
	//m_d3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	//设定融合因子，采用默认值
	//m_d3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//m_d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//创建顶点缓存
	float max = 1.0f, min = 0.0f;
	//float x = 1.0f, y = 0.8f;
	//UVVertex vertex[] = {
	//	{ -x, -y, 1.0f ,0x00ffffff,min ,max,min ,max}, // x, y, z, rhw, color
	//	{ -x, y	, 1.0f ,0xffffffff,min ,min,min ,min},
	//	{ x	, y	, 1.0f ,0xffffffff,max ,min,max ,min},
	//	{ x	, -y, 1.0f ,0xffffffff,max ,max,max ,max},
	//};
	float max1 = 0.75f, min1 = 0.25f;
	float x = 0.0f, y = 0.0f,w = 800.0f,h = 600.0f;
	RHWVertex vertex[] = {
	{ x	   , y + h	, 1.0f ,1.0f ,0x00ffffff,min ,max,min1 ,max1}, // x, y, z, rhw, color
	{ x	   , y		, 1.0f ,1.0f ,0xffffffff,min ,min,min1 ,min1},
	{ x + w, y		, 1.0f ,1.0f ,0xffffffff,max ,min,max1 ,min1},
	{ x + w, y + h	, 1.0f ,1.0f ,0xffffffff,max ,max,max1 ,max1},
	};

	//使用像素着色器
	float color[4] = { 0.0f,0.0f,1.0f,1.0f };
	m_d3dDevice->SetPixelShaderConstantF(0, color, 4);

	float color1[4] = { 0.0f,1.0f,1.0f,1.0f };
	m_d3dDevice->SetPixelShaderConstantF(sizeof(float) * 4, color1, 4);

	m_d3dDevice->SetPixelShader(mPixelShader);

	//使用纹理
	m_d3dDevice->SetTexture(0, m_Texture_1x1);
	m_d3dDevice->SetTexture(1, m_Texture_2x2);

	m_d3dDevice->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_d3dDevice->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

	//绘制顶点缓存
	m_d3dDevice->SetFVF(RHWVertex::FVF);
	short indexBuffer[6] = { 0,1,3,1,2,3 };
	m_d3dDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, 4, 2, indexBuffer, D3DFMT_INDEX16, vertex, sizeof(RHWVertex));
}



void SandBox::RunCSO()
{
	std::ifstream fp;

	fp.open("PixelShader.cso", ios::in | ios::binary);

	HRESULT hr = m_d3dDevice->CreatePixelShader((DWORD*)&fp, &mPixelShader);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"CreatePixelShader - failed", 0, 0);
		return;
	}

	//使用像素着色器
	m_d3dDevice->SetPixelShader(mPixelShader);
	
}

void SandBox::SetUpMatrices()
{
	///四大变换之一：世界变换矩阵的设置
	///[1]绕X旋转矩阵
	//D3DXMATRIX T1;
	//D3DXMatrixTranslation(&T1, -0.5f, 0.5f, 0.5f);
	//m_d3dDevice->SetTransform(D3DTS_WORLD, &T1);

	///四大变换之二：取景变换矩阵的设置
	//D3DXMATRIX matView;
	//D3DXVECTOR3 position(0.0f, 0.0f, -0.01f);//摄像机位置
	//D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);//观察点位置
	//D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);//向上的向量
	//D3DXMatrixLookAtLH(&matView, &position, &target, &up);
	//m_d3dDevice->SetTransform(D3DTS_VIEW, &matView);

	///四大变换之三：投影变换矩阵的设置
	//透视投影矩阵
	D3DXMATRIX proj;
	float aspect = (float)(mWidth / mHeight);
	D3DXMatrixPerspectiveFovLH(&proj, D3DX_PI * 0.5f, aspect, 1.0f, 1000.0f);
	m_d3dDevice->SetTransform(D3DTS_PROJECTION, &proj);

	///四大变换之四：视口变换的设置
	//D3DVIEWPORT9 vp;
	//vp.X = 0;
	//vp.Y = 0;
	//vp.Width = mWidth/2;//视口的宽度
	//vp.Height = mHeight/2;//视口的高度
	//vp.MinZ = 0.0;
	//vp.MaxZ = 1.0;
	//m_d3dDevice->SetViewport(&vp);
}
