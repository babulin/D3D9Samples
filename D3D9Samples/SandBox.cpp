#include "SandBox.h"
#include<iostream>
#include<fstream>
using std::ofstream;
using std::ios;

SandBox::SandBox(LPDIRECT3DDEVICE9 p_d3dDevice)
{
	m_d3dDevice = p_d3dDevice;
}

void SandBox::PSShader01()
{
	//������ɫ��
	LPD3DXBUFFER shader = 0;
	LPD3DXBUFFER errorBuffer = 0;

	HRESULT hr = D3DXCompileShaderFromFile(L"PixelShader_01.hlsl", 0, 0, "main", "ps_3_0", D3DXSHADER_DEBUG, &shader, &errorBuffer, &mPSConstTable);
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

void SandBox::DrawIndexedUpHumTextureShader()
{
	//SetUpMatrices();

	//�������㻺��
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

	//ʹ��������ɫ��
	float color[4] = { 1.0f,1.0f,1.0f,1.0f };
	m_d3dDevice->SetPixelShaderConstantF(0, color, 4);

	float color1[4] = { 0.0f,0.0f,1.0f,1.0f };
	m_d3dDevice->SetPixelShaderConstantF(4, color1, 4);

	m_d3dDevice->SetPixelShader(mPixelShader);

	//ʹ������
	m_d3dDevice->SetTexture(0, m_Texture);
	m_d3dDevice->SetTexture(1, m_Texture_2x2);

	m_d3dDevice->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_d3dDevice->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

	//���ƶ��㻺��
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

	//ʹ��������ɫ��
	m_d3dDevice->SetPixelShader(mPixelShader);
	
}

void SandBox::SetUpMatrices()
{
	///�Ĵ�任֮һ������任���������
	///ƽ�Ʊ任
	//D3DXMATRIX T1;
	//D3DXMatrixTranslation(&T1, -0.5f, 0.5f, 0.5f);
	//m_d3dDevice->SetTransform(D3DTS_WORLD, &T1);

	///�Ĵ�任֮����ȡ���任���������
	//D3DXMATRIX matView;
	//D3DXVECTOR3 position(0.0f, 0.0f, -1.5f);//�����λ��
	//D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);//�۲��λ��
	//D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);//���ϵ�����
	//D3DXMatrixLookAtLH(&matView, &position, &target, &up);
	//m_d3dDevice->SetTransform(D3DTS_VIEW, &matView);

	///�Ĵ�任֮����ͶӰ�任���������
	//͸��ͶӰ����
	//D3DXMATRIX proj;
	//float aspect = (float)(mWidth / mHeight);
	//D3DXMatrixPerspectiveFovLH(&proj, D3DX_PI * 0.5f, aspect, 1.0f, 1000.0f);
	//m_d3dDevice->SetTransform(D3DTS_PROJECTION, &proj);

	///�Ĵ�任֮�ģ��ӿڱ任������
	//D3DVIEWPORT9 vp;
	//vp.X = 0;
	//vp.Y = 0;
	//vp.Width = mWidth/2;//�ӿڵĿ��
	//vp.Height = mHeight/2;//�ӿڵĸ߶�
	//vp.MinZ = 0.0;
	//vp.MaxZ = 1.0;
	//m_d3dDevice->SetViewport(&vp);
}
