#pragma once
#include "USceneComponent.h"
#include "DirectX/XTexture.h"

namespace LJG
{
	class UImage : public USceneComponent
	{
	public:
		explicit UImage(const WText& InKey, const WText& InPath, const float InZOrder);
		~UImage() override;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

		void SetTexture(XTexture* InTexture) const;

		void SetWorldLocation(const FVector2f& InLocation) override;
		void SetScale(const FVector2f& InScale) override;

	protected:
		WText         mTexturePath;
		XSprite2DUPtr mSprite2D;
	};
}
