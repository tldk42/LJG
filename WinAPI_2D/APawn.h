#pragma once
#include "AActor.h"

namespace LJG
{
	class UPawnMovementComponent2D;
	class UPlayerAnimator;
}

namespace LJG
{
	class UDebugBox2D;
}

namespace LJG
{
	class APawn : public AActor
	{
	public:
		APawn();
		~APawn() override;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

#pragma region Get
		inline UPawnMovementComponent2D* GetMovementComponent() const { return mMovementComponent; }
		inline UPlayerAnimator*          GetAnimator() const { return mAnimator; }
#pragma endregion

		void AddMovementInput(const FVector2f& MovementInputAmount);

	private:
		UPawnMovementComponent2D*    mMovementComponent;
		UPlayerAnimator*             mAnimator;
		std::unique_ptr<UDebugBox2D> mDebugBox;

	};
}
