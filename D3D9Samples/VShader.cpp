#include "VShader.h"
VShader::VShader(D3D9* d3d9):Device(d3d9)
{

}

void VShader::LoadVS(wchar_t file[], LPDIRECT3DVERTEXSHADER9 &mVShader, LPD3DXCONSTANTTABLE &mVSCTable)
{
	//---------------------------------------------------
//������ɫ��
	LPD3DXBUFFER pShader = NULL;
	LPD3DXBUFFER errorBuffer = 0;

	HRESULT hr = D3DXCompileShaderFromFile(file, 0, 0, "vs_main", "vs_3_0", D3DXSHADER_DEBUG, &pShader, &errorBuffer, &mVSCTable);
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

	hr = m_d3dDevice->CreateVertexShader((DWORD*)pShader->GetBufferPointer(), &mVShader);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"CreateVertexShader - failed", 0, 0);
		return;
	}

	pShader->Release();
}

void VShader::VSShader(const wchar_t file[],D3DVERTEXELEMENT9 element[])
{
	//---------------------------------------------------
	LPD3DXBUFFER pShader = NULL;
	LPD3DXBUFFER errorBuffer = 0;

	//������ɫ��
	HRESULT hr = D3DXCompileShaderFromFile(file, 0, 0, "vs_main", "vs_3_0", D3DXSHADER_DEBUG, &pShader, &errorBuffer, &mVSConstTable);
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

	//����������ɫ��
	hr = m_d3dDevice->CreateVertexShader((DWORD*)pShader->GetBufferPointer(), &mVertexShader);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"CreateVertexShader - failed", 0, 0);
		return;
	}

	pShader->Release();

	//-------------------------------------------------------------------------------------
	//������������
	//D3DVERTEXELEMENT9 dec[] = {
	//{0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0},//����λ��
	//{0,12,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_NORMAL,0},//���㷨����
	//D3DDECL_END()//����Ԫ��
	//};

	//��������
	if (FAILED(m_d3dDevice->CreateVertexDeclaration(element, &pVertexDecl))) {
		MessageBox(NULL, L"CreateVertexDeclaration - failed", 0, 0);
		return;
	}
}

void VShader::PSShader(const wchar_t file[])
{
	//---------------------------------------------------
	LPD3DXBUFFER shader = 0;
	LPD3DXBUFFER errorBuffer = 0;

	//������ɫ��
	HRESULT hr = D3DXCompileShaderFromFile(file, 0, 0, "ps_main", "ps_2_0", D3DXSHADER_DEBUG, &shader, &errorBuffer, &mPSConstTable);
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

	//����������ɫ��
	hr = m_d3dDevice->CreatePixelShader((DWORD*)shader->GetBufferPointer(), &mPixelShader);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"CreatePixelShader - failed", 0, 0);
		return;
	}

	shader->Release();
}

void VShader::DrawXYZ()
{
	//����������
	D3Vertex vertex[] = {
		{-10.0f, 0.0f, 0.0f,0x00ff0000},//X - R
		{ 10.0f, 0.0f, 0.0f,0x00ff0000},	//X - R
		{ 0.0f, 10.0f, 0.0f,0x0000ff00},	//Y - G
		{ 0.0f,-10.0 , 0.0f,0x0000ff00},	//Y - G
		{ 0.0f, 0.0f,-10.0f,0x000000ff},	//Z - B
		{ 0.0f, 0.0f, 10.0f,0x000000ff},	//Z - B
		{ 0.0f, 0.0f,  0.0f,0xffffffff},	//LIGHT - B
		{ 1.0f, 1.0f, -10.0f,0xffffffff},	//LIGHT - B
	};

	//m_d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//m_d3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//m_d3dDevice->SetRenderState(D3DRS_LIGHTING, false);

	m_d3dDevice->SetFVF(D3Vertex::FVF);
	//���ƶ��㻺��
	short indexBuffer[] = {
		0,1,//X
		2,3,//Y
		4,5,//Z	
		6,7,//LIGHT
	};
	m_d3dDevice->DrawIndexedPrimitiveUP(D3DPT_LINELIST, 0, ARRAYSIZE(indexBuffer), ARRAYSIZE(indexBuffer)/2, indexBuffer, D3DFMT_INDEX16, vertex, sizeof(D3Vertex));
}

void VShader::DrawVSShader()
{

	//��ת����
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

	//���õ�λ�������
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	matWorld = matWorld * Rx * Ry;
	mVSConstTable->SetMatrix(m_d3dDevice, "matWorld", &matWorld);

	//���ù���
	//D3DXVECTOR4 vLightDir(cosf(timeGetTime() / 350.0f), 0.8f, sinf(timeGetTime() / 350.0f), 1.0f);
	D3DXVECTOR4 vLightDir(1.0f, 1.0f, -1.0f, 1.0f);
	mVSConstTable->SetVector(m_d3dDevice, "vecLightDir", &vLightDir);

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
	mVSConstTable->SetMatrix(m_d3dDevice, "matWorldViewProj", &matWorldViewProj);

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
	m_d3dDevice->SetVertexShader(mVertexShader);
	//���ö�����������
	m_d3dDevice->SetVertexDeclaration(pVertexDecl);

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
