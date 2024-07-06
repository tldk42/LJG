#include "AWindSprite.h"

#include "Component/Actor/APlayerCharacter.h"
#include "Component/Animation/UAnimator.h"
#include "Component/Animation/USpriteAnimation.h"
#include "Shape/UBoxComponent.h"

namespace LJG
{

	AWindSprite::AWindSprite()
		: AAnimatedImage(L"Croak's Wind Sprite")
	{
		mAnimator = CreateDefaultSubObject<UAnimator>();
		mAnimator->SetZOrder(0.3f);
		mAnimator->SetOwnerActor(this);
		mAnimator->AddState(0, CreateSprite(L"tallfrog_fan_wind"));
	}

	AWindSprite::~AWindSprite() {}

	void AWindSprite::Initialize()
	{
		AAnimatedImage::Initialize();
	}

	void AWindSprite::Update(float DeltaTime)
	{
		const float_t playerX = LocalPlayer.GetWorldLocation().X;
		if (mWindArea.Min.X < playerX && mWindArea.Max.X > playerX)
		{
			LocalPlayer.AddWorldLocation(FVector2f(-200.f, 0) * DeltaTime);
		}

		AAnimatedImage::Update(DeltaTime);
	}

	void AWindSprite::Render()
	{
		AAnimatedImage::Render();
	}

	void AWindSprite::Release()
	{
		AAnimatedImage::Release();
	}

	void AWindSprite::Play(bool bReverse, bool bEnableLoop)
	{
		AAnimatedImage::Play(bReverse, bEnableLoop);

		FVector2f windLoc = mOwnerActor->GetWorldLocation();
		windLoc.X         = 0.f;
		windLoc.Y         = 0.f;
		SetWorldLocation(windLoc);

		mWindArea.Min = windLoc - FVector2f(200.f, 100.f);
		mWindArea.Max = windLoc + FVector2f(200.f, 100.f);
	}
}
