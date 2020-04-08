
matrix matWorld;//变换矩阵
matrix matView;//
matrix matProj;//
matrix matWVP;	//组合变换矩阵

//输入参数
struct VS_INPUT {
	vector position : POSITION;
	vector diffuse : COLOR;
};

//输出参数
struct VS_OUTPUT {
	vector position : POSITION;
	vector diffuse : COLOR;
};

//顶点着色器入口
VS_OUTPUT vs_main(VS_INPUT input)
{
	//初始化
	VS_OUTPUT output = (VS_OUTPUT)0;


	//不处理输出
	//output.position = input.position;
	//output.diffuse = input.diffuse;

	//处理变换
	output.position = mul(input.position, matProj);//透视投影

	//漫反射
	output.diffuse = mul(input.diffuse, matWorld);//漫反射

	return output;
}