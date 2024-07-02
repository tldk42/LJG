#include "UAnimator.h"
#include "Component/Actor/AActor.h"
#include "USpriteAnimation.h"
#include "DirectX/XSprite2D.h"
#include "DirectX/XTexture.h"

namespace LJG
{

	UAnimator::UAnimator()
		: UObject(L"Animator"),
		  bIsPlaying(false)
	{
		mSprite2D = std::make_unique<XSprite2D>(0.3f);
	}

	UAnimator::~UAnimator() {}

	void UAnimator::Initialize()
	{
		UObject::Initialize();
	}

	void UAnimator::Update(float DeltaTime)
	{
		if (!bIsPlaying)
			return;
		// ???? StateMachine ???
		if (mStateMachine.contains(mCurrentState))
		{
			USpriteAnimation* currentAnim = mStateMachine[mCurrentState];
			mSprite2D->SetWorldTransform(mOwnerActor->GetWorldTransform());
			mSprite2D->SetFlipX(bFlipX);
			mSprite2D->Update(DeltaTime);

			currentAnim->Update(DeltaTime);
			// ????? Transition ????
			if (currentAnim->GetNextAnim() < MAXUINT8)
			{
				SetState(currentAnim->GetNextAnim(), true);
			}
			mSprite2D->SetTexture(currentAnim->GetCurrentTexture());


		}

	}

	void UAnimator::Render()
	{
		if (!bIsPlaying)
			return;
		if (mStateMachine.contains(mCurrentState))
		{
			mSprite2D->Render();
		}
	}

	void UAnimator::Release()
	{
		mSprite2D = nullptr;
	}

	void UAnimator::PlayDefaultTrack(bool bReverse, bool bLoop)
	{
		bIsPlaying = true;
		mSprite2D->SetTexture(mStateMachine[mCurrentState]->GetCurrentTexture());
		if (bReverse)
		{
			mStateMachine[mCurrentState]->PlayReverse(bLoop);
		}
		else
		{
			mStateMachine[mCurrentState]->Play(bLoop);
		}
	}

	void UAnimator::AddTransition(const uint8_t InSrc, const uint8_t InDest, const std::function<bool()>& InCond)
	{
		mStateMachine[InSrc]->AddTransition(InDest, InCond);
	}

	void UAnimator::SetZOrder(const float_t InZOrder) const
	{
		mSprite2D->SetZOrder(InZOrder);
	}

	void UAnimator::SetState(const uint8_t InState, const bool bLoop)
	{
		const auto cachedState = mCurrentState;

		mCurrentState = InState;

		if (mStateMachine.contains(mCurrentState))
		{
			mSprite2D->SetTexture(mStateMachine[mCurrentState]->GetCurrentTexture());
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
