#include "XSprite2D.h"

#include <d3dcompiler.h>
#include "Context.h"
#include "XBlendState.h"
#include "XSamplerState.h"
#include "XTexture.h"
#include "Component/Manager/TextureManager.h"


namespace LJG
{
	XSprite2D::XSprite2D(const float InZOrder)
		: XVertex2D(InZOrder)
	{
		mPrimType  = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		mDrawColor = FLinearColor(1.f, 1.f, 1.f, 1.f);

		mVertexBufferArray.reserve(4);

		mSamplerState          = std::make_unique<XSamplerState>();
		mBlendState_AlphaBlend = std::make_unique<XBlendState>(EBlendType::AlphaBlend);
		XSprite2D::Initialize();
	}

	XSprite2D::XSprite2D(const WText& TextureFile, const float InZOrder)
		: XVertex2D(InZOrder)
	{
		mPrimType  = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		mDrawColor = FLinearColor(1.f, 1.f, 1.f, 1.f);

		mVertexBufferArray.reserve(4);

		mTexture               = Manager_Texture.CreateOrLoad(TextureFile);
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
		if (mTexture)
		{
			XVertex2D::Render();

			mTexture->Render();
			mSamplerState->Render();
			mBlendState_AlphaBlend->Render();

			Context::GetDeviceContext()->DrawIndexed(6, 0, 0);
		}
	}

	void XSprite2D::Release()
	{
		XVertex2D::Release();

		mTexture = nullptr;

		mSamplerState = nullptr;

		mBlendState_AlphaBlend = nullptr;
	}

	void XSprite2D::AdjustRGBA(const FLinearColor& InColor)
	{
		for (FVertexBase& vertex : mVertexBufferArray)
		{
			vertex.Color = InColor;
		}
		SetShaderParams();
	}

	void XSprite2D::AdjustRGBA(float R, float G, float B, float A)
	{
		for (FVertexBase& vertex : mVertexBufferArray)
		{
			vertex.Color.R = R;
			vertex.Color.G = G;
			vertex.Color.B = B;
			vertex.Color.A = A;
		}
		SetShaderParams();
	}

	void XSprite2D::AdjustTextureSize()
	{
		if (mTexture)
		{
			mTextureScale.X = mTexture->GetTextureDesc().Width;
			mTextureScale.Y = mTexture->GetTextureDesc().Height;

			SetScale(mTextureScale);
		}

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

}
