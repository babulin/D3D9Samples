#include <GameWind.h>
#include "D3D9.h"
#include "SandBox.h"
#include "resource.h"
#include <CommCtrl.h>

GameWind* g_wnd;
D3D9* g_d3d9;
SandBox* g_sandBox;
//GameApp* gameApp;//��Ϸ����
static MYCOLOR color = { 0,0,0 };

LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	//��������
	g_wnd = windCreate(hInstance, 800, 600, L"D3D9 PixelShader 2.0");

	//����D3D
	g_d3d9 = new D3D9(g_wnd->mHwnd);

	//��ʼ��
	if (FAILED(g_d3d9->InitD3D())) {
		MessageBox(g_wnd->mHwnd, TEXT("InitD3D��ʼ��ʧ��"), TEXT("������ʾ"), MB_OK);
	}


	//��ʼ������
	g_sandBox = new SandBox(g_d3d9->m_d3dDevice);
	g_sandBox->mWidth = static_cast<float>(g_wnd->mWidth);
	g_sandBox->mHeight = static_cast<float>(g_wnd->mHeight);
	g_sandBox->Init();
	g_sandBox->SetIndices();
	g_sandBox->SetTexture();
	g_sandBox->SetHumTexture();
	g_sandBox->VSShader();
	g_sandBox->PSShader();
	//g_sandBox->PSShader01();
	g_sandBox->SetTexture2X2();

	//�Ի���
	//HWND hAbout = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)About);
	//ShowWindow(hAbout, SW_SHOW);
	//UpdateWindow(hAbout);

	//��Ϸѭ��
	while (g_wnd->ProcessMessage()) {
		g_d3d9->BeginScene();

		//g_sandBox->Draw();
		//g_sandBox->DrawUp();
		//g_sandBox->DrawIndexedUp();
		//g_sandBox->DrawIndexedUpTexture();
		//g_sandBox->DrawIndexedUpHumTexture();
		//g_sandBox->DrawIndexedUpHumTextureShader();
		g_sandBox->DrawVSShader();
		g_d3d9->EndScene();
	}

	//ɾ������
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
			hWndSlider1 = GetDlgItem(hDlg, IDC_SLIDER1); //m_hWndΪ�����ڵľ��
			SendMessageW(hWndSlider1, TBM_SETRANGE, TRUE, (LPARAM)MAKELONG(0, 255));//����0-255

			hWndSlider2 = GetDlgItem(hDlg, IDC_SLIDER2); //m_hWndΪ�����ڵľ��
			SendMessageW(hWndSlider2, TBM_SETRANGE, TRUE, (LPARAM)MAKELONG(0, 255));//����0-255

			hWndSlider3 = GetDlgItem(hDlg, IDC_SLIDER3); //m_hWndΪ�����ڵľ��
			SendMessageW(hWndSlider3, TBM_SETRANGE, TRUE, (LPARAM)MAKELONG(0, 255));//����0-255
			return TRUE;
		}
		case WM_COMMAND:
		{
			if (LOWORD(wParam) == IDC_BUTTON1)
			{
				OutputDebugString(L"��ť�¼�");
				return TRUE;
			}
			break;
		}
		case WM_HSCROLL:
		{
			color.R = (LONG)SendMessageW(hWndSlider1, TBM_GETPOS, 0, 0); //value���ǵ�ǰ�ؼ���ֵ
			color.G = (LONG)SendMessageW(hWndSlider2, TBM_GETPOS, 0, 0); //value���ǵ�ǰ�ؼ���ֵ
			color.B = (LONG)SendMessageW(hWndSlider3, TBM_GETPOS, 0, 0); //value���ǵ�ǰ�ؼ���ֵ

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
