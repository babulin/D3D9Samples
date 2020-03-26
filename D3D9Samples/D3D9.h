#pragma once
#include "Base.h"

class D3D9 {
private:
	HWND mHwnd;						//窗口句柄
	LPDIRECT3D9 m_d3d9;				//d3d对象
	LPD3DXFONT m_d3dFont;			//文字对象
public:
	LPDIRECT3DDEVICE9 m_d3dDevice;	//设备对象
public:
	D3D9(HWND hwnd);
	~D3D9();
	HRESULT InitD3D();
	void BeginScene();
	void EndScene();
};