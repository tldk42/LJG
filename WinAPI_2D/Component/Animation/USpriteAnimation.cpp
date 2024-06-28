#include "USpriteAnimation.h"

#include "DirectX/XSprite2D.h"
#include "DirectX/XTexture.h"

namespace LJG
{

	USpriteAnimation::USpriteAnimation(const WText& InKey)
		: USceneComponent(InKey),
		  mCurrentFrame(0),
		  bLoop(false),
		  bIsPlaying(false),
		  bIsPaused(false)
	{
		mSprite2D = std::make_unique<XSprite2D>(0.3f);
	}

	USpriteAnimation::~USpriteAnimation() {}

	void USpriteAnimation::Initialize()
	{
		USceneComponent::Initialize();
	}

	void USpriteAnimation::Update(float DeltaTime)
	{
		USceneComponent::Update(DeltaTime);

		if (bIsPlaying)
		{
			mSprite2D->SetWorldTransform(mWorldTransform);
			mSprite2D->SetFlipX(bFlipX);
			mSprite2D->Update(DeltaTime);
			mNextAnimState = UINT8_MAX;

			for (auto& transition : mTransitions)
			{
				bool bCanEnter = true;
				for (auto& condition : transition.second)
				{
					if (!condition())
					{
						bCanEnter = false;
					}
				}
				if (bCanEnter)
				{
					mNextAnimState = transition.first;
					Stop();
					return;
				}
			}

			const float currentTime = duration_cast<milliseconds>(steady_clock::now() - mElapsedTime).count()
			* (1.f / 1000.f);

			if (currentTime >= mAnimationData.FrameTime)
			{
				mCurrentFrame++;

				if (mCurrentFrame >= mAnimationData.Textures.size())
				{
					mCurrentFrame = 0;

					if (!bLoop)
					{
						Pause();
					}
				}

				mElapsedTime = steady_clock::now();
				mSprite2D->SetTexture(mAnimationData.Textures[mCurrentFrame]);
			}
		}
	}

	void USpriteAnimation::Render()
	{
		if (bIsPlaying && !mAnimationData.Textures.empty())
		{
			mSprite2D->Render();
		}
	}

	void USpriteAnimation::Release()
	{
		mSprite2D = nullptr;
	}

	void USpriteAnimation::Play(const bool InLoop)
	{
		if (!bIsPlaying)
		{
			bIsPlaying    = true;
			bIsPaused     = false;
			bLoop         = InLoop;
			mCurrentFrame = 0;
			mElapsedTime  = steady_clock::now();
		}
	}

	void USpriteAnimation::Pause()
	{
		bIsPaused = true;
	}

	void USpriteAnimation::Stop()
	{
		bIsPlaying = false;
		bIsPaused  = false;
	}

	void USpriteAnimation::AddTransition(const uint8_t InState, const std::function<bool()>& InCond)
	{
		mTransitions[InState].emplace_back(InCond);
	}
}
