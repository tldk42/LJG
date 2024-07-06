#pragma once
#include "Component/Actor/AProjectile.h"
#include "data/MonsterData.h"

namespace LJG
{
	class FrogProjectile : public AProjectile
	{
	public:
		explicit FrogProjectile(const EGame2Projectile InType, const uint8_t InAddiType);
		~FrogProjectile() override;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

	public:
		inline EGame2Projectile GetFrogProjectileType() const { return mProjectileType; }
		inline uint8_t          IsParriable() const { return bParriable; }

		void SetAdditionalInfo(const uint8_t AddiType) { mAddiType = AddiType; }
		void SetInfo(const EGame2Projectile InType, const uint8_t InAddiType);
		void SetParriable(const bool bEnableParry) { bParriable = bEnableParry; }

	public:
		void OnCollisionEnter(FHitResult_Box2D& HitResult) override;

	private:
		void UpdateBallProjectile(float DeltaTime);

	private:
		EGame2Projectile mProjectileType; // 아이템 타입
		uint8_t          mAddiType;		  // 세부 아이템 타입
		uint8_t          bParriable;

	};
}
