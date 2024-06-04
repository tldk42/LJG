struct VS_OUTPUT
{
	float4 Pos : SV_Position;
	float2 Texture : TEXCOORD0;
};

VS_OUTPUT vs(float2 inPos : POSITION, float2 tex : TEX)
{
	VS_OUTPUT output;

    output.Pos = float4(inPos, 0.5f,  1.f);
    output.Texture = tex;

	return output;
}
