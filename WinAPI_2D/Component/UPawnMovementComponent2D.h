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
		[[nodiscard]] inline bool      IsJumping() const { return bIsJumping; }
		[[nodiscard]] inline float_t   GetJumpPower() const { return mJumpPower_Value; }
		[[nodiscard]] inline float_t   GetMaxWalkSpeed() const { return mMaxWalkSpeed; }
		[[nodiscard]] inline float_t   GetGravity() const { return mGravity; }
		[[nodiscard]] inline FVector2f GetInputVector() const { return mInputVector; }
		[[nodiscard]] inline FVector2f GetVelocity() const { return mVelocity; }
		[[nodiscard]] inline FVector2f GetAirResistance() const { return mAirResistance; }
		[[nodiscard]] inline FVector2f GetGroundFriction() const { return mGroundFriction; }
		[[nodiscard]] inline FVector2f GetAcceleration() const { return mAcceleration; }
#pragma endregion

#pragma region Set
		inline void SetJumpPower(const float_t InJumpPower) { mJumpPower_Value = InJumpPower; }
		inline void Jump() { bIsJumping = true; }
#pragma endregion

	protected:
		void HandleJumpAction(const float DeltaTime);

	protected:
		bool bIsMovingOnGround;
		bool bIsJumping;

		float_t mMaxWalkSpeed;
		float_t mGravity;
		float_t mJumpPower_Value;
		float_t mJumpPower_Current;

		FVector2f mInputVector;
		FVector2f mVelocity;
		FVector2f mAcceleration;
		FVector2f mAirResistance;
		FVector2f mGroundFriction;
		FVector2f mPreviousLocation;
	};
}