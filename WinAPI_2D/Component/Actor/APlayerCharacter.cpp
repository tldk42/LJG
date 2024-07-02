#include "APlayerCharacter.h"

#include "Camera.h"
#include "InputManager.h"
#include "Component/Animation/UPlayerAnimator.h"
#include "Component/Movement/UPlayerMovementComponent.h"
#include "DirectX/Context.h"
#include "Helper/EngineHelper.h"
#include "Shape/UBoxComponent.h"
#include "Shape/ULineComponent.h"

namespace LJG
{
	APlayerCharacter::APlayerCharacter()
		: ACharacter(L"PC") {}

	void APlayerCharacter::Initialize()
	{

		mMovementComponent = CreateDefaultSubObject<UPlayerMovementComponent>();
		mMovementComponent->SetupAttachment(this);
		mMovementComponent->SetOwnerActor(this);
		mMovementComponent->Initialize();

		mAnimator = CreateDefaultSubObject<UPlayerAnimator>();
		mAnimator->SetupAttachment(this);
		mAnimator->SetOwnerActor(this);
		mAnimator->Initialize();

		ACharacter::Initialize();

		mDebugBox->SetScale({100.f, 135.f});

		Manager_Input.AddInputBinding(
			EKeyCode::Right, EKeyState::Pressed,
			std::bind(&APlayerCharacter::OnMovementInputPressed, this, std::placeholders::_1, false));
		Manager_Input.AddInputBinding(
			EKeyCode::Left, EKeyState::Pressed,
			std::bind(&APlayerCharacter::OnMovementInputPressed, this, std::placeholders::_1, true));

		Manager_Input.AddInputBinding(
			EKeyCode::X, EKeyState::Pressed,
			std::bind(&APlayerCharacter::Attack, this, true));
		Manager_Input.AddInputBinding(
			EKeyCode::X, EKeyState::Up,
			std::bind(&APlayerCharacter::Attack, this, false));

		Manager_Input.AddInputBinding(
			EKeyCode::Down, EKeyState::Down,
			std::bind(&UPlayerMovementComponent::TryCrouch, mMovementComponent));
		Manager_Input.AddInputBinding(
			EKeyCode::Down, EKeyState::Up,
			std::bind(&UPlayerMovementComponent::TryUnCrouch, mMovementComponent));

		Manager_Input.AddInputBinding(
			EKeyCode::Z, EKeyState::Down,
			std::bind(&APawn::Jump, this));


		Manager_Input.AddInputBinding(
			EKeyCode::LShift, EKeyState::Down,
			std::bind(&UPlayerMovementComponent::Dash, dynamic_cast<UPlayerMovementComponent*>(mMovementComponent)));

	}

	void APlayerCharacter::Update(float DeltaTime)
	{
		ACharacter::Update(DeltaTime);

		// if (!mMovementComponent->GetVelocity().IsNearlyZero())
		// {
		// 	MainCam.SetPosition(FMath::Lerp(MainCam.GetWorldLocation(), GetWorldLocation(), 5.f * DeltaTime));
		// }
	}

	void APlayerCharacter::AddMovementInput(const FVector2f& MovementInputAmount)
	{
		if (!mMovementComponent->IsCrouching())
		{
			mMovementComponent->AddMovementInput(MovementInputAmount);
			SetWorldLocation(GetWorldLocation() + MovementInputAmount);
		}
	}

	void APlayerCharacter::OnMovementInputPressed(float DeltaTime, bool bFlip)
	{
		const float_t moveDirection = bFlip
										  ? DeltaTime * -mMovementComponent->GetMaxWalkSpeed()
										  : DeltaTime * mMovementComponent->GetMaxWalkSpeed();

		if (mMovementComponent->GetVelocity().X * moveDirection >= 0)
		{
			mAnimator->SetFlipX(bFlip);

			AddMovementInput({
				moveDirection,
				0.f
			});
		}
	}

	void APlayerCharacter::Attack(bool bAttack)
	{
		bIsAttacking = bAttack;
	}


	void APlayerCharacter::OnTraceDown(const FVector2f, const FVector2f, FHitResult&)
	{}

}
