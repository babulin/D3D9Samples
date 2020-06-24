#include "Shader.h"

Shader::Shader(D3D9* d3d9):Texture(d3d9)
{
	//����shader
	g_vshader = new VShader(d3d9);
	g_vsSample = new VShader(d3d9);
	g_pshader = new VShader(d3d9);
	g_ps2hader = new VShader(d3d9);
}

Shader::~Shader()
{
	if (g_vshader != nullptr)
	{
		delete g_vshader;
	}
	if (g_vsSample != nullptr)
	{
		delete g_vsSample;
	}

	if (g_pshader != nullptr)
	{
		delete g_pshader;
	}	
	
	if (g_ps2hader != nullptr)
	{
		delete g_ps2hader;
	}
}

void Shader::Init()
{
	CreateTexture();
	CreateTexture1x1();
	CreateTexture2x2();

	//��ʼ����ɫ��
	//g_vshader->VSShader(L"VertexShader.hlsl");

	//-------------------------------------------------------------------------------------
	//������������ ��������
	D3DVERTEXELEMENT9 element01[] = {
		{0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0},//����λ��
		{0,12,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_NORMAL,0},//���㷨����
		D3DDECL_END()//����Ԫ��
	};
	g_vsSample->VSShader(L"VertexShader.hlsl", element01);

	//����
	D3DXVECTOR4 vMtrlAmbient(1.0f, 1.0f, 1.0f, 1.0f);//��������
	D3DXVECTOR4 vMtrlDiffuse(1.0f, 1.0f, 1.0f, 1.0f);//��������
	g_vsSample->mVSConstTable->SetVector(m_d3dDevice, "mtrlAmbient", &vMtrlAmbient);
	g_vsSample->mVSConstTable->SetVector(m_d3dDevice, "mtrlDiffuse", &vMtrlDiffuse);

	//-------------------------------------------------------------------------------------
	//������������ �������Ρ�
	D3DVERTEXELEMENT9 element[] = {
		{0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0},//����λ��
		{0,12,D3DDECLTYPE_FLOAT4,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_COLOR,0},//��������ɫ
		D3DDECL_END()//����Ԫ��
	};
	g_vshader->VSShader(L"VS01_Shader.hlsl", element);


	//--------------------------------------------------------------------------------------
	//������ͼ
	g_pshader->PSShader(L"PS01_Shader.hlsl");

	//--------------------------------------------------------------------------------------
	//������ͼ2
	g_ps2hader->PSShader(L"PS02_Shader.hlsl");
}

void Shader::SetMatrices()
{
	//��ת����
	D3DXMATRIX matWorld, matTs;
	SetRotation(&matWorld, nullptr,&matTs);
	matWorld = matWorld * matTs;
	g_vsSample->mVSConstTable->SetMatrix(m_d3dDevice, "matWorld", &matWorld);
	

	//���ù���
	//D3DXVECTOR4 vLightDir(cosf(timeGetTime() / 350.0f), 0.8f, sinf(timeGetTime() / 350.0f), 1.0f);
	D3DXVECTOR4 vLightDir(0.0f, 1.0f, 1.0f, 1.0f);
	g_vsSample->mVSConstTable->SetVector(m_d3dDevice, "vecLightDir", &vLightDir);

	//ȡ���任����
	D3DXMATRIX matView;
	D3DXVECTOR3 position(0.0f, 2.0f, -4.0f);//�����λ��
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);//�۲��λ��
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);//���ϵ�����
	D3DXMatrixLookAtLH(&matView, &position, &target, &up);

	//ͶӰ�任����
	D3DXMATRIX matProj;
	float aspect = (float)(mWidth / mHeight);
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI * 0.5f, aspect, 1.0f, 1000.0f);

	//��ϱ任
	D3DXMATRIX matWorldViewProj = matWorld * matView * matProj;
	g_vsSample->mVSConstTable->SetMatrix(m_d3dDevice, "matWorldViewProj", &matWorldViewProj);
}

