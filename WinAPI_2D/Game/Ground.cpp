#include "Ground.h"

#include "Component/UImage.h"
#include "Shape/UBoxComponent.h"

namespace LJG
{

	Ground::Ground(const WText& InText)
		: AActor(InText)
	{
		Initialize();
	}

	Ground::~Ground() {}

	void Ground::Initialize()
	{
		AActor::Initialize();

		mBoxComponent = CreateDefaultSubObject<UBoxComponent>(L"BoxComponent", ETraceType::Ground);
	}

	void Ground::SetTexture(WTextView InKey, WTextView InPath)
	{
		mImage = CreateDefaultSubObject<UImage>(WText(InKey), WText(InPath), 0.5f);
	}

	void Ground::SetBoxSize(const FVector2f& InSize) const
	{
		mBoxComponent->SetScale(InSize);
	}

	void Ground::SetWorldLocation(const FVector2f& InLocation)
	{
		AActor::SetWorldLocation(InLocation);
		if (mImage)
		{
			mImage->SetPosition(InLocation);
		}
		if (mBoxComponent)
		{
			mBoxComponent->SetWorldLocation(InLocation);
		}
	}

	void Ground::SetScale(const FVector2f& InScale)
	{
		AActor::SetScale(InScale);
		mImage->SetScale(InScale);
		mBoxComponent->SetScale(InScale);
	}

}
