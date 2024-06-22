#pragma once
#include "CommonInclude.h"

namespace LJG
{
	class XShaderData : public ICoreAPI
	{
	public:
		explicit XShaderData(const WText& InKey, WTextView InVertexShader, WTextView InPixelShader);
		~XShaderData() override;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

		ID3D11VertexShader* GetVertexShader() const { return mVertexShader.Get(); }
		ID3D11PixelShader*  GetPixelShader() const { return mPixelShader.Get(); }
		ID3DBlob*           GetVertexShaderBuffer() const { return mVertexShaderBuf.Get(); }

	private:
		WText mKey;
		WText mVertexShaderFile;
		WText mPixelShaderFile;

#pragma region Shader
		ComPtr<ID3D11VertexShader> mVertexShader;
		ComPtr<ID3D11PixelShader>  mPixelShader;
		ComPtr<ID3DBlob>           mVertexShaderBuf;
#pragma endregion
	};
}
