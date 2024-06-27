#pragma once
#include "AActor.h"


namespace LJG
{
	class UPawnMovementComponent2D;
	class UBoxComponent;
	class UPlayerAnimator;
	class USpriteAnimation;
	class ACamera;

	class APawn : public AActor
	{
	public:
		explicit APawn(const WText& InKey);
		~APawn() override;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
#pragma endregion

#pragma region Get
		inline UPawnMovementComponent2D* GetMovementComponent() const { return mMovementComponent; }
#pragma endregion

		void AddMovementInput(const FVector2f& MovementInputAmount);
		void OnMovementInputPressed(float DeltaTime, bool bFlip);
		void Jump();
		void Attack();

	protected:
		UPawnMovementComponent2D* mMovementComponent;
		UPlayerAnimator*          mAnimator;
		UBoxComponent*            mDebugBox;
	};
}
