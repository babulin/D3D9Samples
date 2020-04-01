
//ȫ�ֱ���
matrix WorldViewProjMatrix;	//4x4����

struct BGCOLOR {
	float4 Color;
	float4 Color1;
	float4 Color2;
};

//������ɫ������ṹ
struct VS_INPUT {
	vector Position : POSITION;
};

//������ɫ������ṹ
struct VS_OUTPUT {
	vector Position : POSITION;//��������
	vector Diffuse : COLOR;//������ɫ
};

VS_OUTPUT vs_main(VS_INPUT input) {
	//���output
	VS_OUTPUT output = (VS_OUTPUT)0;

	//��ɶ���������任
	output.Position = mul(input.Position, WorldViewProjMatrix);
	
	//������Ϊ��ɫ RGBA
	output.Diffuse = float4(1.0f, 0.0f, 0.0f, 1.0f);
	return output;
}