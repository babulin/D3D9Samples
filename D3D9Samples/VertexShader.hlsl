
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
//标量
bool	//布尔 true false
int		//32位
half	//16位浮点
float	//32位浮点
double	//64位浮点

//向量类型
vector						//4D向量 每个元素float
vector<T, n>				//n维向量(1-4)，每个元素标量类型T
	vector<double, 2> vec;
	vec[1] = 2.0f;
	vec.x = vec.r = 1.0f;	//已定义分量名 r,g,b,a    x,y,z,w

//预定于类型
float2 vec2;	//2D
float3 vec3;	//3D
float4 vec4;	//4D

//替换调配
vector u = { 1.0f,2.0f,3.0f,4.0f };

vector v = { 0.0f,0.0f,0.5f,0.6f };
v = u.xyyw;		//v = {1.0f,2.0f,2.0f,4.0f} 不关心顺序复制

vector v = { 0.0f,0.0f,0.5f,0.6f };
v.xy = u;		//v = {1.0f,2.0f,0.5f,0.6f}	只复制xy

//矩阵
matrix //4x4矩阵 每个元素标量类型 float;
matrix<T, m, n>	//表示m×n个矩阵，每个元素标量类型T m(1-4) n(1-4)
	matrix<float, 2, 2> m2x2;	//2x2 float矩阵
//预定义
float2x2 mat2x2;
float3x3 mat3x3;
float4x4 mat4x4;
float2x4 mat2x4;

#endif;