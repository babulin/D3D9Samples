#include <GameWind.h>
#include "D3DApp.h"

#include "D3D9.h"
#include "SandBox.h"
#include "ShaderBox.h" 
#include <CommCtrl.h>

GameWind* g_wnd;
D3DApp* g_d3dApp;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	//��������
	g_wnd = windCreate(hInstance, 800, 600, L"D3D9 PixelShader 2.0");

	//����Ӧ�ó���
	g_d3dApp = new D3DApp(g_wnd);
	if (FAILED(g_d3dApp->Init())) {
		MessageBox(g_wnd->mHwnd, TEXT("D3DApp��ʼ��ʧ��"), TEXT("������ʾ"), MB_OK);
	}

	//��Ϸѭ��
	while (g_wnd->ProcessMessage()) {
		g_d3dApp->Render();
	}

	g_d3dApp->Clear();


	if (g_wnd != nullptr)
		delete g_wnd;

	return 0;
}