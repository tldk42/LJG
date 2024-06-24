#include "UAnimator.h"

#include "AActor.h"
#include "USpriteAnimation.h"
#include "DirectX/XSprite2D.h"
#include "DirectX/XTexture.h"

namespace LJG
{

	UAnimator::UAnimator(const WText& InKey)
		: UObject(InKey),
		  bIsPlaying(false)
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
			USpriteAnimation* currentAnim = mStateMachine[mCurrentState];
			currentAnim->Update(DeltaTime);

			if (currentAnim->GetNextAnim() < MAXUINT8)
			{
				SetState(currentAnim->GetNextAnim(), true);
			}
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

	void UAnimator::AddTransition(const uint8_t InSrc, const uint8_t InDest, const std::function<bool()>& InCond)
	{
		mStateMachine[InSrc]->AddTransition(InDest, InCond);
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
				mStateMachine[mCurrentState]->Play(bLoop);
			}
			if (cachedState != mCurrentState)
				mStateMachine[cachedState]->Stop();

		}
	}

	void UAnimator::AddState(const uint8_t InState, USpriteAnimation* InAnimation)
	{
		if (!mStateMachine.contains(InState))
		{
			mStateMachine[InState] = InAnimation;
		}
	}

}
