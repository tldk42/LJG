#pragma once
#include "AActor.h"

namespace LJG
{
	class UPawnMovementComponent2D;
	class UPlayerAnimator;
	class UBoxComponent;
	class ACamera;

	class APawn : public AActor
	{
	public:
		APawn();
		~APawn() override;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
#pragma endregion

#pragma region Get
		inline UPawnMovementComponent2D* GetMovementComponent() const { return mMovementComponent; }
		inline UPlayerAnimator*          GetAnimator() const { return mAnimator; }
#pragma endregion

		void AddMovementInput(const FVector2f& MovementInputAmount);
		void OnMovementInputPressed(float DeltaTime, bool bFlip);
		void Jump();
		void Attack();

	private:
		UPawnMovementComponent2D* mMovementComponent;
		UPlayerAnimator*          mAnimator;
		UBoxComponent*            mDebugBox;
		UBoxComponent*            mDebugBox2;

		ACamera* mCamera;

		bool bMove = false;
		bool  bAttacking;
	};
}