void Shader::DrawVSShader()
{
	//���ó���
	SetMatrices();

	//����������
	VSVertex vertex[] = {
		//����
		VSVertex(-1.0f , 1.0f ,-1.0f ,0.0f ,0.0f ,-1.0f),
		VSVertex(1.0f , 1.0f ,-1.0f ,0.0f ,0.0f ,-1.0f),
		VSVertex(1.0f ,-1.0f ,-1.0f ,0.0f ,0.0f ,-1.0f),
		VSVertex(-1.0f ,-1.0f ,-1.0f ,0.0f ,0.0f ,-1.0f),

		//����
		VSVertex(1.0f , 1.0f , 1.0f ,0.0f ,0.0f , 1.0f),
		VSVertex(-1.0f , 1.0f , 1.0f ,0.0f ,0.0f , 1.0f),
		VSVertex(-1.0f ,-1.0f , 1.0f ,0.0f ,0.0f , 1.0f),
		VSVertex(1.0f,-1.0f , 1.0f ,0.0f ,0.0f , 1.0f),

		//����
		VSVertex(-1.0f , 1.0f , 1.0f ,0.0f ,1.0f , 0.0f),
		VSVertex(1.0f , 1.0f , 1.0f ,0.0f ,1.0f , 0.0f),
		VSVertex(1.0f , 1.0f ,-1.0f ,0.0f ,1.0f , 0.0f),
		VSVertex(-1.0f , 1.0f ,-1.0f ,0.0f ,1.0f , 0.0f),

		//����
		VSVertex(-1.0f ,-1.0f ,-1.0f ,0.0f ,-1.0f , 0.0f),
		VSVertex(1.0f ,-1.0f ,-1.0f ,0.0f ,-1.0f , 0.0f),
		VSVertex(1.0f ,-1.0f , 1.0f ,0.0f ,-1.0f , 0.0f),
		VSVertex(-1.0f ,-1.0f , 1.0f ,0.0f ,-1.0f , 0.0f),

		//���
		VSVertex(-1.0f , 1.0f , 1.0f ,-1.0f ,0.0f , 0.0f),
		VSVertex(-1.0f , 1.0f ,-1.0f ,-1.0f ,0.0f , 0.0f),
		VSVertex(-1.0f ,-1.0f ,-1.0f ,-1.0f ,0.0f , 0.0f),
		VSVertex(-1.0f ,-1.0f , 1.0f ,-1.0f ,0.0f , 0.0f),

		//�Ҳ�
		VSVertex(1.0f , 1.0f ,-1.0f ,1.0f ,0.0f , 0.0f),
		VSVertex(1.0f , 1.0f , 1.0f ,1.0f ,0.0f , 0.0f),
		VSVertex(1.0f ,-1.0f , 1.0f ,1.0f ,0.0f , 0.0f),
		VSVertex(1.0f ,-1.0f ,-1.0f ,1.0f ,0.0f , 0.0f),
	};

	//���ö�����ɫ��
	m_d3dDevice->SetVertexShader(g_vsSample->mVertexShader);
	//���ö�����������
	m_d3dDevice->SetVertexDeclaration(g_vsSample->pVertexDecl);

	//ʹ��������ɫ��
	//m_d3dDevice->SetPixelShader(mPixelShader);

	//m_d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//m_d3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	//���ƶ��㻺��
	short indexBuffer[] = {
		0,1,2,0,2,3,		//����
		4,5,6,4,6,7,		//����
		8,9,10,8,10,11,		//����
		12,13,14,12,14,15,	//����
		16,17,18,16,18,19,	//����
		20,21,22,20,22,23,	//����
	};
	m_d3dDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, ARRAYSIZE(indexBuffer), ARRAYSIZE(indexBuffer) / 3, indexBuffer, D3DFMT_INDEX16, vertex, sizeof(VSVertex));
}

//���������� ������ɫ��
void Shader::DrawSquare()
{
	m_d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);//������Ӱ

	//��ת����
	D3DXMATRIX matWorld, matView, matProj,matTs;
	float matTran[4];
	SetRotation(&matWorld,matTran, &matTs);
	//matWorld = matWorld * matTs;//ƽ��
	if (GetAsyncKeyState('1')) {
		D3DXMatrixIdentity(&matWorld);
	}
	g_vshader->mVSConstTable->SetMatrix(m_d3dDevice, "matWorld", &matWorld);
	g_vshader->mVSConstTable->SetFloatArray(m_d3dDevice, "matTran", matTran, 4);

	//ȡ���任����
	SetLookAtLH(&matView);
	if (GetAsyncKeyState('2')) {
		D3DXMatrixIdentity(&matView);
	}
	g_vshader->mVSConstTable->SetMatrix(m_d3dDevice, "matView", &matView);

	//ͶӰ�任����
	SetPerspectiveFovLH(&matProj);
	if (GetAsyncKeyState('3')) {
		D3DXMatrixIdentity(&matProj);
	}
	g_vshader->mVSConstTable->SetMatrix(m_d3dDevice, "matProj", &matProj);

	D3DXMATRIX matWVP = matWorld * matView * matProj;
	g_vshader->mVSConstTable->SetMatrix(m_d3dDevice, "matWVP", &matWVP);


	//����������
	//0 1 
	//3 2
	float x = 0.5f, y = 0.5f;
	VS1Vertex vertex[] = {
		VS1Vertex(-x, y,1.0f,COLORF_RED),
		VS1Vertex( x, y,1.0f,COLORF_GREEN),
		VS1Vertex( x,-y,1.0f,COLORF_BLUE),
		VS1Vertex(-x,-y,1.0f,COLORF_WHITE),
	};

	//ʹ�ö�����ɫ��
	m_d3dDevice->SetVertexShader(g_vshader->mVertexShader);

	//���ö�������
	m_d3dDevice->SetVertexDeclaration(g_vshader->pVertexDecl);

	//���ƶ��㻺��
	short indexBuffer[] = {
		0,1,2,0,2,3,		//����
	};
	m_d3dDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, ARRAYSIZE(indexBuffer), ARRAYSIZE(indexBuffer) / 3, indexBuffer, D3DFMT_INDEX16, vertex, sizeof(VS1Vertex));
}

