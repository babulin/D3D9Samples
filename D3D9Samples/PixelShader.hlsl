
//输入纹理坐标(所有)
struct PS_INPUT {
	float2 t0 : TEXCOORD0;
	float2 t1 : TEXCOORD1;
};

//运算后输出
struct PS_OUTPUT {
	vector diffuse : COLOR0;
};

PS_OUTPUT ps_main()
{
	PS_OUTPUT output = (PS_OUTPUT)0;

	output.diffuse = float4(1.0f, 0.0f, 0.0f, 1.0f);

	return output;
}