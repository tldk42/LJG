#include "UAnimation.h"

#include "USprite2D.h"

namespace LJG
{
	UAnimation::UAnimation(std::vector<FAnimData>& InAnims)
		: mAnimDatas(InAnims)
	{}

	UAnimation::~UAnimation()
	{
		UAnimation::Release();
	}

	void UAnimation::Initialize()
	{}

	void UAnimation::Update(float DeltaTime)
	{
		const FAnimData& frame = mAnimDatas[mFrames];
		const float elapsedTime = duration_cast<milliseconds>(steady_clock::now() - mPlayTime).count() * (1.f / 1000.f);
		if (elapsedTime >= frame.Time) // 애님 경과시간 초과
		{
			mFrames++;

			if (mFrames >= mAnimDatas.size())
				mFrames = 0;

			mPlayTime = steady_clock::now();
		}

		mAnimDatas[mFrames].Sprite->Update(DeltaTime);
	}

	void UAnimation::Render()
	{
		mAnimDatas[mFrames].Sprite->Render();
	}

	void UAnimation::Release()
	{
		for (FAnimData& sprite : mAnimDatas)
		{
			sprite.Sprite = nullptr;
		}
	}

	void UAnimation::PlayAnim(UINT InFrame)
	{
		bIsPlaying = true;

		mFrames   = InFrame;
		mPlayTime = steady_clock::now();
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
