#include "D3DApp.h"
#include "SandBox.h"
#include "VertexBuffer.h"
#include "Texture.h"
#include "Shader.h"

SandBox* g_sBox;
VertexBuffer* g_vBuff;
Texture* g_texture;
Shader* g_shader;

//��ǰ״̬
Samples g_Status = Samples::VERTEX_INDICES_BUFFER;

D3DApp::D3DApp(GameWind* GameWind)
{
	pGameWind = GameWind;
	g_d3d9 = nullptr;
}

HRESULT D3DApp::Init()
{
	//����D3D
	g_d3d9 = new D3D9(pGameWind);

	//��ʼ��
	if (FAILED(g_d3d9->InitD3D())) {
		MessageBox(pGameWind->mHwnd, TEXT("InitD3D��ʼ��ʧ��"), TEXT("������ʾ"), MB_OK);
	}


	switch (g_Status)
	{

	case Samples::VERTEX_BUFFER:
		//------------------------------------
		//���㻺������������
		g_vBuff = new VertexBuffer(g_d3d9);
		g_vBuff->CreateVertex();
	case Samples::VERTEX_INDICES_BUFFER:
		g_vBuff = new VertexBuffer(g_d3d9);
		g_vBuff->CreateIndices();
		break;
	default:
		break;
	}


	//------------------------------------
	//������ͼ
	//g_texture = new Texture(g_d3d9);
	//g_texture->Init();

	//------------------------------------
	//g_shader = new Shader(g_d3d9);
	//g_shader->Init();

	return S_OK;
}

void D3DApp::Render()
{
	g_d3d9->BeginScene();



	//����
	//g_texture->DrawPrimitiveUPUV1();
	//g_texture->DrawIndexedPrimitiveUPUV2();
	switch (g_Status)
	{
	case Samples::VERTEX_BUFFER:
		//����
		g_vBuff->DrawVertex();
		//g_vBuff->DrawPrimitiveUP();
		//g_vBuff->DrawIndexedPrimitiveUP();
		break;
	case Samples::VERTEX_INDICES_BUFFER:
		g_vBuff->DrawIndices();
		break;
	default:
		break;
	}
	//g_texture->DrawIndexedPrimitiveUPUV2x2();

	//����
	//g_shader->DrawVSShader();
	//g_shader->DrawSquare();
<<<<<<< .mine
	//g_shader->DrawPrimitiveUPUV1();
	//g_shader->DrawIndexedPrimitiveUPUV2();
	//g_shader->DrawIndexedPrimitiveUPUV2x2();
=======
	//g_shader->DrawPrimitiveUPUV1();
	g_shader->DrawIndexedPrimitiveUPUV2();
	g_shader->DrawIndexedPrimitiveUPUV2x2();
>>>>>>> .theirs

	g_d3d9->EndScene();
}

void D3DApp::Clear()
{
	OutputDebugString(TEXT("D3DApp::Clear()����\n"));

	//ɾ������
	if (g_d3d9 != nullptr)
		delete g_d3d9;
}
