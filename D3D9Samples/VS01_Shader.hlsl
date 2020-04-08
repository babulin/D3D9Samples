
matrix matWorld;//�任����
matrix matView;//
matrix matProj;//
matrix matWVP;	//��ϱ任����

//�������
struct VS_INPUT {
	vector position : POSITION;
	vector diffuse : COLOR;
};

//�������
struct VS_OUTPUT {
	vector position : POSITION;
	vector diffuse : COLOR;
};

//������ɫ�����
VS_OUTPUT vs_main(VS_INPUT input)
{
	//��ʼ��
	VS_OUTPUT output = (VS_OUTPUT)0;


	//���������
	//output.position = input.position;
	//output.diffuse = input.diffuse;

	//����任
	output.position = mul(input.position, matProj);//͸��ͶӰ

	//������
	output.diffuse = mul(input.diffuse, matWorld);//������

	return output;
}