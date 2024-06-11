#include "XBlendState.h"

#include "Context.h"

namespace LJG
{

	XBlendState::XBlendState(const EBlendType Type)
		: mBlendType(Type) {}

	XBlendState::~XBlendState()
	{
		XBlendState::Release();
	}

	void XBlendState::Initialize()
	{
		/**
		 * Blend 구조??
		 * RenderTarget[8] - 최?? 8개의 RenderTarget??블렌????정
		 * 
		 *	BlendEnable - ??성?????? 
		 *	
		 *	SrcBlend  - 블렌????산????용??는 ??스 ??
		 *	DestBlend - 블렌????산????용??는 ??????
		 *	BlendOp   - 블렌????산
		 *
		 *	SrcBlendAlpha  -
		 *	DestBlendAlpha - 
		 *	BlendOpAlpha   - 
		 *
		 *	RenderTargetWriteMask - ??더 ??켓의 ??상 마스??지??
		 */
		D3D11_BLEND_DESC blendDesc{};
		{
			blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL; // 모든 ??상 채널 ??성

			blendDesc.RenderTarget[0].BlendOp      = D3D11_BLEND_OP_ADD;
			blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

			blendDesc.RenderTarget[0].SrcBlendAlpha  = D3D11_BLEND_ZERO;
			blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

			switch (mBlendType)
			{
			case EBlendType::AlphaBlend:
				blendDesc.RenderTarget[0].BlendEnable = true;
				blendDesc.RenderTarget[0].SrcBlend  = D3D11_BLEND_SRC_ALPHA;
				blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
				break;
			case EBlendType::Additive:
				blendDesc.RenderTarget[0].BlendEnable = false;
				blendDesc.RenderTarget[0].SrcBlend  = D3D11_BLEND_ONE;
				blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
				break;
			}
		}

		CHECK_RESULT(Context::GetDevice()->CreateBlendState(&blendDesc, mBlendState.GetAddressOf()));
	}

	void XBlendState::Update(float DeltaTime) {}

	void XBlendState::Release()
	{
		mBlendState = nullptr;
	}

	void XBlendState::Render()
	{
		Context::GetDeviceContext()->OMSetBlendState(mBlendState.Get(), nullptr, 0xFF);
	}

}
