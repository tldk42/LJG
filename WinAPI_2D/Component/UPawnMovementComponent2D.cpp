#include "UPawnMovementComponent2D.h"

#include "AActor.h"

namespace LJG
{
	UPawnMovementComponent2D::UPawnMovementComponent2D()
		: bIsMovingOnGround(true),
		  mMaxWalkSpeed(350.f),
		  mGravity(98.f),
		  mVelocity(FVector2f::ZeroVector),
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

		const FVector2f ownerLocation = mOwnerActor->GetWorldLocation();

		// if (ownerLocation.Y > 0 || !bIsMovingOnGround)
		// {
		// 	auto newLoc = ownerLocation.Y - (mGravity * DeltaTime);
		// 	mOwnerActor->SetWorldLocation({ownerLocation.X, newLoc});
		// }

		const auto newVelocity = (ownerLocation - mPreviousLocation) / DeltaTime;
		mAcceleration          = (newVelocity - mVelocity) / DeltaTime;
		mVelocity              = newVelocity;
		mPreviousLocation      = ownerLocation;
	}

	void UPawnMovementComponent2D::AddMovementInput(const FVector2f& InInput)
	{
		mInputVector += InInput;
	}
	
}
