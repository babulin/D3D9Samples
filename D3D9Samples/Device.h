#pragma once
#include "Base.h"
#include "D3D9.h"

class Device {
public:
	float mWidth;
	float mHeight;
protected:
	LPDIRECT3DDEVICE9 m_d3dDevice;				//D3D设备
public:
	Device(D3D9* d3d9) {
		mWidth = static_cast<float>(d3d9->pGameWind->mWidth);
		mHeight = static_cast<float>(d3d9->pGameWind->mHeight);
		m_d3dDevice = d3d9->m_d3dDevice;
	};

	//旋转变换矩阵
	HRESULT SetRotation(D3DXMATRIX* matWorld, float* matTran = nullptr,D3DXMATRIX* matTs = nullptr) {
		//旋转矩阵
		D3DXMATRIX Rx, Ry, Rz;
		static float Vx = 0.0f, Vy = 0.0f,Vz = 0.0f;

		//X
		if (GetAsyncKeyState('W')) {
			Vx += 0.01f;
		}
		if (GetAsyncKeyState('S')) {
			Vx -= 0.01f;
		}
		if (Vx > 6.28f) {
			Vx = 0.0f;
		}
		D3DXMatrixRotationX(&Rx, Vx);

		//Y
		if (GetAsyncKeyState('A')) {
			Vy += 0.01f;
		}
		if (GetAsyncKeyState('D')) {
			Vy -= 0.01f;
		}
		if (Vy > 6.28f) {
			Vy = 0.0f;
		}
		D3DXMatrixRotationY(&Ry, Vy);

		//Z
		if (GetAsyncKeyState('Q')) {
			Vz += 0.01f;
		}
		if (GetAsyncKeyState('E')) {
			Vz -= 0.01f;
		}
		if (Vz > 6.28f) {
			Vz = 0.0f;
		}
		D3DXMatrixRotationZ(&Rz, Vz);


		//平移
		static float Dx = 0.0f, Dy = 0.0f, Dz = 0.0f;
		if (GetAsyncKeyState('T')) {
			Dy += 0.01f;
		}
		if (GetAsyncKeyState('H')) {
			Dx += 0.01f;
		}
		if (GetAsyncKeyState('G')) {
			Dy -= 0.01f;
		}
		if (GetAsyncKeyState('F')) {
			Dx -= 0.01f;
		}
		if (GetAsyncKeyState('R')) {
			Dz += 0.01f;
		}
		if (GetAsyncKeyState('Y')) {
			Dz -= 0.01f;
		}
		if (matTran != nullptr)
		{
			matTran[0] = Dx;
			matTran[1] = Dy;
			matTran[2] = Dz;
			matTran[3] = 0.0f;
		}

		if (matTs != nullptr)
		{
			D3DXMatrixTranslation(matTs, Dx, Dy, Dz);
		}

		//wchar_t buf[100];
		//swprintf_s(buf, TEXT("%.2f,%.2f,%.2f\n"),Dx, Dy, Dz);
		//OutputDebugString(buf);

		//设置单位世界矩阵
		D3DXMatrixIdentity(matWorld);
		*matWorld = (*matWorld) * Rx * Ry * Rz;

		return S_OK;
	}

	//取景变换矩阵
	HRESULT SetLookAtLH(D3DXMATRIX* matView,float x = 0.0f,float y = 0.0f,float z = -1.0f) {
		D3DXVECTOR3 position(x, y, z);//摄像机位置
		D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);//观察点位置
		D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);//向上的向量
		D3DXMatrixLookAtLH(matView, &position, &target, &up);
		return S_OK;
	}

	//透视投影矩阵
	HRESULT SetPerspectiveFovLH(D3DXMATRIX* matProj) {
		float aspect = (float)(mWidth / mHeight);
		D3DXMatrixPerspectiveFovLH(matProj, D3DX_PI * 0.5f, aspect, 1.0f, 1000.0f);
		return S_OK;
	}


	void SetUpMatrices()
	{
		///四大变换之一：世界变换矩阵的设置
		///平移变换
		//D3DXMATRIX T1;
		//D3DXMatrixTranslation(&T1, -0.5f, 0.5f, 0.5f);
		//m_d3dDevice->SetTransform(D3DTS_WORLD, &T1);

		///四大变换之二：取景变换矩阵的设置
		//D3DXMATRIX matView;
		//D3DXVECTOR3 position(0.0f, 0.0f, -1.5f);//摄像机位置
		//D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);//观察点位置
		//D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);//向上的向量
		//D3DXMatrixLookAtLH(&matView, &position, &target, &up);
		//m_d3dDevice->SetTransform(D3DTS_VIEW, &matView);

		///四大变换之三：投影变换矩阵的设置
		//透视投影矩阵
		//D3DXMATRIX proj;
		//float aspect = (float)(mWidth / mHeight);
		//D3DXMatrixPerspectiveFovLH(&proj, D3DX_PI * 0.5f, aspect, 1.0f, 1000.0f);
		//m_d3dDevice->SetTransform(D3DTS_PROJECTION, &proj);

		///四大变换之四：视口变换的设置
		//D3DVIEWPORT9 vp;
		//vp.X = 0;
		//vp.Y = 0;
		//vp.Width = mWidth/2;//视口的宽度
		//vp.Height = mHeight/2;//视口的高度
		//vp.MinZ = 0.0;
		//vp.MaxZ = 1.0;
		//m_d3dDevice->SetViewport(&vp);
	}

};