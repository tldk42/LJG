#pragma once
#include "UObject.h"

namespace LJG
{
	class UImage : UObject
	{
	public:
		UImage();
		~UImage() override;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

		void SetPosition(const FVector2f& InLocation);

	protected:
		WText         mImagePath;
		XSprite2DUPtr mSprite2D;
	};
}
