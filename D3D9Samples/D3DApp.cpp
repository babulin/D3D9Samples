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
	//����D3D
	g_d3d9 = new D3D9(pWnd->mHwnd);

	//��ʼ��
	if (FAILED(g_d3d9->InitD3D())) {
		MessageBox(pWnd->mHwnd, TEXT("InitD3D��ʼ��ʧ��"), TEXT("������ʾ"), MB_OK);
	}

	//------------------------------------
	//������
	g_vBuff = new VertexBuffer(g_d3d9->m_d3dDevice,pWnd->mWidth,pWnd->mHeight);

	//��������
	g_vBuff->Init();

	//------------------------------------
	g_texture = new Texture(g_d3d9->m_d3dDevice, pWnd->mWidth, pWnd->mHeight);
	g_texture->Init();
	return S_OK;
}

void D3DApp::Render()
{
	g_d3d9->BeginScene();

	//����
	//g_vBuff->Draw();
	//g_vBuff->DrawPrimitiveUP();
	//g_vBuff->DrawIndexedPrimitiveUP();

	//����
	//g_texture->DrawPrimitiveUPUV1();
	//g_texture->DrawIndexedPrimitiveUPUV2();
	g_texture->DrawIndexedPrimitiveUPUV2x2();


	g_d3d9->EndScene();
}

void D3DApp::Clear()
{
	//ɾ������
	if (g_d3d9 != nullptr)
		delete g_d3d9;
}
