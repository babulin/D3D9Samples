
//纹理对应 顺序
sampler ATex;//0 纹理
sampler BTex;//1 纹理
float4 color;
//输入纹理坐标(所有)
struct PS_INPUT {
	float2 t0 : TEXCOORD0;
	float2 t1 : TEXCOORD1;
};

//运算后输出
struct PS_OUTPUT {
	vector diffuse : COLOR0;
};

PS_OUTPUT main(PS_INPUT input)
{
	PS_OUTPUT output = (PS_OUTPUT)0;
	vector a = tex2D(ATex, input.t0);
	vector b = tex2D(BTex, input.t1);


	//b = vector(1.0f, 1.0f, 1.0f, 0);

	vector c = (a) * b * color;
	output.diffuse = c;

	//output.diffuse = vector(1.0f,1.0f,1.0f,1.0f);
	return output;
}
