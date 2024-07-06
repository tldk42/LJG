#pragma once
#include "Component/UObject.h"


namespace LJG
{
	class UBoxComponent;

	class UPawnMovementComponent2D : public UObject
	{
	public:
		UPawnMovementComponent2D(const WText& InKey);

#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
#pragma endregion


#pragma region Get
		[[nodiscard]] inline bool      IsMovingOnGround() const { return bIsMovingOnGround; }
		[[nodiscard]] inline bool      IsJumping() const { return bIsJumping; }
		[[nodiscard]] inline bool      IsCrouching() const { return bIsCrouching; }
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
		inline void ResetJumpPower() { mJumpPower_Current = (mJumpPower_Value - 200); }

		void Jump();
#pragma endregion

		void AddMovementInput(const FVector2f& InInput);

		void TryCrouch();
		void TryUnCrouch();

	protected:
		void HandleJumpAction(const float_t DeltaTime);
		void HandleGroundCollision(FHitResult_Box2D& HitResult);

	protected:
		APawn* mOwnerPawn;
		bool   bIsMovingOnGround;
		bool   bIsJumping;
		bool   bIsCrouching;

		float_t mMaxWalkSpeed;
		float_t mGravity;
		float_t mJumpPower_Value;
		float_t mJumpPower_Current;
		float_t mCachedBoxHeight;
		float_t mCurrentBoxHeight;
		float_t mTargetCrouchHeight;

		FVector2f mInputVector;
		FVector2f mVelocity;
		FVector2f mAcceleration;
		FVector2f mAirResistance;
		FVector2f mGroundFriction;
		FVector2f mPreviousLocation;

		// UBoxComponent* mCachedGround;
	};
}
