#include "APlayerCharacter.h"

#include "AProjectile.h"
#include "InputManager.h"
#include "Component/Animation/UPlayerAnimator.h"
#include "Component/Movement/UPlayerMovementComponent.h"
#include "DirectX/Context.h"
#include "Game/Actor/AEnemy.h"
#include "Game/Object/Common/InGame_HUD.h"
#include "Game/Object/Game_2/Enemy/FrogProjectile.h"
#include "Helper/EngineHelper.h"
#include "Shape/UBoxComponent.h"

namespace LJG
{
	APlayerCharacter::APlayerCharacter()
		: ACharacter(L"PC"),
		  bIsAttacking(false),
		  mCurrentHP(5),
		  mMaxHP(5)
	{}

	void APlayerCharacter::Initialize()
	{

		mDebugBox = CreateDefaultSubObject<UBoxComponent>(L"DebugBox", ETraceType::Pawn);
		mDebugBox->SetScale({100.f, 135.f});
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
			EKeyCode::Up, EKeyState::Pressed,
			std::bind(&APlayerCharacter::LookUpTarget, this, true));
		Manager_Input.AddInputBinding(
			EKeyCode::Up, EKeyState::Up,
			std::bind(&APlayerCharacter::LookUpTarget, this, false));

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

		GAME_HUD.OnHPChanged(mCurrentHP);

		mDebugBox->OnCollisionEnter_Delegate.Bind(std::bind(&APlayerCharacter::OnCollisionEnter, this,
															std::placeholders::_1));
	}

	void APlayerCharacter::Update(float DeltaTime)
	{
		ACharacter::Update(DeltaTime);

		// if (!mMovementComponent->GetVelocity().IsNearlyZero())
		// {
		// 	MainCam.SetPosition(FMath::Lerp(MainCam.GetWorldLocation(), GetWorldLocation(), 5.f * DeltaTime));
		// }
	}

	float APlayerCharacter::GetCurrentHealth()
	{
		return 0.f;
	}

	float APlayerCharacter::GetMaxHealth()
	{
		return 0.f;
	}

	void APlayerCharacter::OnDead() {}

	void APlayerCharacter::OnHit(float InDamage)
	{
		mCurrentHP--;

		// if (mCurrentHP < 0)
		// {
		// 	OnDead();
		// }
		//
		// FMath::Clamp(mCurrentHP, 0, mMaxHP);
		// GAME_HUD.OnHPChanged(mCurrentHP);
	}

	void APlayerCharacter::Shoot()
	{
		auto*      proj           = Manager_Object.Spawn<AProjectile>();
		const bool bFacingForward = !mAnimator->GetFlip();


		FVector2f ProjectileStartLoc = {GetWorldLocation().X + (bFacingForward ? +65.f : -65.f), GetWorldLocation().Y};
		FVector2f ProjectileVelocity = {(bFacingForward ? 1200.f : -1200.f), 0.f};
		proj->SetWorldRotation(0.f);
		if (bAttackingUp)
		{
			proj->SetWorldRotation(90.f);
			ProjectileStartLoc = {GetWorldLocation().X, GetWorldLocation().Y + 70.f};
			ProjectileVelocity = {0.f, 1200.f};
		}
		else if (bAttackingDiagonalUp)
		{
			proj->SetWorldRotation(bFacingForward ? 45.f : -45.f);
			ProjectileStartLoc = {GetWorldLocation().X + (bFacingForward ? +45.f : -45.f), GetWorldLocation().Y + 45.f};
			ProjectileVelocity = {(bFacingForward ? 900.f : -1000.f), 1000.f};
		}


		proj->SetOwnerActor(this);
		proj->SetWorldLocation(ProjectileStartLoc);
		proj->SetVelocity(ProjectileVelocity);
		proj->SetDamage(20.f);
		proj->Launch();
	}

	void APlayerCharacter::AddMovementInput(const FVector2f& MovementInputAmount)
	{
		if (!mMovementComponent->IsCrouching())
		{
			mMovementComponent->AddMovementInput(MovementInputAmount);
			AddWorldLocation(MovementInputAmount);
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

	void APlayerCharacter::LookUpTarget(const bool bLookUp)
	{
		if (bIsAttacking)
		{
			if (FMath::Abs(mMovementComponent->GetVelocity().X) > 10.f && bLookUp)
			{
				bAttackingUp         = false;
				bAttackingDiagonalUp = true;
			}
			else if (bLookUp)
			{
				bAttackingDiagonalUp = false;
				bAttackingUp         = true;
			}
			else
			{
				bAttackingUp         = false;
				bAttackingDiagonalUp = false;
			}
		}
		else
		{
			bAttackingUp         = false;
			bAttackingDiagonalUp = false;
		}
	}

	void APlayerCharacter::Attack(bool bAttack)
	{
		bIsAttacking = bAttack;
	}

	void APlayerCharacter::OnCollisionEnter(FHitResult_Box2D& HitResult)
	{
		if (HitResult.Src->GetTraceType() == ETraceType::Pawn || HitResult.Dest->GetTraceType() == ETraceType::Pawn)
		{
			if (AEnemy* enemyObj = dynamic_cast<AEnemy*>(HitResult.Src->GetOwnerActor()))
			{
				LOG_CORE_INFO("Player Overlapped By{}", WText2Text(enemyObj->GetName()));
				OnHit(0);
			}
			else if (HitResult.Src->GetTraceType() == ETraceType::Projectile)
			{
				if (dynamic_cast<FrogProjectile*>(HitResult.Src->GetOwnerActor()))
				{
					OnHit(0);
				}
			}
		}
	}


}
