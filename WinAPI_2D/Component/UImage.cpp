#include "UImage.h"

#include "DirectX/XSprite2D.h"
#include "Helper/EngineHelper.h"

namespace LJG
{

	UImage::UImage(const WText& InKey, const WText& InPath, const float InZOrder)
		: UObject(InKey),
		  mTexturePath(InPath)
	{
		mSprite2D = std::make_unique<XSprite2D>(mTexturePath, InZOrder);
	}

	UImage::~UImage()
	{}

	void UImage::Initialize()
	{
		UObject::Initialize();
	}

	void UImage::Update(float DeltaTime)
	{
		UObject::Update(DeltaTime);

		if (IsValid(mSprite2D.get()))
		{
			mSprite2D->Update(DeltaTime);
		}
	}

	void UImage::Render()
	{
		UObject::Render();

		if (IsValid(mSprite2D.get()))
		{
			mSprite2D->Render();
		}
	}

	void UImage::Release()
	{
		UObject::Release();
	}

	void UImage::SetPosition(const FVector2f& InLocation) const
	{
		if (IsValid(mSprite2D.get()))
		{
			mSprite2D->SetWorldLocation(InLocation);
		}
	}

	void UImage::SetScale(const FVector2f& InScale)
	{
		mSprite2D->SetScale(mSprite2D->GetScale() * InScale);
	}
}
