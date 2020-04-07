#pragma once
#include "Base.h"
#include "D3D9.h"

class Device {
public:
	float mWidth;
	float mHeight;
protected:
	LPDIRECT3DDEVICE9 m_d3dDevice;				//D3D�豸
public:
	Device(D3D9* d3d9) {
		mWidth = static_cast<float>(d3d9->pGameWind->mWidth);
		mHeight = static_cast<float>(d3d9->pGameWind->mHeight);
		m_d3dDevice = d3d9->m_d3dDevice;
	};

	void SetUpMatrices()
	{
		///�Ĵ�任֮һ������任���������
		///ƽ�Ʊ任
		//D3DXMATRIX T1;
		//D3DXMatrixTranslation(&T1, -0.5f, 0.5f, 0.5f);
		//m_d3dDevice->SetTransform(D3DTS_WORLD, &T1);

		///�Ĵ�任֮����ȡ���任���������
		//D3DXMATRIX matView;
		//D3DXVECTOR3 position(0.0f, 0.0f, -1.5f);//�����λ��
		//D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);//�۲��λ��
		//D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);//���ϵ�����
		//D3DXMatrixLookAtLH(&matView, &position, &target, &up);
		//m_d3dDevice->SetTransform(D3DTS_VIEW, &matView);

		///�Ĵ�任֮����ͶӰ�任���������
		//͸��ͶӰ����
		//D3DXMATRIX proj;
		//float aspect = (float)(mWidth / mHeight);
		//D3DXMatrixPerspectiveFovLH(&proj, D3DX_PI * 0.5f, aspect, 1.0f, 1000.0f);
		//m_d3dDevice->SetTransform(D3DTS_PROJECTION, &proj);

		///�Ĵ�任֮�ģ��ӿڱ任������
		//D3DVIEWPORT9 vp;
		//vp.X = 0;
		//vp.Y = 0;
		//vp.Width = mWidth/2;//�ӿڵĿ���
		//vp.Height = mHeight/2;//�ӿڵĸ߶�
		//vp.MinZ = 0.0;
		//vp.MaxZ = 1.0;
		//m_d3dDevice->SetViewport(&vp);
	}

};