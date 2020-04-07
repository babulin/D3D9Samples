#include <GameWind.h>
#include "D3DApp.h"
#include <CommCtrl.h>

GameWind* g_wnd;
D3DApp* g_d3dApp;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	//创建窗口
	g_wnd = windCreate(hInstance, 800, 600, L"D3D9 PixelShader 2.0");

	//创建应用程序
	g_d3dApp = new D3DApp(g_wnd);
	if (FAILED(g_d3dApp->Init())) {
		MessageBox(g_wnd->mHwnd, TEXT("D3DApp初始化失败"), TEXT("错误提示"), MB_OK);
	}

	//游戏循环
	while (g_wnd->ProcessMessage()) {
		g_d3dApp->Render();
	}

	g_d3dApp->Clear();

	if (g_d3dApp != nullptr)
	{
		delete g_d3dApp;
	}

	if (g_wnd != nullptr) {
		delete g_wnd;
	}

	return 0;
}