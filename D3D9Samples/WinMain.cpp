#include <GameWind.h>
#include "D3D9.h"
#include "SandBox.h"
#include "resource.h"

GameWind* g_wnd;
D3D9* g_d3d9;
SandBox* g_sandBox;
//GameApp* gameApp;//游戏对象

LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	//创建窗口
	g_wnd = windCreate(hInstance, 800, 600, L"D3D9 PixelShader 2.0");

	//创建D3D
	g_d3d9 = new D3D9(g_wnd->mHwnd);

	//初始化
	if (FAILED(g_d3d9->InitD3D())) {
		MessageBox(g_wnd->mHwnd, TEXT("InitD3D初始化失败"), TEXT("错误提示"), MB_OK);
	}


	//初始化对象
	g_sandBox = new SandBox(g_d3d9->m_d3dDevice);
	g_sandBox->mWidth = static_cast<float>(g_wnd->mWidth);
	g_sandBox->mHeight = static_cast<float>(g_wnd->mHeight);
	g_sandBox->Init();
	g_sandBox->SetIndices();
	g_sandBox->SetTexture();
	g_sandBox->SetHumTexture();
	g_sandBox->Shader();

	//对话框
	HWND hAbout = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)About);
	ShowWindow(hAbout, SW_SHOW);
	UpdateWindow(hAbout);

	//游戏循环
	while (g_wnd->ProcessMessage()) {
		g_d3d9->BeginScene();

		//g_sandBox->Draw();
		//g_sandBox->DrawUp();
		//g_sandBox->DrawIndexedUp();
		//g_sandBox->DrawIndexedUpTexture();
		//g_sandBox->DrawIndexedUpHumTexture();
		g_sandBox->DrawIndexedUpHumTextureShader();

		g_d3d9->EndScene();
	}

	//删除对象
	if (g_d3d9 != nullptr)
		delete g_d3d9;

	if (g_wnd != nullptr)
		delete g_wnd;

	return 0;
}



LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
	}
	break;
	case WM_CLOSE:
	{
		PostQuitMessage(1);
		return TRUE;
	}
	}
	return FALSE;
}
