#include "APawn.h"

#include "InputManager.h"
#include "Component/Animation/UAnimator.h"
#include "Component/UPawnMovementComponent2D.h"
#include "Component/Animation/UPlayerAnimator.h"
#include "Helper/EngineHelper.h"
#include "Shape/UBoxComponent.h"
#include "Shape/ULineComponent.h"

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
			mDebugBox = CreateDefaultSubObject<UBoxComponent>(L"DebugBox");
			mDebugBox->SetScale({125.f, 150.f});
			mDebugBox->SetColor(FLinearColor::Green);
			mDebugBox->SetOwnerActor(this);

			mDebugLine = CreateDefaultSubObject<ULineComponent>(L"DebugLine");
			mDebugLine->SetScale({200.f, 200.f});
			mDebugLine->SetColor(FLinearColor::Green);
			mDebugLine->SetOwnerActor(this);

			mMovementComponent = CreateDefaultSubObject<UPawnMovementComponent2D>(L"MovementComponent");
			mMovementComponent->SetupAttachment(this);
			mMovementComponent->SetOwnerActor(this);
			mMovementComponent->Initialize();

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
