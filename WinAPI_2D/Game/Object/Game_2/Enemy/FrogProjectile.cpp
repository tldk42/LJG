#include "FrogProjectile.h"

#include "Component/Animation/USpriteAnimation.h"
#include "Component/Manager/AnimManager.h"
#include "Helper/EngineHelper.h"

namespace LJG
{

	FrogProjectile::FrogProjectile(const EGame2Projectile InType, const uint8_t InAddiType)
		: mProjectileType(InType),
		  mAddiType(InAddiType)
	{
		mTypeFlag = EProjectileFlag::Enemy;
	}

	FrogProjectile::~FrogProjectile() {}

	void FrogProjectile::Initialize()
	{

		switch (mProjectileType)
		{
		case EGame2Projectile::Fist:
			mAnim->SetAnimData(mAddiType == Pink
								   ? *Manager_Anim.CreateOrLoad(L"shortfrog_fist_pink")
								   : *Manager_Anim.CreateOrLoad(L"shortfrog_fist"));
			bParriable = mAddiType == Pink;
			mBoxSize   = {100, 100};
			mSprite2D->SetFlipX(true);
			mVelocity = {-600, 0};
			break;
		case EGame2Projectile::Butterfly:

			break;
		case EGame2Projectile::Spike:
			switch (mAddiType)
			{
			case Blue:
				mAnim->SetAnimData(*Manager_Anim.CreateOrLoad(L"shorfrog_clap_ball_blue"));
				break;
			case Yellow:
				mAnim->SetAnimData(*Manager_Anim.CreateOrLoad(L"shorfrog_clap_ball_yellow"));
				break;
			case Green:
				mAnim->SetAnimData(*Manager_Anim.CreateOrLoad(L"shorfrog_clap_ball_green"));
				break;
			}
			break;
		case EGame2Projectile::Coin:
			break;
		case EGame2Projectile::Wheel:
			break;
		}

		AProjectile::Initialize();
	}

	void FrogProjectile::Update(float DeltaTime)
	{
		UpdateBallProjectile(DeltaTime);
		AProjectile::Update(DeltaTime);
	}

	void FrogProjectile::Render()
	{
		AProjectile::Render();
	}

	void FrogProjectile::Release()
	{
		AProjectile::Release();
	}

	void FrogProjectile::SetInfo(const EGame2Projectile InType, const uint8_t InAddiType)
	{
		mProjectileType = InType;
		mAddiType       = InAddiType;
	}

	void FrogProjectile::OnCollisionEnter(FHitResult_Box2D& HitResult)
	{
		// AProjectile::OnCollisionEnter(HitResult);
	}

	void FrogProjectile::UpdateBallProjectile(float DeltaTime)
	{
		if (mProjectileType == EGame2Projectile::Spike)
		{
			const float_t MaxHeight = GetWindowHeight() / 2 - 50;
			// 위 아래에 닿으면 y축 이동 방향만 바꿔주자
			if ((GetWorldLocation().Y + mBoxSize.Y / 2) >= MaxHeight)
			{
				mVelocity.Y *= -1;

			}
			else if ((GetWorldLocation().Y - mBoxSize.Y / 2) <= -MaxHeight)
			{
				mVelocity.Y *= -1;

			}

		}

	}
}
