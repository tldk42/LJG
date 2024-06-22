#include "XLayer.h"

#include "Context.h"

namespace LJG
{
	void XLayer::Initialize()
	{
		D3D11_TEXTURE2D_DESC texture2DDesc{};
		{
			texture2DDesc.Width            = Context::GetViewportSize().X;
			texture2DDesc.Height           = Context::GetViewportSize().Y;
			texture2DDesc.MipLevels        = 1;
			texture2DDesc.ArraySize        = 1;
			texture2DDesc.Format           = DXGI_FORMAT_R8G8B8A8_UNORM;
			texture2DDesc.SampleDesc.Count = 1;
			texture2DDesc.Usage            = D3D11_USAGE_DEFAULT;
			texture2DDesc.BindFlags        = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		}

		Context::GetDevice()->CreateTexture2D(&texture2DDesc, nullptr, mLayerTexture.GetAddressOf());
		Context::GetDevice()->CreateRenderTargetView(mLayerTexture.Get(), nullptr, mLayerRTV.GetAddressOf());
		Context::GetDevice()->CreateShaderResourceView(mLayerTexture.Get(), nullptr, mLayerSRV.GetAddressOf());
	}

	void XLayer::Update(float DeltaTime) {}

	void XLayer::Render()
	{
		Context::GetDeviceContext()->OMSetRenderTargets(1, mLayerRTV.GetAddressOf(), nullptr);
	}

	void XLayer::Release() {}
}
