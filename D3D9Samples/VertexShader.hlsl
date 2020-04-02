
//ȫ�ֱ���
matrix matWorld;			//����任����
matrix matWorldViewProj;	//��ϱ任����
float4 vecLightDir;			//���շ���
float4 mtrlAmbient;			//���ʻ�����ϵ��
float4 mtrlDiffuse;			//����������ϵ��

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
	
	float4 LightDir = normalize(vecLightDir);//���߷���λ��
	float4 Normalize = normalize(mul(input.Normal, matWorld));//������ * �������  �� ��λ��
	float4 colorAmbient = { 1.0f,0.0f,0.0f,1.0f };//��������ɫ
	float4 colorDiffuse = { 0.0f,2.0f,0.0f,1.0f };//��������ɫ

	//������Ϊ��ɫ RGBA
	//output.Diffuse =  colorAmbient* mtrlAmbient + colorDiffuse * saturate(dot(LightDir, Normalize)) * mtrlDiffuse;
	
	//��������ɫ * ϵ��
	output.Diffuse = colorAmbient * mtrlAmbient;
	//���߷��� * ������ * ��������ɫ * ������ϵ��
	output.Diffuse += dot(LightDir, Normalize) * colorDiffuse * mtrlDiffuse;

	return output;
}