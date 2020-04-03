#pragma once
#include <Windows.h>
#include <string>
#include <tchar.h> //swprintf_s

#include <d3dx9.h>
#include <d3d9.h>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")//d3d链接库
#pragma comment(lib,"winmm.lib") //timeGetTime()

//D3DFMT_A8R8G8B8	ARGB
#define COLOR_RED D3DCOLOR_ARGB(255, 255, 0, 0)
#define COLOR_GREEN D3DCOLOR_ARGB(255, 0, 255, 0)
#define COLOR_BLUE D3DCOLOR_ARGB(255, 0, 0, 255)
#define COLOR_WHITE D3DCOLOR_ARGB(255, 255, 255, 255)

//D3DFMT_A32B32G32R32F   RGBA
#define COLORF_RED D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f)
#define COLORF_GREEN D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f)
#define COLORF_BLUE D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f)
#define COLORF_WHITE D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f)

struct D3Vertex
{
	float x, y, z;
	DWORD color;
	static const DWORD FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
};

struct UV1Vertex
{
	float x, y, z;
	DWORD color;
	float u, v;
	static const DWORD FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1;
};

struct UV2Vertex
{
	float x, y, z;
	DWORD color;
	float u, v;
	float u1, v1;
	static const DWORD FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX2;
};

struct UV3Vertex
{
	float x, y, z;
	DWORD color;
	float u, v;
	float u1, v1;
	float u2, v2;
	static const DWORD FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX3;
};

struct RHWVertex
{
	float x, y, z, rhw;
	DWORD color;
	float u, v;
	float u1, v1;
	static const DWORD FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX2;
};

//可编程顶点结构
struct VSVertex {
	float x, y, z;//顶点位置
	float nx, ny, nz;//顶点法向量
	VSVertex(float x, float y, float z, float nx, float ny, float nz)
		:x(x), y(y), z(z), nx(nx), ny(ny), nz(nz) {}
	static const DWORD FVF = D3DFVF_XYZ | D3DFVF_NORMAL;
};