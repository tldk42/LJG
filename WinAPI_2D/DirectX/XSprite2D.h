#pragma once
#include "XVertex2D.h"

namespace LJG
{
	class XSprite2D : public XVertex2D
	{
	public:
		XSprite2D(const float InZOrder = 0.6f);
		explicit XSprite2D(const WText& TextureFile, const float InZOrder = 0.6f);
		~XSprite2D() override;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

		inline XTexture* GetTexture() const { return mTexture; }

		inline void SetTexture(XTexture* InTexture)
		{
			mTexture = InTexture;
			AdjustTextureSize();
		}

	private:
		void AdjustTextureSize();

		void CreateVertexArray() override;
		void CreateIndexArray() override;

	private:
		friend class UObject;

	protected:
#pragma region Texture
		XTexture* mTexture;
#pragma endregion

#pragma region Sampler
		XSamplerStateUPtr mSamplerState;
#pragma endregion

#pragma region BlendState
		XBlendStateUPtr mBlendState_AlphaBlend;
#pragma endregion
	};
}
