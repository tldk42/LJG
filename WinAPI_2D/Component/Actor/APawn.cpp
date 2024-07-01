#include "APawn.h"

#include "InputManager.h"
#include "Component/Animation/UAnimator.h"
#include "Component/Animation/UPlayerAnimator.h"
#include "Component/Movement/UPawnMovementComponent2D.h"
#include "Shape/UBoxComponent.h"

namespace LJG
{
	APawn::APawn(const WText& InKey)
		: AActor(InKey)
	{}

	APawn::~APawn()
	{
		APawn::Release();
	}

	void APawn::Initialize()
	{
		AActor::Initialize();

		{
			mDebugBox = CreateDefaultSubObject<UBoxComponent>(L"DebugBox", ETraceType::Pawn);
			mDebugBox->SetScale({125.f, 140.f});
			mDebugBox->SetColor(FLinearColor::Green);
			mDebugBox->SetOwnerActor(this);

			if (!mMovementComponent)
			{
				mMovementComponent = CreateDefaultSubObject<UPawnMovementComponent2D>(L"MovementComponent");
				mMovementComponent->SetupAttachment(this);
				mMovementComponent->SetOwnerActor(this);
				mMovementComponent->Initialize();
			}

			mAnimator = CreateDefaultSubObject<UPlayerAnimator>(L"Animator");
			mAnimator->SetupAttachment(this);
			mAnimator->SetOwnerActor(this);
			mAnimator->Initialize();
		}
	}

	void APawn::Update(float DeltaTime)
	{
		AActor::Update(DeltaTime);
	}

	void APawn::Jump()
	{
		mMovementComponent->Jump();
	}

	void APawn::Attack(bool bAttack)
	{}
}
