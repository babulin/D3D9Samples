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

	//��ת�任����
	HRESULT SetRotation(D3DXMATRIX* matWorld, float* matTran = nullptr,D3DXMATRIX* matTs = nullptr) {
		//��ת����
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


		//ƽ��
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

		//���õ�λ�������
		D3DXMatrixIdentity(matWorld);
		*matWorld = (*matWorld) * Rx * Ry * Rz;

		return S_OK;
	}

	//ȡ���任����
	HRESULT SetLookAtLH(D3DXMATRIX* matView,float x = 0.0f,float y = 0.0f,float z = -1.0f) {
		D3DXVECTOR3 position(x, y, z);//�����λ��
		D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);//�۲��λ��
		D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);//���ϵ�����
		D3DXMatrixLookAtLH(matView, &position, &target, &up);
		return S_OK;
	}

	//͸��ͶӰ����
	HRESULT SetPerspectiveFovLH(D3DXMATRIX* matProj) {
		float aspect = (float)(mWidth / mHeight);
		D3DXMatrixPerspectiveFovLH(matProj, D3DX_PI * 0.5f, aspect, 1.0f, 1000.0f);
		return S_OK;
	}


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
		//vp.Width = mWidth/2;//�ӿڵĿ��
		//vp.Height = mHeight/2;//�ӿڵĸ߶�
		//vp.MinZ = 0.0;
		//vp.MaxZ = 1.0;
		//m_d3dDevice->SetViewport(&vp);
	}

};