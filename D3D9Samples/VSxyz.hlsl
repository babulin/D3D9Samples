
float4 matWorldViewProj;

float4 vs_main( float4 pos : POSITION) : SV_POSITION
{
	//��ɶ���������任
	pos = mul(pos, matWorldViewProj);

	return pos;
}