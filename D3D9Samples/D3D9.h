#pragma once
#include "Base.h"

class D3D9 {
private:
	HWND mHwnd;						//���ھ��
	LPDIRECT3D9 m_d3d9;				//d3d����
	LPD3DXFONT m_d3dFont;			//���ֶ���
public:
	LPDIRECT3DDEVICE9 m_d3dDevice;	//�豸����
public:
	D3D9(HWND hwnd);
	~D3D9();
	HRESULT InitD3D();
	void BeginScene();
	void EndScene();
};