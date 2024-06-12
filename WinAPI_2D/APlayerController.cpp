#include "APlayerController.h"

#include <memory>

#include "InputManager.h"
#include "UAnimator.h"
#include "PlayerData.h"
#include "UPlayerAnimator.h"
#include "Shape/UDebugBox2D.h"

namespace LJG
{
	APlayerController::APlayerController()
	{
		APlayerController::Initialize();
	}

	APlayerController::~APlayerController()
	{
		APlayerController::Release();
	}

	void APlayerController::Initialize()
	{
		AActor::Initialize();


		// DELETE BELOW!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		{
			mDebugBox = std::make_unique<UDebugBox2D>();
			mDebugBox->Initialize();
			mDebugBox->SetScale({120.f, 120.f});
			mDebugBox->SetColor({1, 0, 0, 1});

			mAnimator = CreateDefaultSubObject<UPlayerAnimator>(L"PlayerAnimator");
			mAnimator->Initialize();
			mAnimator->SetOwnerActor(this);

			// mAnimator = CreateDefaultSubObject<UAnimator>(L"PlayerAnimator");
			//
			//
			//
			// mAnimator->AddState(EnumAsByte(EPlayerAnimState::Idle), std::make_shared<UAnimation>(idleAnimSet));
			// mAnimator->AddState(EnumAsByte(EPlayerAnimState::Move), std::make_shared<UAnimation>(moveAnimSet));
			// mAnimator->AddState(EnumAsByte(EPlayerAnimState::Attack), std::make_shared<UAnimation>(attackAnimSet));
			//
			//
			// mAnimator->SetOwnerActor(this);
		}
	}

	void APlayerController::Update(float DeltaTime)
	{
		AActor::Update(DeltaTime);

		mDebugBox->SetWorldLocation(mLocation);

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

		if (InputManager::IsKeyPressed(EKeyCode::X) )
		{
			mAnimator->SetState(EnumAsByte(EPlayerAnimState::Attack), false);
			bIsAttacking = true;
		}
		
	}

	void APlayerController::Render()
	{
		AActor::Render();

		mDebugBox->Render();
	}

	void APlayerController::Release()
	{
		AActor::Release();
	}

	void APlayerController::AddMovementInput(const FVector2f& MovementInputAmount)
	{
		mAnimator->SetState(EnumAsByte(EPlayerAnimState::Move), true);
		mLocation += (MovementInputAmount * .1f);
	}
}
