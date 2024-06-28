#include "UAnimator.h"

#include "Component/Actor/AActor.h"
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
		// 현재 StateMachine 검사
		if (mStateMachine.contains(mCurrentState))
		{
			USpriteAnimation* currentAnim = mStateMachine[mCurrentState];
			currentAnim->SetTransform(mOwnerActor->GetWorldTransform());
			currentAnim->SetFlip(bFlipX);
			currentAnim->Update(DeltaTime);

			// 유효한 Transition 존재
			if (currentAnim->GetNextAnim() < MAXUINT8)
			{
				SetState(currentAnim->GetNextAnim(), true);
			}
		}

	}

	void UAnimator::Render()
	{
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
