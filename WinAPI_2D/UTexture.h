#pragma once
#include <d3d11.h>

#include "CommonInclude.h"

namespace LJG
{
	struct FTexVertex
	{
		FVector2f Pos;
		FVector2f Tex;
	};

	class UTexture : ICoreAPI
	{
	public:
		UTexture() = delete;
		explicit UTexture(const std::wstring& TextureFile = L"");
		~UTexture();


#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

	private:
		HRESULT LoadTextureFromFile(const std::wstring& TextureFile);
		void    AdjustTextureSize();
		HRESULT CreateTriangle();
		HRESULT CreateVertexBuffer();
		HRESULT CreateIndexBuffer();
		HRESULT LoadShaderAndInputLayout();
		HRESULT CreateSamplerState();
		HRESULT CreateConstantBuffer();

		void             SetShaderParams() const;
		static FVector2f GetWorldPositionToNormalized(const FVector2f& InPos);

	public:
		inline FVector2f GetWorldLocation() const { return mWorldLocation; }

		void SetWorldLocation(const FVector2f& InPos);
		void AddWorldLocation(const FVector2f& InPos);

	protected:
#pragma region Buffer & Layout
		ComPtr<ID3D11InputLayout> mVertexLayout;
		ComPtr<ID3D11Buffer>      mVertexBuffer;
		ComPtr<ID3D11Buffer>      mIndexBuffer;
		ComPtr<ID3D11Buffer>      mConstantBuffer;
		std::vector<FTexVertex>   mVertexBufferArray;
#pragma endregion

#pragma region Shader
		ComPtr<ID3D11VertexShader> mVertexShader;
		ComPtr<ID3D11PixelShader>  mPixelShader;
#pragma endregion

#pragma region Texture
		ComPtr<ID3D11Resource>           mTextureResource;
		ComPtr<ID3D11ShaderResourceView> mSRV;
		ComPtr<ID3D11Texture2D>          mTexture;
		ComPtr<ID3D11SamplerState>       mSamplerState;
		D3D11_SHADER_RESOURCE_VIEW_DESC  mSRVDesc;
		D3D11_TEXTURE2D_DESC             mTextureDesc;
#pragma endregion

#pragma region Transform
		FVector2f mScale              = FVector2f::UnitVector;
		FVector2f mWorldLocation      = FVector2f::ZeroVector;
		FVector2f mVertexOffset       = FVector2f::ZeroVector;
		FVector2f mNormalizedLocation = FVector2f::ZeroVector;
#pragma endregion

		D3D_PRIMITIVE_TOPOLOGY mPrimType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	};
}