void Shader::DrawPrimitiveUPUV1()
{
	m_d3dDevice->SetRenderState(D3DRS_LIGHTING, false);
	//m_d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//��ת����
	D3DXMATRIX matWorld, matTs;
	//float4 ����
	float matTran[4];

	SetRotation(&matWorld,matTran,&matTs);
	//matWorld = matWorld * matTs;//ƽ��
	if (GetAsyncKeyState('1')) {
		D3DXMatrixIdentity(&matWorld);
	}
	g_pshader->mPSConstTable->SetMatrix(m_d3dDevice, "matWorld", &matWorld);
	g_pshader->mPSConstTable->SetFloatArray(m_d3dDevice, "matTran", matTran,4);

	//ColorMatrix cmat(matWorld,matTran);
	//g_pshader->mPSConstTable->SetValue(m_d3dDevice, "ColorMatrix", &cmat,sizeof(cmat));

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

	//ʹ��������ɫ��
	m_d3dDevice->SetPixelShader(g_pshader->mPixelShader);

	//ʹ������
	m_d3dDevice->SetTexture(0, mTextureBG1);

	//m_d3dDevice->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	//m_d3dDevice->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

	//���ƶ��㻺��
	m_d3dDevice->SetFVF(UV1Vertex::FVF);
	m_d3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, vertex, sizeof(UV1Vertex));
}

void Shader::DrawIndexedPrimitiveUPUV2()
{
	m_d3dDevice->SetRenderState(D3DRS_LIGHTING, false);
	m_d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//��ת����
	D3DXMATRIX matWorld, matTs;
	//float4 ����
	float matTran[4];

	SetRotation(&matWorld, matTran, &matTs);
	//matWorld = matWorld * matTs;//ƽ��
	if (GetAsyncKeyState('1')) {
		D3DXMatrixIdentity(&matWorld);
	}
	g_ps2hader->mPSConstTable->SetMatrix(m_d3dDevice, "matWorld", &matWorld);
	g_ps2hader->mPSConstTable->SetFloatArray(m_d3dDevice, "matTran", matTran, 4);

	//0 1    //0 
	//  2    //3 2
	float x = 0.8f, y = 0.8f;
	float min = 0.0f, max = 1.0f, min1 = 0.0f, max1 = 1.0f;
	UV2Vertex vertex[] = {
		{-x , y, 1.0f, COLOR_RED	,min,min,min1,min1},
		{ x , y, 1.0f, COLOR_WHITE	,max,min,max1,min1},
		{ x	,-y, 1.0f, COLOR_WHITE	,max,max,max1,max1},
		{-x	, y, 1.0f, COLOR_RED	,min,min,min1,min1},
		{ x	,-y, 1.0f, COLOR_WHITE	,max,max,max1,max1},
		{-x ,-y, 1.0f, COLOR_WHITE	,min,max,min1,max1},
	};

	//ʹ��������ɫ��
	m_d3dDevice->SetPixelShader(g_ps2hader->mPixelShader);

	//ʹ������
	m_d3dDevice->SetTexture(0, mTextureBG1);
	m_d3dDevice->SetTexture(1, mTextureP1);

	//�����ʽ
	m_d3dDevice->SetFVF(UV2Vertex::FVF);

	//���ƶ��㻺��
	short indexBuffer[] = { 0,1,2,3,4,5 };
	m_d3dDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, ARRAYSIZE(indexBuffer), ARRAYSIZE(indexBuffer) / 3, indexBuffer, D3DFMT_INDEX16, vertex, sizeof(UV2Vertex));
}

void Shader::DrawIndexedPrimitiveUPUV2x2()
{
	m_d3dDevice->SetRenderState(D3DRS_LIGHTING, false);
	m_d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//0 1    //0 
	//  2    //3 2
	float x = 0.5f, y = 0.5f;
	float min = 0.0f, max = 1.0f, min1 = 0.25f, max1 = 0.75f;
	UV2Vertex vertex[] = {
		{-x , y, 1.0f, COLOR_WHITE	,min,min,min1,min1},
		{ x , y, 1.0f, COLOR_WHITE	,max,min,max1,min1},
		{ x	,-y, 1.0f, COLOR_WHITE	,max,max,max1,max1},
		{-x	, y, 1.0f, COLOR_WHITE	,min,min,min1,min1},
		{ x	,-y, 1.0f, COLOR_WHITE	,max,max,max1,max1},
		{-x ,-y, 1.0f, COLOR_WHITE	,min,max,min1,max1},
	};
	//��ʹ��������ɫ��
	m_d3dDevice->SetPixelShader(nullptr);

	//ʹ������
	m_d3dDevice->SetTexture(0, mTextureBG1);
	m_d3dDevice->SetTexture(1, mTexture2x2);

	//�����������
	m_d3dDevice->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_d3dDevice->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

	//�����ʽ
	m_d3dDevice->SetFVF(UV2Vertex::FVF);

	//���ƶ��㻺��
	short indexBuffer[] = { 0,1,2,3,4,5 };
	m_d3dDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, ARRAYSIZE(indexBuffer), ARRAYSIZE(indexBuffer) / 3, indexBuffer, D3DFMT_INDEX16, vertex, sizeof(UV2Vertex));
}
