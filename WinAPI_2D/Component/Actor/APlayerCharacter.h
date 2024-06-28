#pragma once
#include "ACharacter.h"

namespace LJG
{
	#define LocalPlayer APlayerCharacter::Get()

	class APlayerCharacter : public ACharacter, public TSingleton<APlayerCharacter>
	{

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
#pragma endregion

	public:
		bool IsAttacking() const { return bIsAttacking; }

	private:
		void AddMovementInput(const FVector2f& MovementInputAmount);
		void OnMovementInputPressed(float DeltaTime, bool bFlip);

		void Attack(bool bAttack) override;

	private:
		bool            bIsAttacking;

	private:
		friend class TSingleton<APlayerCharacter>;

		APlayerCharacter();
		~APlayerCharacter() override = default;

	public:
		APlayerCharacter(const APlayerCharacter&)            = delete;
		APlayerCharacter& operator=(const APlayerCharacter&) = delete;
	};
}
