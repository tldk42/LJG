#pragma once
#include "Component/Movement/UPawnMovementComponent2D.h"

namespace LJG
{
	class UFlyingMovementComponent : public UPawnMovementComponent2D
	{
	public:
		UFlyingMovementComponent();

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
#pragma endregion

	public:
		void Launch();

	private:
		APawn* mOwnerPawn;
		
		float_t   mSpeed;
		FVector2f mVelocity;
		FVector2f mPreviousLocation;

		bool bStartChasing;
	};
}
