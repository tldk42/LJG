#pragma once
#include "FTimer.h"
#include "Game/Actor/AEnemy.h"

namespace LJG
{
	class AFirefly : public AEnemy
	{
	public:
		AFirefly();
		~AFirefly() override;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
#pragma endregion

	public:
#pragma region IDamage Interface
		void OnDead() override;
		void OnHit(float InDamage) override;
#pragma endregion

		void OnCollisionEnter(FHitResult_Box2D& HitResult);

	public:
		void Shoot();
		void SetSkyTarget(const FVector2f& InSkyTargetLoc);

	private:
		static int32_t mObjectNum;

		FTimer mTimer;
		
		bool      bTargetSkyReached;
		FVector2f mTargetSky; // 목표 공중 지점
		FVector2f mTarget; // 목표 지상 지점
	};
}
