#include "UAnimator.h"

#include <ranges>

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

		for (USpriteAnimation* montage : mMontages | std::views::values)
		{
			montage->OnAnimFinished.Bind([&](){
				bIsMontagePlaying = false;
				mMontageState     = MAXUINT8;
				mSprite2D->SetTexture(mStateMachine[mCurrentState]->GetCurrentTexture());
			});
		}
	}

	void UAnimator::Update(float DeltaTime)
	{
		if (!bIsPlaying)
			return;

		if (bIsMontagePlaying && mMontages.contains(mMontageState))
		{
			mSprite2D->SetTexture(mMontages[mMontageState]->GetCurrentTexture());
			mMontages[mMontageState]->Update(DeltaTime);
		}
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
				SetState(currentAnim->GetNextAnim(), mStateMachine[currentAnim->GetNextAnim()]->IsLoopAnim());
			}
			if (!bIsMontagePlaying)
			{
				mSprite2D->SetTexture(currentAnim->GetCurrentTexture());
			}
		}
	}

	void UAnimator::Render()
	{
		if (!bIsPlaying)
			return;

		if (bIsMontagePlaying || mStateMachine.contains(mCurrentState))
		{
			mSprite2D->Render();
		}
	}

	void UAnimator::Release()
	{
		mSprite2D = nullptr;
	}

	void UAnimator::RenderDefaultSprite() const
	{
		if (mStateMachine.contains(mCurrentState))
		{
			if (!mSprite2D->GetTexture())
			{
				mSprite2D->SetTexture(mStateMachine.at(mCurrentState)->GetCurrentTexture());
			}
			mSprite2D->Render();
		}
	}

	void UAnimator::SetMontageTrack(const uint8_t InType, USpriteAnimation* InAnimation)
	{
		mMontages.insert_or_assign(InType, InAnimation);
	}

	void UAnimator::SeteDefaultTrack(USpriteAnimation* InAnimation)
	{
		mStateMachine.insert_or_assign(0, InAnimation);
	}

	void UAnimator::PlayDefaultTrack(bool bReverse, bool bLoop)
	{
		if (mStateMachine.contains(0))
		{
			bIsPlaying = true;
			mSprite2D->SetTexture(mStateMachine[0]->GetCurrentTexture());
			if (bReverse)
			{
				mStateMachine[0]->PlayReverse(bLoop);
			}
			else
			{
				mStateMachine[0]->Play(bLoop);
			}
		}

	}

	void UAnimator::AddTransition(const uint8_t InSrc, const uint8_t InDest, const std::function<bool()>& InCond)
	{
		mStateMachine[InSrc]->AddTransition(InDest, InCond);
	}

	void UAnimator::SetScale(const FVector2f& InScale) const
	{
		mSprite2D->SetScale(InScale);
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

	void UAnimator::PlayMontageAnim(const uint8_t MontageType)
	{
		if (mMontages.contains(MontageType))
		{
			bIsPlaying        = true;
			bIsMontagePlaying = true;
			mMontageState     = MontageType;
			mMontages[mMontageState]->Play(false);
			mSprite2D->SetTexture(mMontages[mMontageState]->GetCurrentTexture());
		}
	}

	void UAnimator::BlinkEffect()
	{

		mSprite2D->AdjustRGBA(FLinearColor::White);
	}

	void UAnimator::AddState(const uint8_t InState, USpriteAnimation* InAnimation)
	{
		if (!mStateMachine.contains(InState))
		{
			mStateMachine[InState] = InAnimation;
		}
	}

}
