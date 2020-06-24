sampler samp;//采样

matrix matWorld;//变换矩阵

//输入纹理坐标(所有)
struct PS_INPUT {
	float2 t0 : TEXCOORD0;//输入纹理坐标UV
	vector color : COLOR;//颜色
};

//运算后输出
struct PS_OUTPUT {
	vector color : COLOR0;
};

PS_OUTPUT ps_main(PS_INPUT input)
{
	//输出
	PS_OUTPUT output = (PS_OUTPUT)0;

	//UV坐标-获取纹理采样颜色值
	float4 color = tex2D(samp, input.t0);

	//HDR高亮
	float4 HDR = float4(2.0f, 2.0f, 2.0f, 2.0f);

	//矩阵乘法
	color = mul(color, matWorld);

	//设置输出颜色
	output.color = color;

	return output;
}