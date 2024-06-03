struct VS_OUTPUT
{
	float4 Pos : SV_Position;
	float4 Color : COLOR;
};

VS_OUTPUT vs(float2 inPos : POSITION)
{
	VS_OUTPUT output;

    output.Pos = float4(inPos, 0.5f,  1.f);
    output.Color = float4(1, 0.58, 0.059, 1.f);

	return output;
}
