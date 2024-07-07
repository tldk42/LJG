#include "AProjectileHitImage.h"
#include "Component/Animation/USpriteAnimation.h"
#include "Component/Animation/UAnimator.h"

namespace LJG
{
	int32_t AProjectileHitImage::mCounter = 0;

	AProjectileHitImage::AProjectileHitImage()
		: AAnimatedImage(std::format(L"HitParticle{}", mCounter++))
	{
		bIsPoolManaged = true;

		// mAnimator->GetDefaultTrack()->OnAnimFinished.Bind([&](){
		// 	SetActive(false);
		// });

	}

	AProjectileHitImage::~AProjectileHitImage() {}

	void AProjectileHitImage::Initialize()
	{
		AAnimatedImage::Initialize();
	}

	void AProjectileHitImage::Update(float DeltaTime)
	{
		AAnimatedImage::Update(DeltaTime);
	}

	void AProjectileHitImage::Render()
	{
		AAnimatedImage::Render();
	}

	void AProjectileHitImage::Release()
	{
		AAnimatedImage::Release();
	}
}
