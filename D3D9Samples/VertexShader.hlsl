
//全局变量
extern matrix matWorld;				//世界变换矩阵
extern matrix matWorldViewProj;		//组合变换矩阵
extern float4 vecLightDir;			//光照方向
extern float4 mtrlAmbient;			//材质环境光系数
extern float4 mtrlDiffuse;			//材质漫反射系数

//顶点着色器输入结构
struct VS_INPUT {
	vector Position : POSITION;	//顶点坐标
	vector Normal : NORMAL0;	//顶点法向量
};

//顶点着色器输出结构
struct VS_OUTPUT {
	vector Position : POSITION;	//顶点坐标
	vector Diffuse : COLOR;		//顶点颜色
};

VS_OUTPUT vs_main(VS_INPUT input) {
	//清空output
	VS_OUTPUT output = (VS_OUTPUT)0;

	//完成顶点的三个变换
	output.Position = mul(input.Position, matWorldViewProj);
	
	//顶点颜色
	float4 LightDir = normalize(vecLightDir);
	float4 Normalize = normalize(mul(input.Normal, matWorld));
	float4 colorDiffuse = { 1.0f,1.0f,1.0f,1.0f };
	float4 colorAmbient = { 0.5f,0.5f,0.5f,1.0f };

	//漫反射为蓝色 RGBA
	output.Diffuse = colorAmbient * mtrlAmbient
		+ colorDiffuse * saturate(dot(LightDir, Normalize)) * mtrlDiffuse;
	return output;
}