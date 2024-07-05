#pragma once
#include "ACharacter.h"
#include "Game/Interface/Interrfaces.h"

namespace LJG
{
	#define LocalPlayer APlayerCharacter::Get()

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

	public:
		bool IsAttacking() const { return bIsAttacking; }
		bool IsAttackingUp() const { return bAttackingUp; }
		bool IsAttackingDiagonalUp() const { return bAttackingDiagonalUp; }

	private:
		void AddMovementInput(const FVector2f& MovementInputAmount);
		void OnMovementInputPressed(float DeltaTime, bool bFlip);
		void LookUpTarget(const bool bLookUp);

		void Attack(bool bAttack) override;

	private:
		void OnCollisionEnter(FHitResult_Box2D& HitResult);

	private:
		bool    bIsAttacking;
		bool    bAttackingUp;
		bool    bAttackingDiagonalUp;
		int32_t mCurrentHP;
		int32_t mMaxHP;

	private:
		friend class TSingleton<APlayerCharacter>;

		APlayerCharacter();
		~APlayerCharacter() override = default;

	public:
		APlayerCharacter(const APlayerCharacter&)            = delete;
		APlayerCharacter& operator=(const APlayerCharacter&) = delete;
	};
}
