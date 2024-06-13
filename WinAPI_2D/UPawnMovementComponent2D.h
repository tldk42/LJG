#pragma once
#include "UObject.h"

namespace LJG
{
	class UPawnMovementComponent2D : public UObject
	{
	public:
		UPawnMovementComponent2D();

#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
#pragma endregion

		void AddMovementInput(const FVector2f& InInput);

#pragma region Get
		[[nodiscard]] inline bool      IsMovingOnGround() const { return bIsMovingOnGround; }
		[[nodiscard]] inline float_t   GetMaxWalkSpeed() const { return mMaxWalkSpeed; }
		[[nodiscard]] inline FVector2f GetInputVector() const { return mInputVector; }
		[[nodiscard]] inline FVector2f GetVelocity() const { return mVelocity; }
		[[nodiscard]] inline FVector2f GetGravity() const { return mGravity; }
		[[nodiscard]] inline FVector2f GetAirResistance() const { return mAirResistance; }
		[[nodiscard]] inline FVector2f GetGroundFriction() const { return mGroundFriction; }
#pragma endregion

	protected:
		bool bIsMovingOnGround;

		float_t mMaxWalkSpeed;

		FVector2f mInputVector;
		FVector2f mVelocity;
		FVector2f mGravity;
		FVector2f mAirResistance;
		FVector2f mGroundFriction;
	};
}
