#include "D3DApp.h"
#include "SandBox.h"
#include "VertexBuffer.h"
#include "Texture.h"

SandBox* g_sBox;
VertexBuffer* g_vBuff;
Texture* g_texture;

D3DApp::D3DApp(GameWind* wnd)
{
	pWnd = wnd;
	mWidth = static_cast<float>(wnd->mWidth);
	mHeight = static_cast<float>(wnd->mHeight);
}

HRESULT D3DApp::Init()
{
	//创建D3D
	g_d3d9 = new D3D9(pWnd->mHwnd);

	//初始化
	if (FAILED(g_d3d9->InitD3D())) {
		MessageBox(pWnd->mHwnd, TEXT("InitD3D初始化失败"), TEXT("错误提示"), MB_OK);
	}

	//------------------------------------
	//三角形
	g_vBuff = new VertexBuffer(g_d3d9->m_d3dDevice,pWnd->mWidth,pWnd->mHeight);

	//创建顶点
	g_vBuff->Init();

	//------------------------------------
	g_texture = new Texture(g_d3d9->m_d3dDevice, pWnd->mWidth, pWnd->mHeight);
	g_texture->Init();
	return S_OK;
}

void D3DApp::Render()
{
	g_d3d9->BeginScene();

	//绘制
	//g_vBuff->Draw();
	//g_vBuff->DrawPrimitiveUP();
	//g_vBuff->DrawIndexedPrimitiveUP();

	//绘制
	//g_texture->DrawPrimitiveUPUV1();
	//g_texture->DrawIndexedPrimitiveUPUV2();
	g_texture->DrawIndexedPrimitiveUPUV2x2();


	g_d3d9->EndScene();
}

void D3DApp::Clear()
{
	//删除对象
	if (g_d3d9 != nullptr)
		delete g_d3d9;
}
