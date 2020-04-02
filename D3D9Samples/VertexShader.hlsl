
//ȫ�ֱ���
extern matrix matWorld;				//����任����
extern matrix matWorldViewProj;		//��ϱ任����
extern float4 vecLightDir;			//���շ���
extern float4 mtrlAmbient;			//���ʻ�����ϵ��
extern float4 mtrlDiffuse;			//����������ϵ��

//������ɫ������ṹ
struct VS_INPUT {
	vector Position : POSITION;	//��������
	vector Normal : NORMAL0;	//���㷨����
};

//������ɫ������ṹ
struct VS_OUTPUT {
	vector Position : POSITION;	//��������
	vector Diffuse : COLOR;		//������ɫ
};

VS_OUTPUT vs_main(VS_INPUT input) {
	//���output
	VS_OUTPUT output = (VS_OUTPUT)0;

	//��ɶ���������任
	output.Position = mul(input.Position, matWorldViewProj);
	
	//������ɫ
	float4 LightDir = normalize(vecLightDir);
	float4 Normalize = normalize(mul(input.Normal, matWorld));
	float4 colorDiffuse = { 1.0f,1.0f,1.0f,1.0f };
	float4 colorAmbient = { 0.5f,0.5f,0.5f,1.0f };

	//������Ϊ��ɫ RGBA
	output.Diffuse = colorAmbient * mtrlAmbient
		+ colorDiffuse * saturate(dot(LightDir, Normalize)) * mtrlDiffuse;
	return output;
}