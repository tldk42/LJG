#include "UAnimation.h"

#include "AActor.h"
#include "UAnimator.h"
#include "DirectX/XSprite2D.h"

namespace LJG
{
	UAnimation::UAnimation(std::vector<FAnimData>&& InAnims)
		: bIsPlaying(false),
		  mFrames(0),
		  mAnimDatas(std::move(InAnims)),
		  mCandidateState(MAXUINT8)
	{}

	UAnimation::~UAnimation()
	{
		UAnimation::Release();
	}

	void UAnimation::Initialize()
	{}

	void UAnimation::Update(float DeltaTime)
	{
		if (bIsPlaying)
		{
			// 트랜스폼 업데이트
			if (mOwnerAnimator && mOwnerAnimator->GetOwnerActor())
			{
				const AActor* ownerActor = mOwnerAnimator->GetOwnerActor();

				for (const FAnimData& anim : mAnimDatas)
				{
					anim.Sprite->SetFlipX(mOwnerAnimator->FlipX() ? true : false);

					anim.Sprite->SetWorldTransform(ownerActor->GetWorldTransform());
				}
			}

			// 스프라이트 업데이트
			const FAnimData& frame       = mAnimDatas[mFrames];
			const float      elapsedTime = duration_cast<milliseconds>(steady_clock::now() - mPlayTime).count() * (1.f /
				1000.f);
			if (elapsedTime >= frame.Time)
			{
				mFrames++;

				if (mFrames >= mAnimDatas.size())
				{
					mFrames = 0;
					if (!bLoop)
					{
						Pause();
					}
				}

				mPlayTime = steady_clock::now();
			}

			mAnimDatas[mFrames].Sprite->Update(DeltaTime);
		}

		// 정지 상태 -> 갈 수 있는 애님 스테이트 확인

		for (auto& transitionRule : mTransitionRules)
		{
			bool bCanBeTrans = true;
			for (TransitionCondition& rule : transitionRule.second)
			{
				if (!rule())
				{
					bCanBeTrans = false;
					break;
				}
			}

			// 모든 조건을 만족하면
			if (bCanBeTrans)
			{
				mCandidateState = transitionRule.first;
				break;
			}
			mCandidateState = MAXUINT8;
		}


	}

	void UAnimation::Render()
	{
		if (bIsPlaying)
			mAnimDatas[mFrames].Sprite->Render();
	}

	void UAnimation::Release()
	{
		for (FAnimData& sprite : mAnimDatas)
		{
			sprite.Sprite = nullptr;
		}
	}

	void UAnimation::PlayAnim(bool InbLoop)
	{
		if (!bIsPlaying)
		{
			bIsPlaying = true;
			bLoop      = InbLoop;

			mFrames   = 0;
			mPlayTime = steady_clock::now();
		}
	}

	void UAnimation::Pause()
	{
		bIsPlaying = false;
	}

	void UAnimation::Stop()
	{
		bIsPlaying = false;
		mFrames    = 0;
	}

	void UAnimation::AddTransition(const uint8_t InAnimName, const TransitionCondition& InRule, UAnimation* InAnim)
	{
		mTransitions[InAnimName] = InAnim;
		mTransitionRules[InAnimName].emplace_back(InRule);
	}

	void UAnimation::AddTransitionCondition(const uint8_t InAnimName, const TransitionCondition& InRule)
	{
		if (mTransitionRules.contains(InAnimName))
		{
			mTransitionRules[InAnimName].emplace_back(InRule);
		}
	}

	uint8_t UAnimation::GetNextAnimation()
	{
		return mCandidateState;
	}

	UAnimation* UAnimation::FindAdjAnim(const uint8_t InAnimName)
	{
		if (mTransitions.contains(InAnimName))
		{
			return mTransitions[InAnimName];
		}

		return nullptr;
	}
}
