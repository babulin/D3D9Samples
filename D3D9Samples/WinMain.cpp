#include <GameWind.h>
#include "D3DApp.h"

#include "D3D9.h"
#include "SandBox.h"
#include "ShaderBox.h" 
#include "resource.h"
#include <CommCtrl.h>

GameWind* g_wnd;
D3DApp* g_d3dApp;

SandBox* g_sandBox;
ShaderBox* g_sBox;
//GameApp* gameApp;//游戏对象
static MYCOLOR color = { 0,0,0 };

LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	//创建窗口
	g_wnd = windCreate(hInstance, 800, 600, L"D3D9 PixelShader 2.0");

	//创建应用程序
	g_d3dApp = new D3DApp(g_wnd);
	if (FAILED(g_d3dApp->Init())) {
		MessageBox(g_wnd->mHwnd, TEXT("D3DApp初始化失败"), TEXT("错误提示"), MB_OK);
	}

	

	////初始化对象
	//g_sandBox = new SandBox(g_d3d9->m_d3dDevice);
	//g_sandBox->mWidth = static_cast<float>(g_wnd->mWidth);
	//g_sandBox->mHeight = static_cast<float>(g_wnd->mHeight);

	//g_sandBox->Init();
	//g_sandBox->SetIndices();
	//g_sandBox->SetTexture();
	//g_sandBox->SetHumTexture();
	//g_sandBox->PSShader01();
	//g_sandBox->SetTexture2X2();
	
	//初始化渲染box
	//g_sBox = new ShaderBox(g_d3d9->m_d3dDevice, g_wnd->mWidth, g_wnd->mHeight);
	
	//加载着色器
	//LPDIRECT3DVERTEXSHADER9 mVShader = NULL;
	//LPD3DXCONSTANTTABLE mVSCTable = NULL;
	//wchar_t file[] = TEXT("VSxyz.hlsl");
	//g_sBox->LoadVS(file, mVShader, mVSCTable);

	//着色器
	//g_sBox->VSShader();

	//对话框
	//HWND hAbout = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)About);
	//ShowWindow(hAbout, SW_SHOW);
	//UpdateWindow(hAbout);

	//游戏循环
	while (g_wnd->ProcessMessage()) {

		g_d3dApp->Render();
		//g_d3d9->BeginScene();

		//g_sandBox->Draw();
		//g_sandBox->DrawUp();
		//g_sandBox->DrawIndexedUp();
		//g_sandBox->DrawIndexedUpTexture();
		//g_sandBox->DrawIndexedUpHumTexture();
		//g_sandBox->DrawIndexedUpHumTextureShader();

		//g_sBox->DrawXYZ();
		//g_sBox->DrawVSShader();
		
		//g_d3d9->EndScene();
	}

	g_d3dApp->Clear();
	//删除对象
	if (g_d3d9 != nullptr)
		delete g_d3d9;

	if (g_wnd != nullptr)
		delete g_wnd;

	return 0;
}



LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hWndSlider1 = nullptr;
	static HWND hWndSlider2 = nullptr;
	static HWND hWndSlider3 = nullptr;

	switch (message)
	{
		case WM_INITDIALOG:{
			hWndSlider1 = GetDlgItem(hDlg, IDC_SLIDER1); //m_hWnd为父窗口的句柄
			SendMessageW(hWndSlider1, TBM_SETRANGE, TRUE, (LPARAM)MAKELONG(0, 255));//设置0-255

			hWndSlider2 = GetDlgItem(hDlg, IDC_SLIDER2); //m_hWnd为父窗口的句柄
			SendMessageW(hWndSlider2, TBM_SETRANGE, TRUE, (LPARAM)MAKELONG(0, 255));//设置0-255

			hWndSlider3 = GetDlgItem(hDlg, IDC_SLIDER3); //m_hWnd为父窗口的句柄
			SendMessageW(hWndSlider3, TBM_SETRANGE, TRUE, (LPARAM)MAKELONG(0, 255));//设置0-255
			return TRUE;
		}
		case WM_COMMAND:
		{
			if (LOWORD(wParam) == IDC_BUTTON1)
			{
				OutputDebugString(L"按钮事件");
				return TRUE;
			}
			break;
		}
		case WM_HSCROLL:
		{
			color.R = (LONG)SendMessageW(hWndSlider1, TBM_GETPOS, 0, 0); //value即是当前控件的值
			color.G = (LONG)SendMessageW(hWndSlider2, TBM_GETPOS, 0, 0); //value即是当前控件的值
			color.B = (LONG)SendMessageW(hWndSlider3, TBM_GETPOS, 0, 0); //value即是当前控件的值

			wchar_t buf[50] = {};
			swprintf_s(buf, L"R:%d,G:%d,B:%d\n", color.R, color.G, color.B);
			OutputDebugString(buf);
			break;
		}
		case WM_CLOSE:
		{
			PostQuitMessage(1);
			return TRUE;
		}
	}
	return FALSE;
}
