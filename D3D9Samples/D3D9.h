#pragma once
#include "Base.h"
#include "GameWind.h"

class D3D9 {
private:
	LPDIRECT3D9 m_d3d9;				//d3d����
	LPD3DXFONT m_d3dFont;			//���ֶ���
public:
	LPDIRECT3DDEVICE9 m_d3dDevice;	//�豸����
	GameWind* pGameWind;			//���ڶ���
public:
	D3D9(GameWind* GameWind);
	~D3D9();
	HRESULT InitD3D();
	void BeginScene();
	void EndScene();
};