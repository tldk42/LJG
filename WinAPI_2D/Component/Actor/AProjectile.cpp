#include "AProjectile.h"

#include "Component/Animation/USpriteAnimation.h"
#include "Component/Manager/AnimManager.h"
#include "Helper/EngineHelper.h"
#include "Shape/UBoxComponent.h"

namespace LJG
{
	int32_t AProjectile::mObjectNum = 0;

	AProjectile::AProjectile()
		: AActor(std::format(L"Projectile_{}", mObjectNum++).c_str())
	{
		mSprite2D = std::make_unique<XSprite2D>();
		Initialize();
	}

	AProjectile::~AProjectile()
	{}

	void AProjectile::Initialize()
	{
		AActor::Initialize();

		mBoxComponent = CreateDefaultSubObject<UBoxComponent>(L"CollisionBox", ETraceType::Projectile);
		mBoxComponent->SetOwnerActor(this);
		mBoxComponent->SetScale({80, 40});

		mVelocity = {1000.f, 0};
		mAnim     = CreateDefaultSubObject<USpriteAnimation>(L"Projectile_Text");
		mAnim->SetAnimData(*Manager_Anim.CreateOrLoad(L"projectile_shoot"));
	}

	void AProjectile::Update(float DeltaTime)
	{
		AActor::Update(DeltaTime);
		mAnim->SetWorldLocation(GetWorldLocation());

		if (bLaunched)
		{
			AddWorldLocation(mVelocity * DeltaTime);
			mAnim->AddWorldLocation(mVelocity * DeltaTime);
			mSprite2D->AddWorldLocation(mVelocity * DeltaTime);

			mAnim->Update(DeltaTime);
			mSprite2D->Update(DeltaTime);
		}
	}

	void AProjectile::Render()
	{
		AActor::Render();
		if (bLaunched)
		{
			mAnim->Render();
			mSprite2D->SetTexture(mAnim->GetCurrentTexture());
			mSprite2D->Render();
		}
	}

	void AProjectile::Release()
	{
		AActor::Release();
	}

	void AProjectile::SetWorldLocation(const FVector2f& InLocation)
	{
		AActor::SetWorldLocation(InLocation);
		mAnim->SetWorldLocation(InLocation);
		mSprite2D->SetWorldLocation(InLocation);
	}

	void AProjectile::Launch()
	{
		bLaunched = true;
		mAnim->Play(true);
	}
}
