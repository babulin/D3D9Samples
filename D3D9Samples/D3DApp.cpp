#include "D3DApp.h"
#include "SandBox.h"
#include "VertexBuffer.h"
#include "Texture.h"
#include "Shader.h"

SandBox* g_sBox;
VertexBuffer* g_vBuff;
Texture* g_texture;
Shader* g_shader;

//当前状态
Samples g_Status = Samples::SHADER;

D3DApp::D3DApp(GameWind* GameWind)
{
	pGameWind = GameWind;
	g_d3d9 = nullptr;
}

HRESULT D3DApp::Init()
{
	//创建D3D
	g_d3d9 = new D3D9(pGameWind);

	//初始化
	if (FAILED(g_d3d9->InitD3D())) {
		MessageBox(pGameWind->mHwnd, TEXT("InitD3D初始化失败"), TEXT("错误提示"), MB_OK);
	}

	switch (g_Status)
	{

	case Samples::VERTEX_BUFFER:
		//------------------------------------
		//顶点缓冲与索引缓冲
		g_vBuff = new VertexBuffer(g_d3d9);
		g_vBuff->CreateVertex();
	case Samples::VERTEX_INDICES_BUFFER:
		g_vBuff = new VertexBuffer(g_d3d9);
		g_vBuff->CreateIndices();
		break;
	case Samples::TEXTURE:
		//------------------------------------
		//纹理贴图
		g_texture = new Texture(g_d3d9);
		g_texture->Init();
		break;
	case Samples::SHADER:
		//------------------------------------
		g_shader = new Shader(g_d3d9);
		g_shader->Init();
		break;
	default:
		break;
	}

	return S_OK;
}

void D3DApp::Render()
{
	g_d3d9->BeginScene();

	switch (g_Status)
	{
	case Samples::VERTEX_BUFFER:
		//绘制
		g_vBuff->DrawVertex();
		//g_vBuff->DrawPrimitiveUP();
		//g_vBuff->DrawIndexedPrimitiveUP();
		break;
	case Samples::VERTEX_INDICES_BUFFER:
		g_vBuff->DrawIndices();
		break;
	case Samples::TEXTURE:
		//绘制
		//g_texture->DrawPrimitiveUPUV1();
		g_texture->DrawIndexedPrimitiveUPUV2x2();
		break;
	case Samples::SHADER:
		//绘制 W S 操作
		g_shader->DrawVSShader();
		//g_shader->DrawSquare();
		//g_shader->DrawPrimitiveUPUV1();
		//g_shader->DrawIndexedPrimitiveUPUV2();
		//g_shader->DrawIndexedPrimitiveUPUV2x2();
		break;
	default:
		break;
	}

	g_d3d9->EndScene();
}

void D3DApp::Clear()
{
	OutputDebugString(TEXT("D3DApp::Clear()析构\n"));

	//删除对象
	if (g_d3d9 != nullptr)
		delete g_d3d9;
}
