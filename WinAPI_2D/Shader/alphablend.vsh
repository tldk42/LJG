cbuffer WorldMatrixBuffer : register(b0)
{
    matrix world;
}

cbuffer ViewProjectionBuffer : register(b1)
{
    matrix view;
}

cbuffer ProjectionBuffer : register(b2)
{
    matrix projection;
}

struct VS_INPUT
{
    float3 Pos : POSITION;
    float4 Col : COLOR;
    float2 Tex : TEX;
};

struct VS_OUTPUT
{
	float4 Pos : SV_Position;
	float4 Col : COLOR;
	float2 Tex : TEXCOORD0;
};

VS_OUTPUT vs(VS_INPUT input)
{
	VS_OUTPUT output;

    output.Pos = float4(input.Pos,  1.f);
    
    output.Pos = mul(output.Pos, world);
    output.Pos = mul(output.Pos, view);
    output.Pos = mul(output.Pos, projection);

    output.Tex = input.Tex;
    output.Col = input.Col;

	return output;
}
