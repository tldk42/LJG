#include "USpriteAnimation.h"

#include "Component/Manager/AnimManager.h"
#include "DirectX/XTexture.h"

namespace LJG
{

	USpriteAnimation::USpriteAnimation(const WText& InKey)
		: USceneComponent(InKey),
		  mCurrentFrame(0),
		  mSpeed(1.f),
		  bLoop(true),
		  bIsPlaying(false),
		  bIsPaused(false)
	{
		SetAnimData(*Manager_Anim.CreateOrLoad(InKey));
	}

	USpriteAnimation::~USpriteAnimation() = default;

	void USpriteAnimation::Initialize()
	{
		USceneComponent::Initialize();
	}

	void USpriteAnimation::Update(float DeltaTime)
	{
		USceneComponent::Update(DeltaTime);

		if (bIsPlaying)
		{
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

			if (currentTime >= mAnimationData.FrameTime / mSpeed)
			{
				if (bReverse)
				{
					if (mCurrentFrame == 0)
					{
						mCurrentFrame = mAnimationData.Textures.size() - 1;
						if (!bLoop)
						{
							Stop();
							OnAnimFinished.Execute();
						}
					}
					else
					{
						mCurrentFrame--;
					}
				}
				else
				{
					mCurrentFrame++;

					if (mCurrentFrame >= mAnimationData.Textures.size())
					{
						mCurrentFrame = 0;

						if (!bLoop)
						{
							Stop();
							OnAnimFinished.Execute();
						}
					}
				}


				OnAnimNotifyBegin[mCurrentFrame].Execute();
				mElapsedTime = steady_clock::now();
			}
		}
	}

	void USpriteAnimation::Render()
	{
		// if (bIsPlaying && !mAnimationData.Textures.empty())
		// {
		// 	mSprite2D->Render();
		// }
	}

	void USpriteAnimation::Release()
	{}

	void USpriteAnimation::Play(const bool InLoop)
	{
		bLoop         = InLoop;
		bIsPlaying    = true;
		bIsPaused     = false;
		mCurrentFrame = 0;
		mElapsedTime  = steady_clock::now();
		if (!bIsPlaying)
		{}
	}

	void USpriteAnimation::PlayReverse(const bool InLoop)
	{
		bIsPlaying    = true;
		bReverse      = true;
		bIsPaused     = false;
		bLoop         = InLoop;
		mCurrentFrame = mAnimationData.Textures.size() - 1;
		mElapsedTime  = steady_clock::now();
	}

	void USpriteAnimation::Pause()
	{
		bIsPaused = true;
	}

	void USpriteAnimation::Stop()
	{
		bIsPlaying = false;
		bIsPaused  = false;
		OnAnimBlendOut.Execute();
	}

	void USpriteAnimation::AddTransition(const uint8_t InState, const std::function<bool()>& InCond)
	{
		mTransitions[InState].emplace_back(InCond);
	}
}
