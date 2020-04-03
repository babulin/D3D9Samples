#include "D3DApp.h"

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
}

void D3DApp::Render()
{

}

void D3DApp::Clear()
{
}
