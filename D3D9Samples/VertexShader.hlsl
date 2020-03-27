
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
//����
bool	//���� true false
int		//32λ
half	//16λ����
float	//32λ����
double	//64λ����

//��������
vector						//4D���� ÿ��Ԫ��float
vector<T, n>				//nά����(1-4)��ÿ��Ԫ�ر�������T
	vector<double, 2> vec;
	vec[1] = 2.0f;
	vec.x = vec.r = 1.0f;	//�Ѷ�������� r,g,b,a    x,y,z,w

//Ԥ��������
float2 vec2;	//2D
float3 vec3;	//3D
float4 vec4;	//4D

//�滻����
vector u = { 1.0f,2.0f,3.0f,4.0f };

vector v = { 0.0f,0.0f,0.5f,0.6f };
v = u.xyyw;		//v = {1.0f,2.0f,2.0f,4.0f} ������˳����

vector v = { 0.0f,0.0f,0.5f,0.6f };
v.xy = u;		//v = {1.0f,2.0f,0.5f,0.6f}	ֻ����xy

//����
matrix //4x4���� ÿ��Ԫ�ر������� float;
matrix<T, m, n>	//��ʾm��n������ÿ��Ԫ�ر�������T m(1-4) n(1-4)
	matrix<float, 2, 2> m2x2;	//2x2 float����
//Ԥ����
float2x2 mat2x2;
float3x3 mat3x3;
float4x4 mat4x4;
float2x4 mat2x4;

#endif;