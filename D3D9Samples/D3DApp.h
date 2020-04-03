#pragma once
#include "GameWind.h"
#include "D3D9.h"
#include "Base.h"

class D3DApp {
	GameWind* pWnd;
	D3D9* g_d3d9;
	LPDIRECT3DDEVICE9 m_d3dDevice;
	float mWidth;
	float mHeight;
public:
	D3DApp(GameWind* wnd);
	HRESULT Init();
	void Render();
	void Clear();
};