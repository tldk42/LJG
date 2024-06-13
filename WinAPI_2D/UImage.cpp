#include "UImage.h"

#include "XSprite2D.h"

namespace LJG
{
	UImage::UImage()
	{
	}

	UImage::~UImage()
	{
	}

	void UImage::Initialize()
	{
		UObject::Initialize();

		mSprite2D = std::make_unique<XSprite2D>(mImagePath);
		mSprite2D->Initialize();
	}

	void UImage::Update(float DeltaTime)
	{
		UObject::Update(DeltaTime);
	}

	void UImage::Render()
	{
		UObject::Render();
	}

	void UImage::Release()
	{
		UObject::Release();
	}

	void UImage::SetPosition(const FVector2f& InLocation)
	{
		mSprite2D->SetWorldLocation(InLocation);
	}
}
