struct VS_INPUT {
	vector position : POSITION;
};

struct VS_OUTPUT {
	vector position : POSITION;
};

VS_OUTPUT main(VS_INPUT input) {
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.position = vector(1.0f,1.3f,1.0f,1.0f);
	return output;
}