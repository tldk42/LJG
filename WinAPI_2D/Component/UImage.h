#pragma once
#include "UObject.h"

namespace LJG
{
	class UImage : public UObject
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

		void SetPosition(const FVector2f& InLocation) const;

	protected:
		WText         mTexturePath;
		XSprite2DUPtr mSprite2D;
	};
}
