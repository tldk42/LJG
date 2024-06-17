#include "UAnimation.h"

#include "AActor.h"
#include "UAnimator.h"
#include "DirectX/XSprite2D.h"

namespace LJG
{
	UAnimation::UAnimation(std::vector<FAnimData>&& InAnims)
		: bIsPlaying(false),
		  mFrames(0),
		  mAnimDatas(std::move(InAnims))
	{
	}

	UAnimation::~UAnimation()
	{
		UAnimation::Release();
	}

	void UAnimation::Initialize()
	{
	}

	void UAnimation::Update(float DeltaTime)
	{
		if (bIsPlaying)
		{
			if (mOwnerAnimator)
			{
				const AActor* ownerActor = mOwnerAnimator->GetOwnerActor();


				for (const FAnimData& anim : mAnimDatas)
				{
					anim.Sprite->SetFlipX(mOwnerAnimator->FlipX() ? true : false);
					static float testRot = 0.1f;
					testRot += DeltaTime;

					anim.Sprite->SetWorldTransform(ownerActor->GetWorldLocation(), testRot, ownerActor->GetScale());
					// anim.Sprite->SetScale(ownerActor->GetScale());
					// anim.Sprite->SetWorldRotation(testRot);
					// anim.Sprite->SetWorldLocation(ownerActor->GetWorldLocation());
				}
			}


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
}
