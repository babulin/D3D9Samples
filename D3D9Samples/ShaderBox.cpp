#include "ShaderBox.h"

ShaderBox::ShaderBox(LPDIRECT3DDEVICE9 d3dDevice,int width,int height)
{
	m_d3dDevice = d3dDevice;
	mWidth = static_cast<float>(width);
	mHeight = static_cast<float>(height);
}

void ShaderBox::VSShader()
{
	//---------------------------------------------------
	//创建着色器
	LPD3DXBUFFER pShader = NULL;
	LPD3DXBUFFER errorBuffer = 0;

	HRESULT hr = D3DXCompileShaderFromFile(L"VertexShader.hlsl", 0, 0, "vs_main", "vs_3_0", D3DXSHADER_DEBUG, &pShader, &errorBuffer, &mVSConstTable);
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

	//获取常量
	//D3DXHANDLE hWorldViewProjMatrix;
	//hWorldViewProjMatrix = mVSConstTable->GetConstantByName(NULL,"WorldViewProjMatrix");
	//if (hWorldViewProjMatrix == NULL)
	//{
	//	MessageBox(NULL, L"获取常量 - failed", 0, 0);
	//	return;
	//}

	//获取常量设置
	//D3DXHANDLE hBGCOLOR = mVSConstTable->GetConstantByName(NULL,"BGCOLOR");
	//D3DXHANDLE bgColor = mVSConstTable->GetConstantByName(hBGCOLOR,"Color");
	//float fColor[4] = { 1.0f,0.0f,0.0f,1.0f };
	//mVSConstTable->SetFloatArray(m_d3dDevice, bgColor, fColor, 4);


	//按索引获取句柄
	//pConstTable->GetConstant(NULL, 0);
	//pConstTable->GetConstantElement(NULL, 0);


	hr = m_d3dDevice->CreateVertexShader((DWORD*)pShader->GetBufferPointer(), &mVertexShader);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"CreateVertexShader - failed", 0, 0);
		return;
	}

	pShader->Release();

	//-------------------------------------------------------------------------------------
	//创建声明顶点
	D3DVERTEXELEMENT9 dec[] = {
	{0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0},//顶点位置
	{0,12,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_NORMAL,0},//顶点法向量
	D3DDECL_END()//结束元素
	};

	//顶点声明
	if (FAILED(m_d3dDevice->CreateVertexDeclaration(dec, &pVertexDecl))) {
		MessageBox(NULL, L"CreateVertexDeclaration - failed", 0, 0);
		return;
	}

	//设置
	D3DXVECTOR4 vMtrlAmbient(1.0f, 1.0f, 1.0f, 1.0f);//环境光
	D3DXVECTOR4 vMtrlDiffuse(1.0f, 1.0f, 1.0f, 1.0f);//漫反射
	mVSConstTable->SetVector(m_d3dDevice, "mtrlAmbient", &vMtrlAmbient);
	mVSConstTable->SetVector(m_d3dDevice, "mtrlDiffuse", &vMtrlDiffuse);
}

void ShaderBox::PSShader()
{
	//创建着色器
	LPD3DXBUFFER shader = 0;
	LPD3DXBUFFER errorBuffer = 0;

	HRESULT hr = D3DXCompileShaderFromFile(L"PixelShader.hlsl", 0, 0, "ps_main", "ps_3_0", D3DXSHADER_DEBUG, &shader, &errorBuffer, &mPSConstTable);
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
}

void ShaderBox::DrawXYZ()
{

	//绘制立方体
	D3Vertex vertex[] = {
		{-10.0f, 0.0f, 0.0f,0x00ff0000},//X - R
		{ 10.0f, 0.0f, 0.0f,0x00ff0000},	//X - R
		{ 0.0f, 10.0f, 0.0f,0x0000ff00},	//Y - G
		{ 0.0f,-10.0 , 0.0f,0x0000ff00},	//Y - G
		{ 0.0f, 0.0f,-10.0f,0x000000ff},	//Z - B
		{ 0.0f, 0.0f, 10.0f,0x000000ff},	//Z - B
	};

	//使用像素着色器
	//m_d3dDevice->SetPixelShader(mPixelShader);

	//m_d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//m_d3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_d3dDevice->SetRenderState(D3DRS_LIGHTING, false);

	m_d3dDevice->SetFVF(D3Vertex::FVF);
	//绘制顶点缓存
	short indexBuffer[] = {
		0,1,//X
		2,3,//Y
		4,5,//Z	
	};
	m_d3dDevice->DrawIndexedPrimitiveUP(D3DPT_LINELIST, 0, 6, 3, indexBuffer, D3DFMT_INDEX16, vertex, sizeof(D3Vertex));
}

void ShaderBox::DrawVSShader()
{

	//旋转矩阵
	D3DXMATRIX Rx, Ry;
	static float Vx = 0.0f, Vy = 0.0f;
	if (GetAsyncKeyState('W')) {
		Vx += 0.01f;
	}
	if (GetAsyncKeyState('S')) {
		Vx -= 0.01f;
	}
	if (Vx > 6.28f) {
		Vx = 0.0f;
	}

	D3DXMatrixRotationX(&Rx, Vx);

	if (GetAsyncKeyState('A')) {
		Vy += 0.01f;
	}
	if (GetAsyncKeyState('D')) {
		Vy -= 0.01f;
	}
	if (Vy > 6.28f) {
		Vy = 0.0f;
	}
	D3DXMatrixRotationY(&Ry, Vy);

	//设置单位世界矩阵
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	matWorld = matWorld * Rx * Ry;
	mVSConstTable->SetMatrix(m_d3dDevice, "matWorld", &matWorld);

	//设置光照
	//D3DXVECTOR4 vLightDir(cosf(timeGetTime() / 350.0f), 0.8f, sinf(timeGetTime() / 350.0f), 1.0f);
	D3DXVECTOR4 vLightDir(1.0f, 1.0f, -1.0f, 1.0f);
	mVSConstTable->SetVector(m_d3dDevice, "vecLightDir", &vLightDir);

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
	mVSConstTable->SetMatrix(m_d3dDevice, "matWorldViewProj", &matWorldViewProj);

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
	m_d3dDevice->SetVertexShader(mVertexShader);
	//设置顶点声明描述
	m_d3dDevice->SetVertexDeclaration(pVertexDecl);

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
