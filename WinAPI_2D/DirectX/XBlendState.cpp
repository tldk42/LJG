#include "XBlendState.h"

#include "Context.h"
#include "Helper/UDXHelper.h"

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
		 * Blend 구조체
		 * RenderTarget[8] - 최대 8개의 RenderTarget에 블렌드 설정
		 * 
		 *	BlendEnable - 활성화 여부 
		 *	
		 *	SrcBlend  - 블렌딩 연산에 사용되는 소스 값
		 *	DestBlend - 블렌딩 연산에 사용되는 타겟 값
		 *	BlendOp   - 블렌딩 연산
		 *
		 *	SrcBlendAlpha  -
		 *	DestBlendAlpha - 
		 *	BlendOpAlpha   - 
		 *
		 *	RenderTargetWriteMask - 렌더 타켓의 색상 마스크 지정
		 */
		D3D11_BLEND_DESC blendDesc{};
		{
			blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL; // 모든 색상 채널 활성

			blendDesc.RenderTarget[0].BlendOp      = D3D11_BLEND_OP_ADD;
			blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

			blendDesc.RenderTarget[0].SrcBlendAlpha  = D3D11_BLEND_ONE;
			blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

			switch (mBlendType)
			{
			case EBlendType::AlphaBlend:
				blendDesc.RenderTarget[0].BlendEnable = true;
				blendDesc.RenderTarget[0].SrcBlend              = D3D11_BLEND_SRC_ALPHA;
				blendDesc.RenderTarget[0].DestBlend             = D3D11_BLEND_INV_SRC_ALPHA;
				blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
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
		static constexpr float_t blendFactor[4] = {0.0f, 0.0f, 0.0f, 0.0f};
		Context::GetDeviceContext()->OMSetBlendState(mBlendState.Get(), blendFactor, 0xffffffff);
	}

}
