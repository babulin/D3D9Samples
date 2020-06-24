sampler samp;//����
sampler samp1;//����

matrix matWorld;//�任����
float4 matTran;//ƽ�ƾ���

//������������(����)
struct PS_INPUT {
	float2 t0 : TEXCOORD0;//������������UV
	float2 t1 : TEXCOORD1;//������������UV
	vector color : COLOR;//��ɫ
};

//��������
struct PS_OUTPUT {
	vector color : COLOR0;
};

//  
//				 _             _
//				| Rr Rg Rb Ra 0 |
//				| Gr Gg Gb Ga 0 |
//[R G B A 1]	| Br Bg Bb Ba 0 |
//				| Ar Ag Ab Aa 0 |
//				|_Or Og Ob Oa 1_|

//				 _             _
//				| Rr Rg Rb Ra  |
//				| Gr Gg Gb Ga  |
//[R G B A]		| Br Bg Bb Ba  |
//				| Ar Ag Ab Aa  |
//				|_Or Og Ob Oa _|
struct ColorMatrix {
	row_major float4x4 mat;
	float4 offset;
};

float4 ColorTransform(float4 color, ColorMatrix mat)
{
	return mul(color, mat.mat) + mat.offset;
}

PS_OUTPUT ps_main(PS_INPUT input)
{
	//��ʼ��
	ColorMatrix mat;
	mat.mat = matWorld;
	mat.offset = matTran;

	//���
	PS_OUTPUT output = (PS_OUTPUT)0;

	//UV����-��ȡ���������ɫֵ
	float4 color = tex2D(samp, input.t0);
	float4 color1 = tex2D(samp1, input.t1);

	//��ɫ�������
	color = color * color1;
	color = ColorTransform(color, mat);

	//���������ɫ
	output.color = color;

	return output;
}