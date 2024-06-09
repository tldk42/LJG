#include "USprite2D.h"

#include <d3dcompiler.h>
#include "Context.h"
#include "UDXHelper.h"
#include "XBlendState.h"
#include "XSamplerState.h"
#include "XTexture.h"


namespace LJG
{
	USprite2D::USprite2D(const std::wstring& TextureFile)
	{
		mPrimType  = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		mDrawColor = FLinearColor(0, 0, 0, 1);

		mVertexBufferArray.reserve(4);

		mTexture.reset(new XTexture(TextureFile));
		mSamplerState.reset(new XSamplerState());
		mBlendState_AlphaBlend.reset(new XBlendState(EBlendType::AlphaBlend));

		USprite2D::Initialize();
	}

	USprite2D::~USprite2D()
	{
		USprite2D::Release();
	}

	void USprite2D::Initialize()
	{
		SetWindowResolution();

		mTexture->Initialize();
		mSamplerState->Initialize();
		mBlendState_AlphaBlend->Initialize();

		AdjustTextureSize();

		XVertex2D::Initialize();
	}

	void USprite2D::Update(float DeltaTime)
	{
		XVertex2D::Update(DeltaTime);
	}

	void USprite2D::Render()
	{
		XVertex2D::Render();

		// 렌더링 리소스가 변경될 때 다시 호출 (각기 다른 텍스처로 설정 -> 렌더링)
		// Context::GetDeviceContext()->PSSetShaderResources(0, 1, mSRV.GetAddressOf());
		// Context::GetDeviceContext()->PSSetSamplers(0, 1, mSamplerState.GetAddressOf());

		mTexture->Render();
		mSamplerState->Render();
		mBlendState_AlphaBlend->Render();

		Context::GetDeviceContext()->DrawIndexed(6, 0, 0);
	}

	void USprite2D::Release()
	{
		XVertex2D::Release();

		mTexture = nullptr;

		mSamplerState = nullptr;

		mBlendState_AlphaBlend = nullptr;
	}

	void USprite2D::AdjustTextureSize()
	{
		const FVector2f cachedScale = mScale;

		mScale.X = static_cast<float_t>(mTexture->GetTextureDesc().Width) / mScreenResolution.X;
		mScale.Y = static_cast<float_t>(mTexture->GetTextureDesc().Height) / mScreenResolution.Y;

		if (const float overflowArea = mScale.GetMax(); overflowArea > 1)
		{
			mScale /= overflowArea;
		}

		for (FVertexBase& vertex : mVertexBufferArray)
		{
			vertex.Pos *= (mScale / cachedScale);
		}
	}

	void USprite2D::CreateVertexArray()
	{
		XVertex2D::CreateVertexArray();
	}

	void USprite2D::CreateIndexArray()
	{
		mIndices =
		{
			0, 1, 2,
			0, 2, 3
		};
	}

	void USprite2D::OnResizeCallback()
	{
		SetWindowResolution();
		AdjustTextureSize();
	}
}
