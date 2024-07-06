#include "UFlyingMovementComponent.h"

#include "Component/Actor/APawn.h"
#include "Component/Actor/APlayerCharacter.h"

namespace LJG
{

	UFlyingMovementComponent::UFlyingMovementComponent()
		: UPawnMovementComponent2D(L"FlyingMovementComponent"),
		  mOwnerPawn(nullptr),
		  mSpeed(230.f),
		  mVelocity(FVector2f::ZeroVector),
		  mPreviousLocation(FVector2f::ZeroVector),
		  bStartChasing(false)
	{}

	void UFlyingMovementComponent::Initialize()
	{
		UObject::Initialize();

		assert(mOwnerActor != nullptr);

		mOwnerPawn = dynamic_cast<APawn*>(mOwnerActor);
	}

	void UFlyingMovementComponent::Update(float DeltaTime)
	{
		const FVector2f ownerLocation = mOwnerActor->GetWorldLocation();

		if (bStartChasing)
		{
			FVector2f newVelocity = (LocalPlayer.GetWorldLocation() - ownerLocation).GetSafeNormal() * mSpeed * DeltaTime;
			mOwnerPawn->AddWorldLocation(newVelocity);
		}

		const auto newVelocity = (ownerLocation - mPreviousLocation) / DeltaTime;
		mAcceleration          = (newVelocity - mVelocity) / DeltaTime;
		mVelocity              = newVelocity;
		mPreviousLocation      = ownerLocation;
	}

	void UFlyingMovementComponent::Launch()
	{
		bStartChasing = true;
	}
}
