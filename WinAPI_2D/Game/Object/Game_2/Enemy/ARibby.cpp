#include "ARibby.h"

#include "ACroaks.h"
#include "FrogProjectile.h"
#include "FTimer.h"
#include "Anim/URibbyAnimator.h"
#include "Component/Manager/AnimManager.h"
#include "Game/AI/Test/Blackboard_Game2.h"
#include "Game/AI/Test/Game2BT.h"
#include "Helper/EngineHelper.h"
#include "Shape/UBoxComponent.h"

namespace LJG
{

	ARibby::ARibby()
		: AEnemy(L"Ribby"),
		  mCurrentState(ERibbyState::Idle),
		  bIsRibbyTurn(true)
	{
		mCurrentHP = Game2MonsterHP[0];
	}

	ARibby::~ARibby()
	{
	}

	void ARibby::Initialize()
	{
		mAnimator = CreateDefaultSubObject<URibbyAnimator>();
		mAnimator->SetupAttachment(this);
		mAnimator->SetOwnerActor(this);
		mAnimator->Initialize();

		APawn::Initialize();

		SetWorldLocation({208.f * 1.5f, -157.f * 1.5f});

		mDebugBox->SetScale({110.f, 270.f});

		mTimer.Reset();

		SetActive(true);
	}

	void ARibby::Update(float DeltaTime)
	{
		APawn::Update(DeltaTime);
	}

	void ARibby::OnDead()
	{
		AEnemy::OnDead();
	}

	void ARibby::OnHit(float InDamage)
	{
		AEnemy::OnHit(InDamage);

		BB_Game2.CurrentHP -= InDamage;

		if (BB_Game2.CurrentHP <= 0)
		{
			BB_Game2.ChangePhase();
		}
	}

	uint8_t ARibby::GetState()
	{
		return EnumAsByte(mCurrentState);
	}

	void ARibby::SetState(uint8_t NewState)
	{
		mCurrentState = static_cast<ERibbyState>(NewState);

		switch (mCurrentState)
		{
		case ERibbyState::Intro:
			break;
		case ERibbyState::Idle:
			mAnimator->SetState(NewState, true);
			break;


		case ERibbyState::Attack_Punch_Start:
			ResetCombo();
			mAnimator->SetState(NewState, false);
			break;
		case ERibbyState::Attack_Punch_Loop:
			mAnimator->SetState(NewState, true);
			break;
		case ERibbyState::Attack_Punch_End:
			break;


		case ERibbyState::Attack_Spike_Intro_Start:
			mAnimator->SetState(NewState, false);
			break;
		case ERibbyState::Attack_Spike_Intro_Loop:
			mAnimator->SetState(NewState, true);
			break;
		case ERibbyState::Attack_Spike_Loop:
			ResetCombo();
			mAnimator->SetState(NewState, true);
			break;

		case ERibbyState::Roll_Intro_Start:
			mAnimator->SetState(NewState, false);
			break;
		case ERibbyState::Roll_Intro_Loop:
			mAnimator->SetState(NewState, true);
			mTimer.Reset();
			break;
		case ERibbyState::Roll_Intro_End:
			mAnimator->SetState(NewState, false);
			break;
		case ERibbyState::Roll_Loop:
			mAnimator->SetState(NewState, true);
			break;
		case ERibbyState::Roll_End:
			ResetCombo();
			mAnimator->SetState(NewState, false);
			break;

		case ERibbyState::Dead:
			break;
		case ERibbyState::End:
			break;


		}
	}

	void ARibby::ResetCombo()
	{
		mTimer.Reset();
		mLastLaunchTime    = 0.f;
		mProjectileCounter = 0;
	}

	void ARibby::TryAttack_Punch()
	{
		/// 1. 먼저 애니메이션Attack_Punch_Start이 끝나면 Punch_loop로 돌린다.
		/// 3. 9초 동안 1.5초 간격으로 랜덤한 Punch 소환
		const float_t elapsedSeconds = mTimer.ElapsedSeconds();
		if (elapsedSeconds > 9.f)
		{
			SetState(EnumAsByte(ERibbyState::Idle));
			bIsRibbyTurn = false;
		}

		if ((elapsedSeconds - mLastLaunchTime) > 1.5f)
		{
			Punch();
			mLastLaunchTime = elapsedSeconds;
		}

	}

	void ARibby::CheckSpikeCoolTime()
	{
		const float_t elapsedSeconds = mTimer.ElapsedSeconds();

		if (elapsedSeconds > 3.f)
		{
			SetState(EnumAsByte(ERibbyState::Attack_Spike_Intro_Start));
			mTimer.Reset();
		}
	}

	void ARibby::TryAttack_Spike()
	{
		const float_t elapsedSeconds = mTimer.ElapsedSeconds();

		if (mSpikeCoolTime < elapsedSeconds)
		{
			mMaxProjectile = FMath::GenerateNum(1, 3);
			SetState(EnumAsByte(ERibbyState::Attack_Spike_Loop));
		}
	}

	void ARibby::Roll(bool bLeft)
	{
		if (bLeft)
		{
			mRollTarget = {-420.f * 1.5f, -157.f * 1.5f};
		}
		else
		{
			mRollTarget = Croaks.GetWorldLocation() - FVector2f(100.f, 0);
		}
		FVector2f targetDirection = (mRollTarget - GetWorldLocation()).GetSafeNormal();

		AddWorldLocation(targetDirection * GetDeltaSeconds() * 600.f);


		if (targetDirection.IsNearlyZero())
		{
			if (bLeft)
			{
				mAnimator->SetFlipX(bLeft);
				Ribby.SetState(EnumAsByte(ERibbyState::Roll_End));
				SetWorldLocation({-300.f * 1.5f, -130.f * 1.5f});
			}

		}
		if (!bLeft && (mRollTarget - GetWorldLocation()).GetLength() < 110.f)
		{
			Croaks.SetState(EnumAsByte(ECroaksState::Morph_Outro));
			SetActive(false);
		}
	}

	void ARibby::Punch()
	{
		FrogProjectile* projectile = Manager_Object.Spawn<FrogProjectile>(EGame2Projectile::Fist, Normal);

		const float_t randHeight = FMath::GenerateRandomfloat(GetWorldLocation().Y - 70.f,
															  GetWorldLocation().Y + 70.f);

		projectile->SetAdditionalInfo(mProjectileCounter % 3 == 0 ? Pink : Normal);

		projectile->SetWorldLocation({GetWorldLocation().X - 100.f, randHeight});
		projectile->SetOwnerActor(this);
		projectile->Launch();

		mProjectileCounter++;
	}

	void ARibby::SpikeBall()
	{
		if (mProjectileCounter >= mMaxProjectile)
		{
			SetState(EnumAsByte(ERibbyState::Idle));
			mTimer.Reset();
			return;
		}

		FrogProjectile* projectile = Manager_Object.Spawn<FrogProjectile>(EGame2Projectile::Spike, Blue);

		projectile->SetInfo(EGame2Projectile::Spike, mMaxProjectile - 1);
		projectile->SetWorldLocation({GetWorldLocation().X + 200.f, GetWorldLocation().Y});
		projectile->SetVelocity(++mProjectileCounter % 2 == 0 ? FVector2f(280.f, 700.f) : FVector2f(280.f, -700.f));
		projectile->SetOwnerActor(this);
		projectile->Launch();
	}
}
