#include "AAnimatedImage.h"

#include "Component/Animation/UAnimator.h"

namespace LJG
{

	AAnimatedImage::AAnimatedImage(const WText& InKey)
		: AActor(InKey)
	{}

	AAnimatedImage::~AAnimatedImage() {}

	void AAnimatedImage::Initialize()
	{
		AActor::Initialize();
	}

	void AAnimatedImage::Update(float DeltaTime)
	{
		AActor::Update(DeltaTime);
	}

	void AAnimatedImage::Render()
	{
		AActor::Render();
	}

	void AAnimatedImage::Release()
	{
		AActor::Release();
	}

	void AAnimatedImage::Play(bool bReverse, bool bEnableLoop)
	{
		if (mAnimator)
		{
			mAnimator->PlayDefaultTrack(bReverse, bEnableLoop);
		}
	}

	void AAnimatedImage::SetScale(const FVector2f& InScale)
	{
		AActor::SetScale(InScale);
	}
}
