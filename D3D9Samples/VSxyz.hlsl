
float4 matWorldViewProj;

float4 vs_main( float4 pos : POSITION) : SV_POSITION
{
	//完成顶点的三个变换
	pos = mul(pos, matWorldViewProj);

	return pos;
}