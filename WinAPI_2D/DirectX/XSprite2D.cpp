#include "XSprite2D.h"

#include <d3dcompiler.h>
#include "Context.h"
#include "XBlendState.h"
#include "XSamplerState.h"
#include "XTexture.h"


namespace LJG
{
	XSprite2D::XSprite2D(const std::wstring& TextureFile)
	{
		mPrimType  = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		mDrawColor = FLinearColor(0.f, 0.f, 0.f, 0);

		mVertexBufferArray.reserve(4);

		mTexture               = std::make_unique<XTexture>(TextureFile);
		mSamplerState          = std::make_unique<XSamplerState>();
		mBlendState_AlphaBlend = std::make_unique<XBlendState>(EBlendType::AlphaBlend);

		XSprite2D::Initialize();
	}

	XSprite2D::~XSprite2D()
	{
		XSprite2D::Release();
	}

	void XSprite2D::Initialize()
	{
		mTexture->Initialize();
		mSamplerState->Initialize();
		mBlendState_AlphaBlend->Initialize();

		AdjustTextureSize();

		XVertex2D::Initialize();
	}

	void XSprite2D::Update(float DeltaTime)
	{
		XVertex2D::Update(DeltaTime);
	}

	void XSprite2D::Render()
	{
		XVertex2D::Render();

		mTexture->Render();
		mSamplerState->Render();
		mBlendState_AlphaBlend->Render();

		Context::GetDeviceContext()->DrawIndexed(6, 0, 0);
	}

	void XSprite2D::Release()
	{
		XVertex2D::Release();

		mTexture = nullptr;

		mSamplerState = nullptr;

		mBlendState_AlphaBlend = nullptr;
	}

	void XSprite2D::AdjustTextureSize()
	{
		mScale.X = static_cast<float_t>(mTexture->GetTextureDesc().Width);
		mScale.Y = static_cast<float_t>(mTexture->GetTextureDesc().Height);
	}

	void XSprite2D::CreateVertexArray()
	{
		XVertex2D::CreateVertexArray();
	}

	void XSprite2D::CreateIndexArray()
	{
		mIndices =
		{
			0, 1, 2,
			0, 2, 3
		};
	}

	void XSprite2D::OnResizeCallback()
	{
	}
}
