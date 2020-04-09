#include "Shader.h"

Shader::Shader(D3D9* d3d9):Texture(d3d9)
{
	//创建shader
	g_vshader = new VShader(d3d9);
	g_pshader = new VShader(d3d9);
}

Shader::~Shader()
{
	if (g_vshader != nullptr)
	{
		delete g_vshader;
	}
	if (g_pshader != nullptr)
	{
		delete g_pshader;
	}
}

void Shader::Init()
{
	CreateTexture();
	CreateTexture1x1();
	CreateTexture2x2();

	//初始化着色器
	//g_vshader->VSShader(L"VertexShader.hlsl");

	//-------------------------------------------------------------------------------------
	//创建声明顶点
	D3DVERTEXELEMENT9 element[] = {
		{0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0},//顶点位置
		{0,12,D3DDECLTYPE_FLOAT4,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_COLOR,0},//漫反射颜色
		D3DDECL_END()//结束元素
	};
	g_vshader->VSShader(L"VS01_Shader.hlsl", element);


	//--------------------------------------------------------------------------------------
	g_pshader->PSShader(L"PS01_Shader.hlsl");
}

void Shader::DrawVSShader()
{
	//设置常量
	SetMatrices();

	//绘制立方体
	VSVertex vertex[] = {
		//正面
		VSVertex(-1.0f , 1.0f ,-1.0f ,0.0f ,0.0f ,-1.0f),
		VSVertex(1.0f , 1.0f ,-1.0f ,0.0f ,0.0f ,-1.0f),
		VSVertex(1.0f ,-1.0f ,-1.0f ,0.0f ,0.0f ,-1.0f),
		VSVertex(-1.0f ,-1.0f ,-1.0f ,0.0f ,0.0f ,-1.0f),

		//背面
		VSVertex(1.0f , 1.0f , 1.0f ,0.0f ,0.0f , 1.0f),
		VSVertex(-1.0f , 1.0f , 1.0f ,0.0f ,0.0f , 1.0f),
		VSVertex(-1.0f ,-1.0f , 1.0f ,0.0f ,0.0f , 1.0f),
		VSVertex(1.0f,-1.0f , 1.0f ,0.0f ,0.0f , 1.0f),

		//顶面
		VSVertex(-1.0f , 1.0f , 1.0f ,0.0f ,1.0f , 0.0f),
		VSVertex(1.0f , 1.0f , 1.0f ,0.0f ,1.0f , 0.0f),
		VSVertex(1.0f , 1.0f ,-1.0f ,0.0f ,1.0f , 0.0f),
		VSVertex(-1.0f , 1.0f ,-1.0f ,0.0f ,1.0f , 0.0f),

		//底面
		VSVertex(-1.0f ,-1.0f ,-1.0f ,0.0f ,-1.0f , 0.0f),
		VSVertex(1.0f ,-1.0f ,-1.0f ,0.0f ,-1.0f , 0.0f),
		VSVertex(1.0f ,-1.0f , 1.0f ,0.0f ,-1.0f , 0.0f),
		VSVertex(-1.0f ,-1.0f , 1.0f ,0.0f ,-1.0f , 0.0f),

		//左侧
		VSVertex(-1.0f , 1.0f , 1.0f ,-1.0f ,0.0f , 0.0f),
		VSVertex(-1.0f , 1.0f ,-1.0f ,-1.0f ,0.0f , 0.0f),
		VSVertex(-1.0f ,-1.0f ,-1.0f ,-1.0f ,0.0f , 0.0f),
		VSVertex(-1.0f ,-1.0f , 1.0f ,-1.0f ,0.0f , 0.0f),

		//右侧
		VSVertex(1.0f , 1.0f ,-1.0f ,1.0f ,0.0f , 0.0f),
		VSVertex(1.0f , 1.0f , 1.0f ,1.0f ,0.0f , 0.0f),
		VSVertex(1.0f ,-1.0f , 1.0f ,1.0f ,0.0f , 0.0f),
		VSVertex(1.0f ,-1.0f ,-1.0f ,1.0f ,0.0f , 0.0f),
	};

	//设置顶点着色器
	m_d3dDevice->SetVertexShader(g_vshader->mVertexShader);
	//设置顶点声明描述
	m_d3dDevice->SetVertexDeclaration(g_vshader->pVertexDecl);

	//使用像素着色器
	//m_d3dDevice->SetPixelShader(mPixelShader);

	//m_d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//m_d3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	//绘制顶点缓存
	short indexBuffer[] = {
		0,1,2,0,2,3,		//正面
		4,5,6,4,6,7,		//背面
		8,9,10,8,10,11,		//顶面
		12,13,14,12,14,15,	//底面
		16,17,18,16,18,19,	//左面
		20,21,22,20,22,23,	//右面
	};
	m_d3dDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, ARRAYSIZE(indexBuffer), ARRAYSIZE(indexBuffer) / 3, indexBuffer, D3DFMT_INDEX16, vertex, sizeof(VSVertex));
}

