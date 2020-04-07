#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(D3D9* d3d9):Device(d3d9)
{
	m_d3dBuffer = nullptr;		//���㻺����
	m_d3dIndex = nullptr;		//����������
}

void VertexBuffer::Init()
{
	CreateVertex();
	CreateIndices();
}

/*�������㻺��*/
HRESULT VertexBuffer::CreateVertex()
{
	//�������㻺��
	// 0  1
	// 3  2
	float x = 0.5f, y = 0.5f;
	D3Vertex vertex[] = {
		{ -x,  y, 1.0f, COLOR_RED},
		{  x,  y, 1.0f, COLOR_GREEN},
		{  x, -y, 1.0f, COLOR_BLUE},
		{ -x, -y, 1.0f, COLOR_WHITE},
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

//������������
HRESULT VertexBuffer::CreateIndices()
{
	//������������
	short indexBuffer[6] = { 0,1,2,0,2,3 };
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

//����
void VertexBuffer::Draw()
{
	//�رչ���
	m_d3dDevice->SetRenderState(D3DRS_LIGHTING, false);
	m_d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//���ƶ��㻺��
	m_d3dDevice->SetStreamSource(0, m_d3dBuffer, 0, sizeof(D3Vertex));
	m_d3dDevice->SetFVF(D3Vertex::FVF);
	//6����

	//m_d3dDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);

	m_d3dDevice->SetIndices(m_d3dIndex);
	m_d3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 6, 0, 2);
}

//ֱ��ʹ�ö������
void VertexBuffer::DrawPrimitiveUP()
{
	m_d3dDevice->SetRenderState(D3DRS_LIGHTING, false);
	m_d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);//������Ӱ
	//m_d3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);//���ģʽ

	//�������㻺��

	//0 1	//0  
	//  2   //3 2
	float x = 0.5f, y = 0.5f;
	D3Vertex vertex[] = {
		{-x , y, 1.0f, COLOR_RED }, // x, y, z, rhw, color
		{ x	, y, 1.0f, COLOR_GREEN },
		{ x ,-y, 1.0f, COLOR_BLUE },
		{-x	, y, 1.0f, COLOR_RED },
		{ x	,-y, 1.0f, COLOR_BLUE },
		{-x ,-y, 1.0f, COLOR_WHITE },
	};

	//ʹ������

	//���ƶ��㻺��
	m_d3dDevice->SetFVF(D3Vertex::FVF);
	m_d3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, vertex, sizeof(D3Vertex));
}

//ֱ��ʹ�ö��� ��������
void VertexBuffer::DrawIndexedPrimitiveUP()
{
	m_d3dDevice->SetRenderState(D3DRS_LIGHTING, false);
	m_d3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//�������㻺��
	//0 1 
	//3 2
	float x = 0.5f, y = 0.5f;
	D3Vertex vertex[] = {
		{-x , y, 1.0f, COLOR_RED },
		{ x	, y, 1.0f, COLOR_GREEN },
		{ x ,-y, 1.0f, COLOR_BLUE },
		{-x ,-y, 1.0f, COLOR_WHITE },
	};

	//ʹ������

	//���ƶ��㻺��
	m_d3dDevice->SetFVF(D3Vertex::FVF);
	short indexBuffer[6] = { 0,1,2,0,2,3 };
	m_d3dDevice->DrawIndexedPrimitiveUP(
		D3DPT_TRIANGLELIST,					//ͼԪ����
		0,									//
		ARRAYSIZE(indexBuffer),				//�������
		ARRAYSIZE(indexBuffer) / 3,			//ͼԪ����
		indexBuffer,						//������������
		D3DFMT_INDEX16,						//����������ʽ
		vertex,								//��������
		sizeof(D3Vertex)					//һ�鶥��Ĵ�С
	);
}

