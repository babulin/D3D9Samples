sampler samp;//����

matrix matWorld;//�任����

//������������(����)
struct PS_INPUT {
	float2 t0 : TEXCOORD0;//������������UV
	vector color : COLOR;//��ɫ
};

//��������
struct PS_OUTPUT {
	vector color : COLOR0;
};

PS_OUTPUT ps_main(PS_INPUT input)
{
	//���
	PS_OUTPUT output = (PS_OUTPUT)0;

	//UV����-��ȡ���������ɫֵ
	float4 color = tex2D(samp, input.t0);

	//HDR����
	float4 HDR = float4(2.0f, 2.0f, 2.0f, 2.0f);

	//����˷�
	color = mul(color, matWorld);

	//���������ɫ
	output.color = color;

	return output;
}