#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(LPDIRECT3DDEVICE9 d3dDevice, int width, int height)
{
	m_d3dDevice = d3dDevice;
	mWidth = width;
	mHeight = height;
}

HRESULT VertexBuffer::CreateVertex()
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

HRESULT VertexBuffer::CreateIndices()
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

void VertexBuffer::Draw()
{
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
