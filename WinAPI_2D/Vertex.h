#pragma once
#include <d3d11.h>

#include "CommonInclude.h"

namespace LJG
{
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

	private:
		HRESULT CreateTriangle();
		HRESULT CreateVertexBuffer();
		HRESULT CreateIndexBuffer();
		HRESULT LoadShaderAndInputLayout();
		HRESULT CreateConstantBuffer();

	protected:
#pragma region Buffer & Layout
		ID3D11InputLayout* mVertexLayout;
		ID3D11Buffer*      mVertexBuffer;
		ID3D11Buffer*      mIndexBuffer;
		ID3D11Buffer*      mConstantBuffer;
#pragma endregion

#pragma region Shader
		ID3D11VertexShader* mVertexShader;
		ID3D11PixelShader*  mPixelShader;
#pragma endregion

		D3D_PRIMITIVE_TOPOLOGY mPrimType;
	};
}
