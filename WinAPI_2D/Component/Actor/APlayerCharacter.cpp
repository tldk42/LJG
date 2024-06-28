#include "APlayerCharacter.h"

#include "Camera.h"
#include "InputManager.h"
#include "Component/UPawnMovementComponent2D.h"
#include "Component/Animation/UPlayerAnimator.h"
#include "DirectX/Context.h"

namespace LJG
{
	APlayerCharacter::APlayerCharacter()
		: ACharacter(L"PC") {}

	void APlayerCharacter::Initialize()
	{
		ACharacter::Initialize();

		Manager_Input.AddInputBinding(
			EKeyCode::D, EKeyState::Pressed,
			std::bind(&APlayerCharacter::OnMovementInputPressed, this, std::placeholders::_1, false));
		Manager_Input.AddInputBinding(
			EKeyCode::A, EKeyState::Pressed,
			std::bind(&APlayerCharacter::OnMovementInputPressed, this, std::placeholders::_1, true));

		Manager_Input.AddInputBinding(
			EKeyCode::Right, EKeyState::Pressed,
			std::bind(&APlayerCharacter::Attack, this, true));
		Manager_Input.AddInputBinding(
			EKeyCode::Right, EKeyState::Up,
			std::bind(&APlayerCharacter::Attack, this, false));

		Manager_Input.AddInputBinding(
			EKeyCode::S, EKeyState::Pressed,
			std::bind(&UPawnMovementComponent2D::TryCrouch, mMovementComponent));
		Manager_Input.AddInputBinding(
			EKeyCode::S, EKeyState::Up,
			std::bind(&UPawnMovementComponent2D::TryUnCrouch, mMovementComponent));

		Manager_Input.AddInputBinding(
			EKeyCode::Space, EKeyState::Down, std::bind(&APawn::Jump, this));

	}

	void APlayerCharacter::Update(float DeltaTime)
	{
		ACharacter::Update(DeltaTime);

		if (!mMovementComponent->GetVelocity().IsNearlyZero())
		{
			MainCam.SetPosition(FMath::Lerp(MainCam.GetWorldLocation(), GetWorldLocation(), 5.f * DeltaTime));
		}
	}

	void APlayerCharacter::AddMovementInput(const FVector2f& MovementInputAmount)
	{
		mMovementComponent->AddMovementInput(MovementInputAmount);
		SetWorldLocation(GetWorldLocation() + MovementInputAmount);
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

}
