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