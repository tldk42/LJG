struct VS_OUTPUT
{
	float4 Pos : SV_Position;
	float4 Color : COLOR;
};

VS_OUTPUT vs(float2 inPos : POSITION)
{
	VS_OUTPUT output;

    output.Pos = float4(inPos, 0.5f,  1.f);
    output.Color = float4(0.5f, 0.1f, 0.2f, 1.f);

	return output;
}
