#include "APawn.h"

#include <memory>

#include "InputManager.h"
#include "UAnimator.h"
#include "PlayerData.h"
#include "UPawnMovementComponent2D.h"
#include "UPlayerAnimator.h"
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
			mDebugBox = std::make_unique<UBoxComponent>();
			mDebugBox->Initialize();
			mDebugBox->SetScale({120.f, 120.f});
			mDebugBox->SetColor(FLinearColor::Green);
			mDebugBox->SetOwnerActor(this);

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


		mDebugBox->Update(DeltaTime);

		bool bMove = false;


		if (InputManager::IsKeyPressed(EKeyCode::D))
		{
			AddMovementInput({DeltaTime, 0.f});
			bMove = true;
		}
		if (InputManager::IsKeyPressed(EKeyCode::S))
		{
			AddMovementInput({0.f, -DeltaTime});
			bMove = true;
		}
		if (InputManager::IsKeyPressed(EKeyCode::W))
		{
			AddMovementInput({0.f, DeltaTime});
			bMove = true;
		}
		if (InputManager::IsKeyPressed(EKeyCode::A))
		{
			AddMovementInput({-DeltaTime, 0.f});
			bMove = true;
		}

		if (!bMove)
		{
			mAnimator->SetState(EnumAsByte(EPlayerAnimState::Idle), true);
		}

		if (InputManager::IsKeyPressed(EKeyCode::X))
		{
			mAnimator->SetState(EnumAsByte(EPlayerAnimState::Attack), false);
		}
		else
		{
			mTestRotation = 0.f;
		}
	}

	void APawn::Render()
	{
		AActor::Render();

		mDebugBox->Render();
	}

	void APawn::Release()
	{
		AActor::Release();
	}

	void APawn::AddMovementInput(const FVector2f& MovementInputAmount)
	{
		mMovementComponent->AddMovementInput(MovementInputAmount);
		mAnimator->SetState(EnumAsByte(EPlayerAnimState::Move), true);
		mLocation += (MovementInputAmount * mMovementComponent->GetMaxWalkSpeed());
	}
}
