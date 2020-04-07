#pragma once
#include "Base.h"
#include "GameWind.h"

class D3D9 {
private:
	LPDIRECT3D9 m_d3d9;				//d3d对象
	LPD3DXFONT m_d3dFont;			//文字对象
public:
	LPDIRECT3DDEVICE9 m_d3dDevice;	//设备对象
	GameWind* pGameWind;			//窗口对象
public:
	D3D9(GameWind* GameWind);
	~D3D9();
	HRESULT InitD3D();
	void BeginScene();
	void EndScene();
};