#include "APawn.h"
#include "Camera.h"
#include "InputManager.h"
#include "Component/UAnimator.h"
#include "Component/UPawnMovementComponent2D.h"
#include "DirectX/XTexture.h"
#include "Component/USpriteAnimation.h"
#include "DirectX/Context.h"
#include "Helper/EngineHelper.h"
#include "Shape/UBoxComponent.h"

namespace LJG
{
	APawn::APawn(const WText& InKey)
		: AActor(InKey)
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
			mCamera->SetProjection(Context::GetViewportSize().X, Context::GetViewportSize().Y);

			mDebugBox = CreateDefaultSubObject<UBoxComponent>(L"DebugBox");
			mDebugBox->SetScale({180.f, 180.f});
			mDebugBox->SetColor(FLinearColor::GreenPea);
			mDebugBox->SetOwnerActor(this);

			mMovementComponent = CreateDefaultSubObject<UPawnMovementComponent2D>(L"MovementComponent");
			mMovementComponent->SetupAttachment(this);
			mMovementComponent->SetOwnerActor(this);
			mMovementComponent->Initialize();

			mSprite = CreateDefaultSubObject<USpriteAnimation>(L"PlayerAnimation");
			mSprite->SetAnimData(AnimUtil::LoadAnimations(L"rsc/Player/chalice_idle_", 10, 10.f, true));
			mSprite->SetupAttachment(this);
			mSprite->SetOwnerActor(this);
			mSprite->Play(true);

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
			// mAnimator->SetFlipX(bFlip);

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
		// mAnimator->SetState(EnumAsByte(EPlayerAnimState::Attack), false);
	}
}
