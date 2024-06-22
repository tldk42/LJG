#pragma once
#include "CommonInclude.h"
namespace LJG
{
	class XLayer : public ICoreAPI
	{
	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

	protected:
		ComPtr<ID3D11Texture2D>          mLayerTexture;
		ComPtr<ID3D11RenderTargetView>   mLayerRTV;
		ComPtr<ID3D11ShaderResourceView> mLayerSRV;
	};
}
