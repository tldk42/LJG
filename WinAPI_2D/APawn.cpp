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


			mMovementComponent = CreateDefaultSubObject<UPawnMovementComponent2D>(L"MovementComponent");
			mMovementComponent->SetupAttachment(this);
			mMovementComponent->SetOwnerActor(this);
			mMovementComponent->Initialize();

			mAnimator = CreateDefaultSubObject<UPlayerAnimator>(L"PlayerAnimator");
			mAnimator->SetupAttachment(this);
			mAnimator->SetOwnerActor(this);
			mAnimator->Initialize();

			{
				InputManager::Get().AddInputBinding(
					EKeyCode::D, EKeyState::Pressed,
					std::bind(&APawn::OnMovementInputPressed, this, std::placeholders::_1, false));
				InputManager::Get().AddInputBinding(
					EKeyCode::A, EKeyState::Pressed,
					std::bind(&APawn::OnMovementInputPressed, this, std::placeholders::_1, true));
				InputManager::Get().AddInputBinding(
					EKeyCode::Space, EKeyState::Down, std::bind(&APawn::Jump, this));
				// InputManager::Get().AddInputBinding(
				// 	EKeyCode::LButton, EKeyState::Down, std::bind(&APawn::Attack, this));
			}


		}
	}

	void APawn::Update(float DeltaTime)
	{
		AActor::Update(DeltaTime);

		if (bAttacking)
			return;

		if (mMovementComponent->GetVelocity().IsNearlyZero())
		{
			bMove = false;
		}

		if (bMove)
		{
			mCamera->SetPosition(FMath::Lerp(mCamera->GetWorldLocation(), GetWorldLocation(), 5.f * DeltaTime));
		}
		else
		{
			// mAnimator->SetState(EnumAsByte(EPlayerAnimState::Idle), true);
		}
	}

	void APawn::AddMovementInput(const FVector2f& MovementInputAmount)
	{
		mMovementComponent->AddMovementInput(MovementInputAmount);
		// mAnimator->SetState(EnumAsByte(EPlayerAnimState::Move), true);
		SetWorldLocation(GetWorldLocation() + MovementInputAmount);
		bMove = true;
	}

	void APawn::OnMovementInputPressed(float DeltaTime, bool bFlip)
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

	void APawn::Jump()
	{
		mMovementComponent->Jump();
	}

	void APawn::Attack()
	{
		bAttacking = true;
		mAnimator->SetState(EnumAsByte(EPlayerAnimState::Attack), false);
	}
}
