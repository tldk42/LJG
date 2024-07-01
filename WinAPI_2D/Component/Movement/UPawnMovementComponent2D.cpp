#include "UPawnMovementComponent2D.h"

#include "Component/Actor/AActor.h"
#include "Component/Actor/APawn.h"
#include "Shape/Tracer.h"
#include "Shape/UBoxComponent.h"

namespace LJG
{
	UPawnMovementComponent2D::UPawnMovementComponent2D(const WText& InKey)
		: UObject(InKey),
		  bIsMovingOnGround(false),
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

		mOwnerPawn = dynamic_cast<APawn*>(mOwnerActor);
	}

	void UPawnMovementComponent2D::Update(float DeltaTime)
	{
		UObject::Update(DeltaTime);

		CheckGround(DeltaTime);
		HandleJumpAction(DeltaTime);
		// HandleCrouchAction(DeltaTime);

		const FVector2f ownerLocation = mOwnerActor->GetWorldLocation();

		const auto newVelocity = (ownerLocation - mPreviousLocation) / DeltaTime;
		mAcceleration          = (newVelocity - mVelocity) / DeltaTime;
		mVelocity              = newVelocity;
		mPreviousLocation      = ownerLocation;
	}

	void UPawnMovementComponent2D::Jump()
	{
		// TODO: 아래방향키를 누르고있으면 내려가는 로직 작성
		if (!bIsJumping)
		{
			mJumpPower_Current = mJumpPower_Value;
			bIsJumping         = true;
			bIsMovingOnGround  = false;
		}
	}

	void UPawnMovementComponent2D::AddMovementInput(const FVector2f& InInput)
	{
		mInputVector = InInput;
	}

	void UPawnMovementComponent2D::TryCrouch()
	{
		if (bIsMovingOnGround && !bIsCrouching)
		{
			bIsCrouching             = true;
			const auto debugBoxScale = mOwnerPawn->mDebugBox->GetScale();
			mOwnerPawn->mDebugBox->SetScale({debugBoxScale.X, debugBoxScale.Y / 2});
			mOwnerPawn->AddWorldLocation({0, -debugBoxScale.Y / 4});
			mCachedBoxHeight    = mOwnerPawn->GetWorldLocation().Y;
			mTargetCrouchHeight = mCachedBoxHeight - 50.f;
			mCurrentBoxHeight   = mCachedBoxHeight;
		}
	}

	void UPawnMovementComponent2D::TryUnCrouch()
	{
		if (bIsCrouching)
		{
			const auto debugBoxScale = mOwnerPawn->mDebugBox->GetScale();

			mOwnerPawn->mDebugBox->SetScale({debugBoxScale.X, debugBoxScale.Y * 2});
			mOwnerPawn->AddWorldLocation({0, debugBoxScale.Y / 2});

			bIsCrouching             = false;

			mTargetCrouchHeight = mCachedBoxHeight;
			mCurrentBoxHeight   = mCachedBoxHeight;
		}
	}

	void UPawnMovementComponent2D::HandleJumpAction(const float DeltaTime)
	{
		if (bIsJumping)
		{
			mJumpPower_Current -= mGravity * DeltaTime;
			mOwnerActor->AddWorldLocation(FVector2f(0.f, mJumpPower_Current * DeltaTime));
		}
		else if (!bIsMovingOnGround && !bIsJumping)
		{
			mOwnerActor->AddWorldLocation(FVector2f(0.f, -980.f * DeltaTime));
		}
	}

	void UPawnMovementComponent2D::CheckGround(const float_t DeltaTime)
	{
		if (mCachedGround)
		{
			if (mOwnerPawn->mDebugBox->GetBox().Intersect(mCachedGround->GetBox()))
			{
				if (bIsJumping && (mJumpPower_Value - mJumpPower_Current) > 10.f)
				{
					bIsJumping        = false;
					bIsMovingOnGround = true;
				}
				return;
			}
		}

		for (UBoxComponent* box : BoxTypes.Types())
		{
			// Ground Box만 Check
			if (box->GetTraceType() != ETraceType::Ground)
				continue;
			if (mOwnerPawn->mDebugBox->GetBox().Intersect(box->GetBox()))
			{
				if (box->GetBox().Max.Y <= mPreviousLocation.Y)
				{
					float_t groundPos = box->GetBox().Max.Y + mOwnerPawn->mDebugBox->GetScale().Y / 2;
					mOwnerActor->SetWorldLocation({
						mOwnerPawn->GetWorldLocation().X, groundPos
					});

					bIsJumping        = false;
					mCachedGround     = box;
					bIsMovingOnGround = true;
					return;
				}

			}
		}

		if (!bIsCrouching)
		{
			bIsMovingOnGround = false;
		}
	}


}
