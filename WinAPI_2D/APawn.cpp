#include "APawn.h"
#include "Camera.h"
#include "InputManager.h"
#include "Component/UAnimator.h"
#include "PlayerData.h"
#include "Component/UPawnMovementComponent2D.h"
#include "Component/UPlayerAnimator.h"
#include "Shape/UBoxComponent.h"

namespace LJG
{
	APawn::APawn()
	{
		APawn::Initialize();
	}

	APawn::~APawn()
	{
		APawn::Release();
	}

	void APawn::Initialize()
	{
		AActor::Initialize();


		// DELETE BELOW!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		{
			mCamera = CreateDefaultSubObject<ACamera>(L"Camera");
			mCamera->SetOwnerActor(this);
			mCamera->SetProjection(1024, 768);

			mDebugBox = CreateDefaultSubObject<UBoxComponent>(L"DebugBox");
			mDebugBox->SetScale({120.f, 120.f});
			mDebugBox->SetColor(FLinearColor::Green);
			mDebugBox->SetOwnerActor(this);

			mDebugBox2 = CreateDefaultSubObject<UBoxComponent>(L"DebugBox2");
			mDebugBox2->SetScale({200.f, 200.f});
			mDebugBox2->SetColor(FLinearColor::BlackPearl);
			mDebugBox2->SetOwnerActor(this);


			mAnimator = CreateDefaultSubObject<UPlayerAnimator>(L"PlayerAnimator");
			mAnimator->SetupAttachment(this);
			mAnimator->SetOwnerActor(this);
			mAnimator->Initialize();

			mMovementComponent = CreateDefaultSubObject<UPawnMovementComponent2D>(L"MovementComponent");
			mMovementComponent->SetupAttachment(this);
			mMovementComponent->SetOwnerActor(this);
			mMovementComponent->Initialize();
		}
	}

	void APawn::Update(float DeltaTime)
	{
		AActor::Update(DeltaTime);
		mCamera->SetPosition(mLocation);

		bool bMove = false;

		if (InputManager::IsKeyPressed(EKeyCode::D))
		{
			AddMovementInput({DeltaTime * mMovementComponent->GetMaxWalkSpeed(), 0.f});
			mAnimator->SetFlipX(false);
			bMove = true;
		}
		if (InputManager::IsKeyPressed(EKeyCode::A))
		{
			AddMovementInput({-DeltaTime * mMovementComponent->GetMaxWalkSpeed(), 0.f});
			mAnimator->SetFlipX(true);
			bMove = true;
		}

		if (InputManager::IsKeyDown(EKeyCode::Space))
		{
			mLocation += {0, 250 * DeltaTime};
		}

		if (!bMove)
		{
			mAnimator->SetState(EnumAsByte(EPlayerAnimState::Idle), true);
		}

		if (InputManager::IsKeyPressed(EKeyCode::X))
		{
			mAnimator->SetState(EnumAsByte(EPlayerAnimState::Attack), false);
		}
	}

	void APawn::AddMovementInput(const FVector2f& MovementInputAmount)
	{
		mMovementComponent->AddMovementInput(MovementInputAmount);
		mAnimator->SetState(EnumAsByte(EPlayerAnimState::Move), true);
		mLocation += MovementInputAmount;
	}
}
