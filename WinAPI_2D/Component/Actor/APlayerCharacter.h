#pragma once
#include "ACharacter.h"

namespace LJG
{
	class APlayerCharacter : public ACharacter, public TSingleton<APlayerCharacter>
	{
	public:
		explicit APlayerCharacter(const WText& InKey);
		~APlayerCharacter() override;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
#pragma endregion

	private:
		void AddMovementInput(const FVector2f& MovementInputAmount);
		void OnMovementInputPressed(float DeltaTime, bool bFlip);

	private:
		ACamera* mCamera;
	};
}