void Shader::SetMatrices()
{
	//旋转矩阵
	D3DXMATRIX matWorld;
	SetRotation(&matWorld);
	g_vshader->mVSConstTable->SetMatrix(m_d3dDevice, "matWorld", &matWorld);

	//设置光照
	//D3DXVECTOR4 vLightDir(cosf(timeGetTime() / 350.0f), 0.8f, sinf(timeGetTime() / 350.0f), 1.0f);
	D3DXVECTOR4 vLightDir(1.0f, 1.0f, -1.0f, 1.0f);
	g_vshader->mVSConstTable->SetVector(m_d3dDevice, "vecLightDir", &vLightDir);

	//取景变换矩阵
	D3DXMATRIX matView;
	D3DXVECTOR3 position(0.0f, 2.0f, -4.0f);//摄像机位置
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);//观察点位置
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);//向上的向量
	D3DXMatrixLookAtLH(&matView, &position, &target, &up);

	//投影变换矩阵
	D3DXMATRIX matProj;
	float aspect = (float)(mWidth / mHeight);
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI * 0.5f, aspect, 1.0f, 1000.0f);

	//组合变换
	D3DXMATRIX matWorldViewProj = matWorld * matView * matProj;
	g_vshader->mVSConstTable->SetMatrix(m_d3dDevice, "matWorldViewProj", &matWorldViewProj);
}

//绘制正方形 顶点着色器
void Shader::DrawSquare()
{
	m_d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);//背面消影

	//旋转矩阵
	D3DXMATRIX matWorld, matView, matProj;
	SetRotation(&matWorld);
	if (GetAsyncKeyState('1')) {
		D3DXMatrixIdentity(&matWorld);
	}
	g_vshader->mVSConstTable->SetMatrix(m_d3dDevice, "matWorld", &matWorld);

	//取景变换矩阵
	SetLookAtLH(&matView);
	if (GetAsyncKeyState('2')) {
		D3DXMatrixIdentity(&matView);
	}
	g_vshader->mVSConstTable->SetMatrix(m_d3dDevice, "matView", &matView);

	//投影变换矩阵
	SetPerspectiveFovLH(&matProj);
	if (GetAsyncKeyState('3')) {
		D3DXMatrixIdentity(&matProj);
	}
	g_vshader->mVSConstTable->SetMatrix(m_d3dDevice, "matProj", &matProj);

	D3DXMATRIX matWVP = matWorld * matView * matProj;
	g_vshader->mVSConstTable->SetMatrix(m_d3dDevice, "matWVP", &matWVP);


	//绘制立方体
	//0 1 
	//3 2
	float x = 0.5f, y = 0.5f;
	VS1Vertex vertex[] = {
		VS1Vertex(-x, y,1.0f,COLORF_RED),
		VS1Vertex( x, y,1.0f,COLORF_GREEN),
		VS1Vertex( x,-y,1.0f,COLORF_BLUE),
		VS1Vertex(-x,-y,1.0f,COLORF_WHITE),
	};

	//使用顶点着色器
	m_d3dDevice->SetVertexShader(g_vshader->mVertexShader);

	//设置顶点描述
	m_d3dDevice->SetVertexDeclaration(g_vshader->pVertexDecl);

	//绘制顶点缓存
	short indexBuffer[] = {
		0,1,2,0,2,3,		//正面
	};
	m_d3dDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, ARRAYSIZE(indexBuffer), ARRAYSIZE(indexBuffer) / 3, indexBuffer, D3DFMT_INDEX16, vertex, sizeof(VS1Vertex));
}



void Shader::DrawPrimitiveUPUV1()
{
	m_d3dDevice->SetRenderState(D3DRS_LIGHTING, false);
	//m_d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//旋转矩阵
	D3DXMATRIX matWorld;
	SetRotation(&matWorld);
	if (GetAsyncKeyState('1')) {
		D3DXMatrixIdentity(&matWorld);
	}
	g_pshader->mPSConstTable->SetMatrix(m_d3dDevice, "matWorld", &matWorld);

	//0 1    //0 
	//  2    //3 2
	float x = 0.9f, y = 0.9f;
	float min = 0.0f, max = 1.0f;
	UV1Vertex vertex[] = {
		{-x , y, 1.0f, COLOR_RED	,min,min},
		{ x , y, 1.0f, COLOR_GREEN	,max,min},
		{ x	,-y, 1.0f, COLOR_BLUE	,max,max},
		{-x	, y, 1.0f, COLOR_RED	,min,min},
		{ x	,-y, 1.0f, COLOR_BLUE	,max,max},
		{-x ,-y, 1.0f, COLOR_WHITE	,min,max},
	};

	//使用像素着色器
	m_d3dDevice->SetPixelShader(g_pshader->mPixelShader);

	//使用纹理
	m_d3dDevice->SetTexture(0, mTextureBG1);

	//m_d3dDevice->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	//m_d3dDevice->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

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

	//使用顶点着色器

	//使用像素着色器


	//设置纹理采样
	m_d3dDevice->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_d3dDevice->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

	//顶点格式
	m_d3dDevice->SetFVF(UV2Vertex::FVF);

	//绘制顶点缓存
	short indexBuffer[] = { 0,1,2,3,4,5 };
	m_d3dDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, ARRAYSIZE(indexBuffer), ARRAYSIZE(indexBuffer) / 3, indexBuffer, D3DFMT_INDEX16, vertex, sizeof(UV2Vertex));
}
