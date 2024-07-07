#include "AFirefly.h"

#include "FrogProjectile.h"
#include "Anim/UFireflyAnimator.h"
#include "Component/Actor/APlayerCharacter.h"
#include "Component/Movement/UPawnMovementComponent2D.h"
#include "Helper/EngineHelper.h"
#include "Movement/UFlyingMovementComponent.h"
#include "Shape/UBoxComponent.h"

namespace LJG
{
	int32_t AFirefly::mObjectNum = 0;

	AFirefly::AFirefly()
		: AEnemy(std::format(L"Firefly_{}", mObjectNum++).c_str())
	{
		bIsPoolManaged = true;

		mCurrentHP = 40.f;

		mDebugBox = CreateDefaultSubObject<UBoxComponent>(L"DebugBox", ETraceType::Pawn);
		mDebugBox->SetScale({100.f, 100.f});
		mDebugBox->SetColor(FLinearColor::Green);
		mDebugBox->SetOwnerActor(this);

		mMovementComponent = CreateDefaultSubObject<UFlyingMovementComponent>();
		mMovementComponent->SetupAttachment(this);
		mMovementComponent->SetOwnerActor(this);
		mMovementComponent->Initialize();

		mAnimator = CreateDefaultSubObject<UFireflyAnimator>();
		mAnimator->SetupAttachment(this);
		mAnimator->SetOwnerActor(this);
		mAnimator->Initialize();

		AEnemy::Initialize();

		mTimer.Reset();

		mDebugBox->OnCollisionEnter_Delegate.Bind(std::bind(&AFirefly::OnCollisionEnter, this, std::placeholders::_1));
	}

	AFirefly::~AFirefly() {}

	void AFirefly::Initialize()
	{
		mTimer.Reset();
		mCurrentHP        = 40.f;
		bTargetSkyReached = false;
	}

	void AFirefly::Update(float DeltaTime)
	{
		AEnemy::Update(DeltaTime);

		if (!bTargetSkyReached)
		{
			// 방향만 구하기
			const FVector2f targetDist = (mTargetSky - GetWorldLocation()).GetSafeNormal();

			AddWorldLocation(targetDist * 230.f * DeltaTime);
		}


		if (!bTargetSkyReached && mTargetSky.IsNearlyEqual(GetWorldLocation()))
		{
			if (UFlyingMovementComponent* flyComp = dynamic_cast<UFlyingMovementComponent*>(mMovementComponent))
			{
				flyComp->Launch();
			}
			bTargetSkyReached = true;
		}
	}

	void AFirefly::OnDead()
	{
		AEnemy::OnDead();

		mAnimator->SetState(EnumAsByte(EFireflyState::Dead), false);
		mDebugBox->SetActive(false);
	}

	void AFirefly::OnHit(float InDamage)
	{
		mCurrentHP -= InDamage;
		if (mCurrentHP <= 0)
		{
			OnDead();
		}
	}

	void AFirefly::OnCollisionEnter(FHitResult_Box2D& HitResult)
	{
		// if (HitResult.Src->GetTraceType() == ETraceType::Projectile)
		// {
		// 	if (!dynamic_cast<FrogProjectile*>(HitResult.Src->GetOwnerActor()))
		// 	{
		// 		LOG_CORE_INFO("{}", mLife);
		// 		OnHit(-1);
		// 	}
		// }
	}

	void AFirefly::SetSkyTarget(const FVector2f& InSkyTargetLoc)
	{
		mTargetSky = InSkyTargetLoc;
	}
}
