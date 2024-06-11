#include "APlayerController.h"

#include <memory>

#include "InputManager.h"
#include "UAnimator.h"
#include "PlayerData.h"
#include "UAnimation.h"
#include "XSprite2D.h"
#include "Debug/UDebugBox2D.h"

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
			mDebugBox->SetScale({150.f, 150.f});

			mAnimator = std::make_shared<UAnimator>();


			std::vector<FAnimData> idleAnimSet;
			std::vector<FAnimData> moveAnimSet;
			std::vector<FAnimData> attackAnimSet;

			for (int32_t i = 1; i <= 60; ++i)
			{
				std::wstringstream ss;
				ss << L"rsc/ND/Idle/LD_Idle_" << std::setw(4) << std::setfill(L'0') << i << L".png";
				std::wstring filePath = ss.str();
				idleAnimSet.emplace_back(new XSprite2D(filePath), 1.f / 60);
			}
			for (int32_t i = 1; i <= 5; ++i)
			{
				std::wstringstream ss;
				ss << L"rsc/ND/Move/LD_Run_" << std::setw(4) << std::setfill(L'0') << i << L".png";
				std::wstring filePath = ss.str();
				moveAnimSet.emplace_back(new XSprite2D(filePath), 1.f / 20);
			}
			for (int32_t i = 1; i <= 22; ++i)
			{
				std::wstringstream ss;
				ss << L"rsc/ND/Attack/LD_Combo2b_" << std::setw(4) << std::setfill(L'0') << i << L".png";
				std::wstring filePath = ss.str();
				attackAnimSet.emplace_back(new XSprite2D(filePath), 1.f / 22);
			}

			mAnimator->AddState(EnumAsByte(EPlayerAnimState::Idle), std::make_shared<UAnimation>(idleAnimSet));
			mAnimator->AddState(EnumAsByte(EPlayerAnimState::Move), std::make_shared<UAnimation>(moveAnimSet));
			mAnimator->AddState(EnumAsByte(EPlayerAnimState::Attack), std::make_shared<UAnimation>(attackAnimSet));


			mAnimator->SetOwnerActor(this);
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

		if (InputManager::IsKeyPressed(EKeyCode::X))
		{
			mAnimator->SetState(EnumAsByte(EPlayerAnimState::Attack), false);
			bIsAttacking = true;
		}

		mAnimator->Update(DeltaTime);
	}

	void APlayerController::Render()
	{
		AActor::Render();

		mDebugBox->Render();

		mAnimator->Render();
	}

	void APlayerController::Release()
	{
		AActor::Release();
	}

	void APlayerController::AddMovementInput(const FVector2f& MovementInputAmount)
	{
		mAnimator->SetState(EnumAsByte(EPlayerAnimState::Move), true);
		mLocation += MovementInputAmount;
	}
}
