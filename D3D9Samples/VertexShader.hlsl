
//全局变量
matrix WorldViewProjMatrix;	//4x4矩阵

struct BGCOLOR {
	float4 Color;
	float4 Color1;
	float4 Color2;
};

//顶点着色器输入结构
struct VS_INPUT {
	vector Position : POSITION;
};

//顶点着色器输出结构
struct VS_OUTPUT {
	vector Position : POSITION;//顶点坐标
	vector Diffuse : COLOR;//顶点颜色
};

VS_OUTPUT vs_main(VS_INPUT input) {
	//清空output
	VS_OUTPUT output = (VS_OUTPUT)0;

	//完成顶点的三个变换
	output.Position = mul(input.Position, WorldViewProjMatrix);
	
	//漫反射为蓝色 RGBA
	output.Diffuse = float4(1.0f, 0.0f, 0.0f, 1.0f);
	return output;
}