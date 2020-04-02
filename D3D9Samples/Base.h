#pragma once
#include <Windows.h>
#include <string>
#include <tchar.h> //swprintf_s

#include <d3dx9.h>
#include <d3d9.h>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")//d3d链接库
#pragma comment(lib,"winmm.lib") //timeGetTime()

struct MYCOLOR
{
	LONG R;
	LONG G;
	LONG B;
};


struct D3Vertex
{
	float x, y, z;
	DWORD color;
	static const DWORD FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
};

struct UVVertex
{
	float x, y, z;
	DWORD color;
	float u, v;
	float u1, v1;
	static const DWORD FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX2;
};

struct UV2Vertex
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