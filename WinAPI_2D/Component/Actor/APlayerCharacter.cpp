#include "APlayerCharacter.h"

#include "AProjectile.h"
#include "InputManager.h"
#include "Component/Animation/UPlayerAnimator.h"
#include "Component/Movement/UPlayerMovementComponent.h"
#include "DirectX/Context.h"
#include "Shape/UBoxComponent.h"

namespace LJG
{
	APlayerCharacter::APlayerCharacter()
		: ACharacter(L"PC") {}

	void APlayerCharacter::Initialize()
	{
		mDebugBox = CreateDefaultSubObject<UBoxComponent>(L"DebugBox", ETraceType::Pawn);
		mDebugBox->SetScale({125.f, 140.f});
		mDebugBox->SetColor(FLinearColor::Green);
		mDebugBox->SetOwnerActor(this);

		mMovementComponent = CreateDefaultSubObject<UPlayerMovementComponent>();
		mMovementComponent->SetupAttachment(this);
		mMovementComponent->SetOwnerActor(this);
		mMovementComponent->Initialize();

		mAnimator = CreateDefaultSubObject<UPlayerAnimator>();
		mAnimator->SetupAttachment(this);
		mAnimator->SetOwnerActor(this);
		mAnimator->Initialize();

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

	void APlayerCharacter::Shoot()
	{
		auto*      proj           = Manager_Object.Spawn<AProjectile>();
		const bool bFacingForward = !mAnimator->GetFlip();

		proj->SetOwnerActor(this);
		proj->SetWorldLocation({GetWorldLocation().X + (bFacingForward ? +65.f : -65.f), GetWorldLocation().Y});
		proj->SetVelocity({(bFacingForward ? 1200.f : -1200.f), 0.f});
		proj->SetDamage(50.f);
		proj->Launch();
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


}
