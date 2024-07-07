#include "APlayerCharacter.h"

#include "AAnimatedImage.h"
#include "AProjectile.h"
#include "InputManager.h"
#include "PlayerData.h"
#include "Component/Animation/UPlayerAnimator.h"
#include "Component/Manager/AnimManager.h"
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
		if (!bInitialized)
		{
			mShootParticle = CreateDefaultSubObject<AAnimatedImage>(L"ShootParticle");
			mShootParticle->SetOwnerActor(this);
			mShootParticle->SetAnimation(CreateSprite(L"cuphead_shoot_particle_head"));
			mShootParticle->SetZOrder(0.1f);

			mMoveParticle = CreateDefaultSubObject<AAnimatedImage>(L"MoveParticle");
			mMoveParticle->SetOwnerActor(this);
			mMoveParticle->SetZOrder(0.1f);

			HitParticle_Ground = CreateSprite(L"cuphead_dust");
			HitParticle_Jump   = CreateSprite(L"cuphead_dust_jump");

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
				EKeyCode::V, EKeyState::Down,
				std::bind(&APlayerCharacter::ExecSkill, this));


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
				std::bind(&APlayerCharacter::Jump, this));

			Manager_Input.AddInputBinding(
				EKeyCode::LShift, EKeyState::Down,
				std::bind(&UPlayerMovementComponent::Dash, dynamic_cast<UPlayerMovementComponent*>(mMovementComponent)));

			GAME_HUD.OnHPChanged(mCurrentHP);

			mDebugBox->OnCollisionEnter_Delegate.Bind(std::bind(&APlayerCharacter::OnCollisionEnter, this,
																std::placeholders::_1));

			bInitialized = true;
		}

		
	}

	void APlayerCharacter::Update(float DeltaTime)
	{
		ACharacter::Update(DeltaTime);

		UpdateMuzzleLocation();

		if (bExecSkill)
		{
			HandleSkillMovement(DeltaTime);
		}
		if (bIsAttacking && !mAnimator->IsAnyMontagePlaying())
		{
			HandleAttack(DeltaTime);
		}
	}

	float APlayerCharacter::GetCurrentHealth()
	{
		return 0.f;
	}

	float APlayerCharacter::GetMaxHealth()
	{
		return 0.f;
	}

	void APlayerCharacter::AddMP(const int32_t InValue)
	{
		mCurrentMP = FMath::Clamp(mCurrentMP + InValue, 0, 500);

		GAME_HUD.OnMPChanged(mCurrentMP);
	}

	void APlayerCharacter::OnDead() {}

	void APlayerCharacter::OnHit(float InDamage)
	{

		// Parry °¡´É & Parrying
		if (InDamage == 0 && bParrying)
		{
			HandleParry();
		}
		else
		{
			mCurrentHP--;
			mAnimator->PlayMontageAnim(EnumAsByte(EPlayerMontages::Hit));
		}

		// if (mCurrentHP < 0)
		// {
		// 	OnDead();
		// }
		//
		// FMath::Clamp(mCurrentHP, 0, mMaxHP);
		// GAME_HUD.OnHPChanged(mCurrentHP);
	}

	void APlayerCharacter::SpawnShootProjectile(AProjectile*& proj)
	{
		proj = Manager_Object.Spawn<AProjectile>();
		proj->SetOwnerActor(this);
		const bool bFacingForward = !mAnimator->GetFlip();

		FVector2f ProjectileVelocity = {(bFacingForward ? 1200.f : -1200.f), 0.f};
		proj->SetWorldRotation(0.f);
		if (bAttackingUp)
		{
			proj->SetWorldRotation(90.f);
			ProjectileVelocity = {0.f, 1200.f};
		}
		else if (bAttackingDiagonalUp)
		{
			proj->SetWorldRotation(bFacingForward ? 45.f : -45.f);
			ProjectileVelocity = {(bFacingForward ? 900.f : -1000.f), 1000.f};
		}

		proj->SetWorldLocation(mMuzzleLocation);
		proj->SetVelocity(ProjectileVelocity);
	}

	void APlayerCharacter::PlayDust() const
	{
		mMoveParticle->SetWorldLocation(FVector2f(GetWorldLocation().X, GetWorldLocation().Y - 40.f));
		mMoveParticle->SetAnimation(HitParticle_Ground);
		mMoveParticle->Play();
	}

	void APlayerCharacter::PlayJumpDust() const
	{
		mMoveParticle->SetWorldLocation(FVector2f(GetWorldLocation().X, GetWorldLocation().Y - 40.f));
		mMoveParticle->SetAnimation(HitParticle_Jump);
		mMoveParticle->Play();
	}

	void APlayerCharacter::Shoot()
	{
		AProjectile* proj;
		SpawnShootProjectile(proj);

		proj->SetDamage(20.f);
		proj->SetCollisionBoxSize({80, 40});
		proj->SetAnimation(*Manager_Anim.GetResource(L"projectile_shoot"));
		proj->SetHitAnimation(*Manager_Anim.GetResource(L"cuphead_shoot_particle_hit"));
		proj->Launch();

		mShootParticle->Play();
	}

	void APlayerCharacter::ShootEx()
	{
		AProjectile* proj;
		SpawnShootProjectile(proj);

		proj->SetDamage(50.f);
		proj->SetCollisionBoxSize({100, 100});
		proj->SetAnimation(*Manager_Anim.GetResource(L"PeaShoot_Ex"));
		proj->SetHitAnimation(*Manager_Anim.GetResource(L"cuphead_shoot_particle_ex_hit"));
		proj->Launch();

		mShootParticle->Play();
	}

	void APlayerCharacter::Jump()
	{
		if (!mAnimator->IsAnyMontagePlaying())
		{
			if (!mMovementComponent->IsJumping())
			{
				if (mMovementComponent->IsCrouching() && !bMovingOnLand)
				{
					AddWorldLocation({0, -1.f});
				}
				else
				{
					ACharacter::Jump();
				}
				return;
			}

			if (!bParrying)
			{
				bParrying = true;
				FTimer::SetTimer([&](){ bParrying = false; }, 0.3f);
				OnPlayerParryStart.Execute();
			}
		}

	}

	void APlayerCharacter::AddMovementInput(const FVector2f& MovementInputAmount)
	{
		if (!mAnimator->IsAnyMontagePlaying())
		{
			if (!mMovementComponent->IsCrouching())
			{
				mMovementComponent->AddMovementInput(MovementInputAmount);
				AddWorldLocation(MovementInputAmount);
			}
		}

	}

	void APlayerCharacter::OnMovementInputPressed(float DeltaTime, bool bFlip)
	{
		if (!mAnimator->IsAnyMontagePlaying())
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

	}

	void APlayerCharacter::LookUpTarget(const bool bLookUp)
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

	void APlayerCharacter::HandleAttack(float DeltaTime)
	{
		mTimeLastShooted += DeltaTime;

		if (mTimeLastShooted >= 1.f / 6.f)
		{
			Shoot();
			mTimeLastShooted -= 1.0f / 6.0f;
		}
	}

	void APlayerCharacter::Attack(bool bAttack)
	{

		bIsAttacking = bAttack;

	}

	void APlayerCharacter::ExecSkill()
	{
		if (!mAnimator->IsAnyMontagePlaying() && mCurrentMP > 100) // TODO: MP Check
		{
			mAnimator->PlayMontageAnim(
				bAttackingDiagonalUp
					? EnumAsByte(EPlayerMontages::Exec_Diagonal)
					: bAttackingUp
					? EnumAsByte(EPlayerMontages::Exec_Up)
					: EnumAsByte(EPlayerMontages::Exec_Straight));

			AddMP(-100);
			bExecSkill = true;
		}
	}

	void APlayerCharacter::HandleSkillMovement(float DeltaTime)
	{
		if (bAttackingUp)
		{
			AddWorldLocation(FVector2f(0, 20.f) * DeltaTime);
		}
		else if (bAttackingDiagonalUp)
		{
			AddWorldLocation(FVector2f(-10, 10.f) * DeltaTime);
		}
		else
		{
			AddWorldLocation(FVector2f(-20, 0.f) * DeltaTime);
		}
	}

	void APlayerCharacter::UpdateMuzzleLocation()
	{
		const bool bFacingForward = !mAnimator->GetFlip();
		mMuzzleLocation           = {GetWorldLocation().X + (bFacingForward ? +50.f : -50.f), GetWorldLocation().Y};
		if (bAttackingUp)
		{
			mMuzzleLocation = {GetWorldLocation().X + (bFacingForward ? +35.f : -35.f), GetWorldLocation().Y + 85.f};
		}
		else if (bAttackingDiagonalUp)
		{
			mMuzzleLocation = {GetWorldLocation().X + (bFacingForward ? +60.f : -60.f), GetWorldLocation().Y + 50.f};
		}
		else if (FMath::Abs(mMovementComponent->GetVelocity().X) > 10.f)
		{
			mMuzzleLocation = {GetWorldLocation().X + (bFacingForward ? +70.f : -70.f), GetWorldLocation().Y};
		}

		mShootParticle->SetWorldLocation(mMuzzleLocation);
	}

	void APlayerCharacter::HandleParry()
	{
		LOG_DX_INFO("PARRY!!!");
		AddMP(100.f);
		mMovementComponent->ResetJumpPower();

		//TODO: Add MP
	}

	void APlayerCharacter::OnCollisionEnter(FHitResult_Box2D& HitResult)
	{
		if (!mAnimator->IsAnyMontagePlaying())
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
					FrogProjectile* projectile = dynamic_cast<FrogProjectile*>(HitResult.Src->GetOwnerActor());
					if (projectile)
					{
						OnHit(projectile->IsParriable() ? 0 : 1);
					}
				}
			}
			if (HitResult.Dest && HitResult.Dest->GetTraceType() == ETraceType::Ground)
			{
				PlayJumpDust();
				bParrying = false;

				if ((HitResult.Dest->GetBox().Max - HitResult.Dest->GetBox().Min).Y > 10.f)
				{
					bMovingOnLand = true;
				}
				else
				{
					bMovingOnLand = false;
				}
			}
		}

	}


}
