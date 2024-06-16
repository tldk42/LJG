#include "UAnimation2D.h"

#include "AActor.h"
#include "DirectX/XSprite2D.h"

namespace LJG
{
	UAnimation2D::UAnimation2D(std::vector<FAnimData2D>& InAnims)
		: mAnimDatas(InAnims)
	{}

	UAnimation2D::~UAnimation2D()
	{
		UAnimation2D::Release();
	}

	void UAnimation2D::Initialize()
	{
		UObject::Initialize();
	}

	void UAnimation2D::Update(float DeltaTime)
	{
		UObject::Update(DeltaTime);

		const FAnimData2D& frame = mAnimDatas[mIndex];
		const float elapsedTime = duration_cast<milliseconds>(steady_clock::now() - mPlayTime).count() * (1.f / 1000.f);
		if (elapsedTime >= frame.Time) // 애님 경과시간 초과
		{
			mIndex++;

			if (mIndex >= mAnimDatas.size())
				mIndex = 0;

			mPlayTime = steady_clock::now();
		}

		mAnimDatas[mIndex].Sprite->Update(DeltaTime);
	}

	void UAnimation2D::Render()
	{
		UObject::Render();

		mAnimDatas[mIndex].Sprite->Render();
	}

	void UAnimation2D::Release()
	{
		UObject::Release();

		for (FAnimData2D& sprite : mAnimDatas)
		{
			sprite.Sprite = nullptr;
		}
	}

	void UAnimation2D::PlayAnim(UINT InFrame)
	{
		bIsPlaying = true;

		mIndex    = InFrame;
		mPlayTime = steady_clock::now();
	}

	void UAnimation2D::Pause()
	{
		bIsPlaying = false;
	}

	void UAnimation2D::Stop()
	{
		bIsPlaying = false;
		mIndex     = 0;
	}

	void UAnimation2D::SetPosition(const FVector2f& InPosition)
	{
		for (FAnimData2D& anim : mAnimDatas)
		{
			anim.Sprite->SetWorldLocation(InPosition);
		}
	}

	void UAnimation2D::SetScale(const FVector2f& InScale)
	{
		for (FAnimData2D& anim : mAnimDatas)
		{
			anim.Sprite->SetScale(InScale);
		}
	}
}
