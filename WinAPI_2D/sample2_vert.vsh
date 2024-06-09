struct VS_INPUT
{
    float2 Pos : POSITION;
    float2 Tex : TEX;
    float4 Col : COLOR;
};

struct VS_OUTPUT
{
	float4 Pos : SV_Position;
	float2 Tex : TEXCOORD0;
	float4 Col : COLOR;
};

VS_OUTPUT vs(VS_INPUT input)
{
	VS_OUTPUT output;

    output.Pos = float4(input.Pos, 0.5f,  1.f);
    output.Tex = input.Tex;
    output.Col = input.Col;

	return output;
}
