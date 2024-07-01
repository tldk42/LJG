#include "UPlayerMovementComponent.h"

#include "FTimer.h"
#include "Component/Actor/AActor.h"

namespace LJG
{

	UPlayerMovementComponent::UPlayerMovementComponent()
		: UPawnMovementComponent2D(L"PlayerMovementComp"),
		  bIsDashing(false),
		  mDashPower(400.f) {}

	UPlayerMovementComponent::~UPlayerMovementComponent() {}

	void UPlayerMovementComponent::Update(float DeltaTime)
	{
		UPawnMovementComponent2D::Update(DeltaTime);

		HandleDash(DeltaTime);
	}

	void UPlayerMovementComponent::Dash()
	{
		if (!bIsDashing)
		{
			bIsDashing = true;
			FTimer::SetTimer([&](){
				bIsDashing = false;
			}, .5f);
		}
	}

	void UPlayerMovementComponent::HandleDash(const float_t DeltaTime) const
	{
		if (bIsDashing)
		{
			const FVector2f dashVelocity = {FMath::Sign(mInputVector.X) ? mDashPower : -mDashPower, 0};
			mOwnerActor->AddWorldLocation(dashVelocity * DeltaTime);
		}
	}
}
