#include "D3DApp.h"

D3DApp::D3DApp(GameWind* wnd)
{
	pWnd = wnd;
	mWidth = static_cast<float>(wnd->mWidth);
	mHeight = static_cast<float>(wnd->mHeight);
}

HRESULT D3DApp::Init()
{
	//����D3D
	g_d3d9 = new D3D9(pWnd->mHwnd);

	//��ʼ��
	if (FAILED(g_d3d9->InitD3D())) {
		MessageBox(pWnd->mHwnd, TEXT("InitD3D��ʼ��ʧ��"), TEXT("������ʾ"), MB_OK);
	}
}

void D3DApp::Render()
{

}

void D3DApp::Clear()
{
}
