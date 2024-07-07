#pragma once
#include "ACharacter.h"
#include "Game/Interface/Interrfaces.h"

namespace LJG
{
	struct FAnimData;
}
namespace LJG
{
	#define LocalPlayer APlayerCharacter::Get()

	DECLARE_DYNAMIC_DELEGATE(FOnPlayerParryStart)

	class AAnimatedImage;

	class APlayerCharacter : public ACharacter, public IDamagable, public TSingleton<APlayerCharacter>
	{
	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
#pragma endregion

	public:
#pragma region IDamage Interface
		float GetCurrentHealth() override;
		float GetMaxHealth() override;

		void AddMP(const int32_t InValue);
		void OnDead() override;
		void OnHit(float InDamage) override;
#pragma endregion

	public:
		void Shoot();
		void ShootEx();

		void PlayDust() const;
		void PlayJumpDust() const;

		void HandleParry();

		void Jump() override;

	public:
		inline bool IsAttacking() const { return bIsAttacking; }
		inline bool IsAttackingUp() const { return bAttackingUp; }
		inline bool IsAttackingDiagonalUp() const { return bAttackingDiagonalUp; }
		inline bool IsSkillExecuted() const { return bExecSkill; }
		inline bool IsParring() const { return bParrying; }

		inline void ResetSkill() { bExecSkill = false; }

	private:
		void AddMovementInput(const FVector2f& MovementInputAmount);
		void OnMovementInputPressed(float DeltaTime, bool bFlip);

		void SpawnShootProjectile(AProjectile*& proj);

		void Attack(bool bAttack) override;
		void ExecSkill();

	private:
		void LookUpTarget(const bool bLookUp);
		void HandleAttack(float DeltaTime);
		void HandleSkillMovement(float DeltaTime);
		void UpdateMuzzleLocation();
		void OnCollisionEnter(FHitResult_Box2D& HitResult);

	public:
		FOnPlayerParryStart OnPlayerParryStart;

	private:
		bool bInitialized;
		bool bIsAttacking;
		bool bAttackingUp;
		bool bAttackingDiagonalUp;
		bool bExecSkill;
		bool bParrying;
		bool bMovingOnLand;

		int32_t mCurrentHP;
		int32_t mMaxHP;

		int32_t mCurrentMP = 0;
		int32_t mMaxMP     = 500;

		float mTimeLastShooted = 0.f;

		FVector2f mMuzzleLocation;

		AAnimatedImage* mShootParticle;
		AAnimatedImage* mMoveParticle;

		USpriteAnimation* HitParticle_Ground;
		USpriteAnimation* HitParticle_Jump;

	private:
		friend class TSingleton<APlayerCharacter>;

		APlayerCharacter();
		~APlayerCharacter() override = default;

	public:
		APlayerCharacter(const APlayerCharacter&)            = delete;
		APlayerCharacter& operator=(const APlayerCharacter&) = delete;
	};
}
