#include "AProjectile.h"

#include "APlayerCharacter.h"
#include "Component/Animation/USpriteAnimation.h"
#include "Component/Manager/AnimManager.h"
#include "Game/Actor/AEnemy.h"
#include "Helper/EngineHelper.h"
#include "Shape/UBoxComponent.h"

namespace LJG
{
	int32_t AProjectile::mObjectNum = 0;

	AProjectile::AProjectile()
		: AActor(std::format(L"Projectile_{}", mObjectNum++).c_str()),
		  mLifeTime(5.f),
		  mVelocity({1000.f, 0}),
		  mBoxSize(FVector2f(80, 40))
	{
		bIsPoolManaged = true;
		
		mSprite2D      = std::make_unique<XSprite2D>();
		mSprite2D->SetZOrder(.2f);

		mBoxComponent = CreateDefaultSubObject<UBoxComponent>(L"CollisionBox", ETraceType::Projectile);
		mBoxComponent->SetOwnerActor(this);
		mBoxComponent->OnCollisionEnter_Delegate.Bind(
			std::bind(&AProjectile::OnCollisionEnter, this, std::placeholders::_1));

		mAnim = CreateSprite(L"projectile_shoot");
		mAnim->SetOwnerActor(this);

	}

	AProjectile::AProjectile(const FAnimData& InAnimData, const FVector2f& InSize, const FVector2f& InVelocity)
		: AProjectile()
	{
		mBoxSize  = InSize;
		mVelocity = InVelocity;

		mAnim->SetAnimData(InAnimData);
	}


	AProjectile::~AProjectile()
	{}

	void AProjectile::Initialize()
	{
		timer.Reset();

		AActor::Initialize();

		mBoxComponent->SetScale(mBoxSize);
	}

	void AProjectile::Update(float DeltaTime)
	{
		if (bLaunched && bActive)
		{
			if (timer.ElapsedSeconds() >= mLifeTime)
			{
				bLaunched = false;
				SetActive(false);
			}
			AActor::Update(DeltaTime);

			AddWorldLocation(mVelocity * DeltaTime);
			mSprite2D->Update(DeltaTime);
		}
	}

	void AProjectile::Render()
	{
		if (bLaunched && bActive)
		{
			AActor::Render();

			mSprite2D->SetTexture(mAnim->GetCurrentTexture());
			mSprite2D->Render();
		}
	}

	void AProjectile::Release()
	{
		AActor::Release();
	}

	void AProjectile::AddWorldLocation(const FVector2f& InAddLocation)
	{
		AActor::AddWorldLocation(InAddLocation);
		mSprite2D->AddWorldLocation(InAddLocation);

	}

	void AProjectile::SetWorldLocation(const FVector2f& InLocation)
	{
		AActor::SetWorldLocation(InLocation);
		mBoxComponent->SetWorldLocation(InLocation);
		mAnim->SetWorldLocation(InLocation);
		mSprite2D->SetWorldLocation(InLocation);
	}

	void AProjectile::SetWorldRotation(const float InDegree)
	{
		AActor::SetWorldRotation(InDegree);
		mBoxComponent->SetWorldRotation(InDegree);
		mAnim->SetWorldRotation(InDegree);
		mSprite2D->SetWorldRotation(InDegree);
	}

	void AProjectile::Launch()
	{
		Initialize();

		bLaunched = true;
		mAnim->Play(true);
	}

	void AProjectile::SetLifeTime(const float_t InLifeTime)
	{
		mLifeTime = InLifeTime;
	}

	void AProjectile::SetDamage(const float_t InDamage)
	{
		mDamage = InDamage;
	}

	void AProjectile::SetVelocity(const FVector2f& InVelocity)
	{
		mVelocity = InVelocity;
	}

	void AProjectile::SetCollisionBoxSize(const FVector2f& InSize) const
	{
		mBoxComponent->SetScale(InSize);
	}

	void AProjectile::SetAnimation(const FAnimData& InAnimData) const
	{
		mAnim->SetAnimData(InAnimData);
	}

	void AProjectile::OnCollisionEnter(FHitResult_Box2D& HitResult)
	{
		if (HitResult.Dest->GetTraceType() == ETraceType::Pawn)
		{
			if (AActor* ownerActor = HitResult.Dest->GetOwnerActor(); ownerActor != mOwnerActor)
			{
				if (AEnemy* enemy = dynamic_cast<AEnemy*>(ownerActor))
				{
					enemy->OnHit(mDamage);
					LOG_CORE_INFO("Hit ID:{} Damage:{}", WText2Text(enemy->GetName()), enemy->GetCurrentHealth());
					Manager_Object.DeSpawn(this);
				}
			}
		}
	}
}
