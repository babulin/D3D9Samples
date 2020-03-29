
matrix ViewProjMatrix;
vector Blue = { 0.0f,0.0f,1.0f,1.0f };

struct VS_INPUT {
	vector position : POSITION;
};

struct VS_OUTPUT {
	vector position : POSITION;
	vector diffuse : COLOR;
};

VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.position = mul(input.position, ViewProjMatrix);
	output.diffuse = Blue;
	return output;
}

#if 0
//±êÁ¿
bool	//²¼¶û true false
int		//32Î»
half	//16Î»¸¡µã
float	//32Î»¸¡µã
double	//64Î»¸¡µã

//ÏòÁ¿ÀàÐÍ
vector						//4DÏòÁ¿ Ã¿¸öÔªËØfloat
vector<T, n>				//nÎ¬ÏòÁ¿(1-4)£¬Ã¿¸öÔªËØ±êÁ¿ÀàÐÍT
	vector<double, 2> vec;
	vec[1] = 2.0f;
	vec.x = vec.r = 1.0f;	//ÒÑ¶¨Òå·ÖÁ¿Ãû r,g,b,a    x,y,z,w

//Ô¤¶¨ÓÚÀàÐÍ
float2 vec2;	//2D
float3 vec3;	//3D
float4 vec4;	//4D

//Ìæ»»µ÷Åä
vector u = { 1.0f,2.0f,3.0f,4.0f };

vector v = { 0.0f,0.0f,0.5f,0.6f };
v = u.xyyw;		//v = {1.0f,2.0f,2.0f,4.0f} ²»¹ØÐÄË³Ðò¸´ÖÆ

vector v = { 0.0f,0.0f,0.5f,0.6f };
v.xy = u;		//v = {1.0f,2.0f,0.5f,0.6f}	Ö»¸´ÖÆxy

//¾ØÕó
matrix //4x4¾ØÕó Ã¿¸öÔªËØ±êÁ¿ÀàÐÍ float;
matrix<T, m, n>	//±íÊ¾m¡Án¸ö¾ØÕó£¬Ã¿¸öÔªËØ±êÁ¿ÀàÐÍT m(1-4) n(1-4)
	matrix<float, 2, 2> m2x2;	//2x2 float¾ØÕó
//Ô¤¶¨Òå
float2x2 mat2x2;
float3x3 mat3x3;
float4x4 mat4x4;
float2x4 mat2x4;

#endif;



#if 0
	//应用程序

	//D3DXHANDLE handle;
	//handle = m_ConstantTable->GetConstantByName(0, "ViewProjMatrix");

	//BOOL b = true;
	//m_ConstantTable->SetBool(m_d3dDevice, handle, b);

	//BOOL b1[3] = { true,true,true };
	//m_ConstantTable->SetBoolArray(m_d3dDevice, handle, b1, 3);

	//FLOAT f = 3.14f;
	//m_ConstantTable->SetFloat(m_d3dDevice, handle, f);

	//FLOAT f1[2] = { 3.14f,4.14f };
	//m_ConstantTable->SetFloatArray(m_d3dDevice, handle, f1,2);

	//INT i = 3;
	//m_ConstantTable->SetInt(m_d3dDevice, handle, i);

	//INT i1[3] = { 3,4,5 };
	//m_ConstantTable->SetIntArray(m_d3dDevice, handle, i1, 3);

	//D3DXMATRIX matrix;
	//m_ConstantTable->SetMatrix(m_d3dDevice, handle, &matrix);

	//D3DXMATRIX matrix1[4];
	//m_ConstantTable->SetMatrixArray(m_d3dDevice, handle, matrix1,4);

	//D3DXMATRIX* matrix2[4];
	//m_ConstantTable->SetMatrixPointerArray(m_d3dDevice, handle, matrix2, 4);

	//D3DXVECTOR4 v(1.0f,2.0f,3.0f,4.0f);
	//m_ConstantTable->SetVector(m_d3dDevice, handle, &v);

	//D3DXVECTOR4 v1[3];
	//m_ConstantTable->SetVectorArray(m_d3dDevice, handle, v1, 3);

	//D3DXMATRIX mm;
	//m_ConstantTable->SetValue(m_d3dDevice, handle, (void*)&mm,sizeof(mm));
#endif;