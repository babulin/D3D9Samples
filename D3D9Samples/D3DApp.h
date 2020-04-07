#pragma once
#include "GameWind.h"
#include "D3D9.h"
#include "Base.h"

class D3DApp {
	GameWind* pGameWind;
	D3D9* g_d3d9;
public:
	D3DApp(GameWind* GameWind);
	HRESULT Init();
	void Render();
	void Clear();
};