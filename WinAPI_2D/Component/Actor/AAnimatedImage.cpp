#include "AAnimatedImage.h"

#include "Component/Animation/UAnimator.h"
#include "Component/Animation/USpriteAnimation.h"

namespace LJG
{

	AAnimatedImage::AAnimatedImage(const WText& InKey)
		: AActor(InKey)
	{
		mAnimator = CreateDefaultSubObject<UAnimator>();
		mAnimator->SetOwnerActor(this);
	}

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

	void AAnimatedImage::PlayMontage() const
	{
		mAnimator->PlayMontageAnim(0);
	}

	void AAnimatedImage::SetMontage(USpriteAnimation* InAnim) const
	{
		mAnimator->SetMontageTrack(0, InAnim);
	}

	void AAnimatedImage::SetAnimation(USpriteAnimation* InAnim) const
	{
		mAnimator->SeteDefaultTrack(InAnim);
	}

	void AAnimatedImage::SetScale(const FVector2f& InScale)
	{
		AActor::SetScale(InScale);
		mAnimator->SetScale(InScale);
	}

	void AAnimatedImage::SetZOrder(const float_t InZOrder) const
	{
		mAnimator->SetZOrder(InZOrder);
	}
}
