#pragma once
#include "CommonInclude.h"

namespace LJG
{
	class XTexture : public ICoreAPI
	{
	public:
		explicit XTexture(const WText& InKey, UINT InSlot = 0);
		~XTexture() override;

#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

		inline D3D11_TEXTURE2D_DESC      GetTextureDesc() const { return mTextureDesc; }
		inline ID3D11ShaderResourceView* GetShaderResourceView() const { return mSRV.Get(); }

	private:
		UINT                             mSlot;
		WText                            mKey;
		ComPtr<ID3D11Resource>           mTextureResource;
		ComPtr<ID3D11ShaderResourceView> mSRV;
		ComPtr<ID3D11Texture2D>          mTexture;
		D3D11_SHADER_RESOURCE_VIEW_DESC  mSRVDesc;
		D3D11_TEXTURE2D_DESC             mTextureDesc;

	};

}
