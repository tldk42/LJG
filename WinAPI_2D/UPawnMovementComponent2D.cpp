#include "UPawnMovementComponent2D.h"

namespace LJG
{
	UPawnMovementComponent2D::UPawnMovementComponent2D()
		: bIsMovingOnGround(false),
		  mMaxWalkSpeed(350.f),
		  mVelocity(FVector2f::ZeroVector),
		  mGravity(),
		  mAirResistance(),
		  mGroundFriction()
	{
	}

	void UPawnMovementComponent2D::Initialize()
	{
		UObject::Initialize();

		assert(mOwnerActor != nullptr);
	}

	void UPawnMovementComponent2D::Update(float DeltaTime)
	{
		UObject::Update(DeltaTime);

		if (bIsMovingOnGround)
		{
			mVelocity += mGroundFriction;
		}
		else
		{
			mVelocity += mGravity;
		}
	}

	void UPawnMovementComponent2D::AddMovementInput(const FVector2f& InInput)
	{
		mInputVector += InInput;
	}
}
