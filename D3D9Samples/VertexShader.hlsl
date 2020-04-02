
//全局变量
matrix matWorld;			//世界变换矩阵
matrix matWorldViewProj;	//组合变换矩阵
float4 vecLightDir;			//光照方向
float4 mtrlAmbient;			//材质环境光系数
float4 mtrlDiffuse;			//材质漫反射系数

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
	
	float4 LightDir = normalize(vecLightDir);//光线方向单位化
	float4 Normalize = normalize(mul(input.Normal, matWorld));//法向量 * 世界矩阵  再 单位化
	float4 colorAmbient = { 1.0f,0.0f,0.0f,1.0f };//环境光颜色
	float4 colorDiffuse = { 0.0f,2.0f,0.0f,1.0f };//漫反射颜色

	//漫反射为蓝色 RGBA
	//output.Diffuse =  colorAmbient* mtrlAmbient + colorDiffuse * saturate(dot(LightDir, Normalize)) * mtrlDiffuse;
	
	//环境光颜色 * 系数
	output.Diffuse = colorAmbient * mtrlAmbient;
	//光线方向 * 法向量 * 漫反射颜色 * 漫反射系数
	output.Diffuse += dot(LightDir, Normalize) * colorDiffuse * mtrlDiffuse;

	return output;
}