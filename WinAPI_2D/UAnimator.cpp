#include "UAnimator.h"

#include "AActor.h"
#include "UAnimation.h"

namespace LJG
{

	UAnimator::UAnimator()
		: bIsPlaying(false)
	{}

	UAnimator::~UAnimator() {}

	void UAnimator::Initialize()
	{
		UObject::Initialize();
	}

	void UAnimator::Update(float DeltaTime)
	{
		UObject::Update(DeltaTime);

		if (mStateMachine.contains(mCurrentState))
		{
			mStateMachine[mCurrentState]->Update(DeltaTime);
		}
	}

	void UAnimator::Render()
	{
		UObject::Render();

		if (mStateMachine.contains(mCurrentState))
		{
			mStateMachine[mCurrentState]->Render();
		}
	}

	void UAnimator::Release()
	{
		UObject::Release();
	}

	void UAnimator::SetState(const uint8_t InState, const bool bLoop)
	{
		const auto cachedState = mCurrentState;

		mCurrentState = InState;

		if (mStateMachine.contains(mCurrentState))
		{
			if (!bIsPlaying || cachedState != mCurrentState)
			{
				bIsPlaying = true;
				mStateMachine[mCurrentState]->PlayAnim(bLoop);
			}
		}
	}

	void UAnimator::AddState(const uint8_t InState, const UAnimationSPtr& InAnimation)
	{
		if (!mStateMachine.contains(InState))
		{
			mStateMachine[InState] = InAnimation;
			InAnimation->SetAnimator(shared_from_this());
		}
	}
}
