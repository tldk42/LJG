#pragma once
#include <d3d11.h>

#include "CommonInclude.h"

namespace LJG::Utils
{
	class Timer;
}

namespace LJG
{
	struct SimpleVertex
	{
		float x;
		float y;
	};

	class Vertex : ICoreAPI
	{
	public:
		Vertex();
		~Vertex();

#pragma region Core Interface
		void Initialize() override;
		void Update() override;
		void Render() override;
		void Release() override;
#pragma endregion

	public:
		HRESULT CreateTriangle();
		HRESULT LoadShaderAndInputLayout();
		HRESULT CreateVertexBuffer();
		HRESULT CreateIndexBuffer();
		HRESULT CreateConstantBuffer();

	protected:
		ID3D11InputLayout* mVertexLayout;
		ID3D11Buffer*      mVertexBuffer;
		ID3D11Buffer*      mIndexBuffer;
		ID3D11Buffer*      mConstantBuffer;

		ID3D11VertexShader*    mVertexShader;
		ID3D11PixelShader*     mPixelShader;
		D3D_PRIMITIVE_TOPOLOGY mPrimType;
	};
}
