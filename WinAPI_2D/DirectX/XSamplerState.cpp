#include "XSamplerState.h"

#include "Context.h"
#include "Helper/UDXHelper.h"

namespace LJG
{

	XSamplerState::XSamplerState(const UINT InSlot, const ESamplerType InSamplerType, const FLinearColor& InColor)
		: mSlot(InSlot),
		  mSamplerType(InSamplerType),
		  mColor(InColor)
	{}

	XSamplerState::~XSamplerState()
	{
		XSamplerState::Release();
	}

	void XSamplerState::Initialize()
	{
		D3D11_SAMPLER_DESC samplerDesc{};
		{
			samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
			samplerDesc.MinLOD         = 0;
			samplerDesc.MaxLOD         = D3D11_FLOAT32_MAX;

			memcpy(samplerDesc.BorderColor, mColor.RGBA, sizeof(FLinearColor));

			switch (mSamplerType)
			{
			case ESamplerType::PointWrap:
				samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
				samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
				samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
				samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
				break;
			case ESamplerType::LinearWrap:
				samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
				samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
				samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
				samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
				break;
			case ESamplerType::PointBorder:
				samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
				samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
				samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
				samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
				break;
			case ESamplerType::LinearBorder:
				samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
				samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
				samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
				samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
				break;
			}
		}

		CHECK_RESULT(Context::GetDevice()->CreateSamplerState(&samplerDesc, mSampler.GetAddressOf()));
	}

	void XSamplerState::Update(float DeltaTime)
	{}

	void XSamplerState::Render()
	{
		Context::GetDeviceContext()->PSSetSamplers(mSlot, 1, mSampler.GetAddressOf());
	}

	void XSamplerState::Release()
	{
		mSampler = nullptr;
	}
}
