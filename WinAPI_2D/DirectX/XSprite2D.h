#pragma once
#include "XVertex2D.h"

namespace LJG
{
	class XSprite2D : public XVertex2D
	{
	public:
		XSprite2D() = delete;
		explicit XSprite2D(const std::wstring& TextureFile = L"");
		~XSprite2D() override;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

	private:
		void AdjustTextureSize();

		void CreateVertexArray() override;
		void CreateIndexArray() override;

	private:
		void OnResizeCallback() override;
		friend class UObject;

	protected:
#pragma region Texture
		XTextureUPtr mTexture;
#pragma endregion

#pragma region Sampler
		XSamplerStateUPtr mSamplerState;
#pragma endregion

#pragma region BlendState
		XBlendStateUPtr mBlendState_AlphaBlend;
#pragma endregion
	};
}
