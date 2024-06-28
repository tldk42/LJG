#include "UPawnMovementComponent2D.h"
#include "Component/Actor/AActor.h"

namespace LJG
{
	UPawnMovementComponent2D::UPawnMovementComponent2D(const WText& InKey)
		: UObject(InKey),
		  bIsMovingOnGround(true),
		  mMaxWalkSpeed(350.f),
		  mGravity(3333.f),
		  mJumpPower_Value(1250.f),
		  mJumpPower_Current(1250.f),
		  mVelocity({0, 0}),
		  mAirResistance(),
		  mGroundFriction()
	{}

	void UPawnMovementComponent2D::Initialize()
	{
		UObject::Initialize();

		assert(mOwnerActor != nullptr);
	}

	void UPawnMovementComponent2D::Update(float DeltaTime)
	{
		UObject::Update(DeltaTime);

		HandleJumpAction(DeltaTime);

		const FVector2f ownerLocation = mOwnerActor->GetWorldLocation();

		const auto newVelocity = (ownerLocation - mPreviousLocation) / DeltaTime;
		mAcceleration          = (newVelocity - mVelocity) / DeltaTime;
		mVelocity              = newVelocity;
		mPreviousLocation      = ownerLocation;
	}

	void UPawnMovementComponent2D::AddMovementInput(const FVector2f& InInput)
	{
		mInputVector = InInput;
	}

	void UPawnMovementComponent2D::TryCrouch()
	{
		bIsCrouching = true;
	}

	void UPawnMovementComponent2D::TryUnCrouch()
	{
		bIsCrouching = false;
	}

	void UPawnMovementComponent2D::HandleJumpAction(const float DeltaTime)
	{
		if (bIsJumping)
		{
			mJumpPower_Current -= mGravity * DeltaTime;
			mOwnerActor->AddWorldLocation(FVector2f(0.f, mJumpPower_Current * DeltaTime));
		}
		if (mOwnerActor->GetWorldLocation().Y <= 0.f)
		{
			mJumpPower_Current = mJumpPower_Value;
			bIsJumping         = false;
		}
	}


}
