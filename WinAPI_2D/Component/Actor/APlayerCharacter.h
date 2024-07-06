#pragma once
#include "ACharacter.h"
#include "Game/Interface/Interrfaces.h"

namespace LJG
{
	#define LocalPlayer APlayerCharacter::Get()

	DECLARE_DYNAMIC_DELEGATE(FOnPlayerParryStart)

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
		void  OnDead() override;
		void  OnHit(float InDamage) override;
#pragma endregion

	public:
		void Shoot();
		void Jump() override;

	public:
		inline bool IsAttacking() const { return bIsAttacking; }
		inline bool IsAttackingUp() const { return bAttackingUp; }
		inline bool IsAttackingDiagonalUp() const { return bAttackingDiagonalUp; }
		inline bool IsParring() const { return bParrying; }

	private:
		void AddMovementInput(const FVector2f& MovementInputAmount);
		void OnMovementInputPressed(float DeltaTime, bool bFlip);

		void Attack(bool bAttack) override;

	private:
		void LookUpTarget(const bool bLookUp);
		void HandleParry();
		void OnCollisionEnter(FHitResult_Box2D& HitResult);

	public:
		FOnPlayerParryStart OnPlayerParryStart;

	private:
		bool bIsAttacking;
		bool bAttackingUp;
		bool bAttackingDiagonalUp;
		bool bParrying;

		int32_t mCurrentHP;
		int32_t mMaxHP;

		int32_t mCurrentMP = 0;
		int32_t mMaxMP     = 500;

	private:
		friend class TSingleton<APlayerCharacter>;

		APlayerCharacter();
		~APlayerCharacter() override = default;

	public:
		APlayerCharacter(const APlayerCharacter&)            = delete;
		APlayerCharacter& operator=(const APlayerCharacter&) = delete;
	};
}
