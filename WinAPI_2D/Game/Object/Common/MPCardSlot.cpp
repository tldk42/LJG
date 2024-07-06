#include "MPCardSlot.h"
#include "Component/Animation/USpriteAnimation.h"
#include "Component/Animation/UAnimator.h"

namespace LJG
{
	int32_t MPCardSlot::mCounter = 0;

	MPCardSlot::MPCardSlot()
		: AAnimatedImage(std::format(L"MP Card {}", mCounter++))
	{
		mAnimator = CreateDefaultSubObject<UAnimator>();
		mAnimator->SetZOrder(0.01f);
		mAnimator->SetOwnerActor(this);
		mAnimator->AddState(0, CreateSprite(L"hud_ch_card_flip"));
	}

	MPCardSlot::~MPCardSlot() {}

	void MPCardSlot::Initialize()
	{
		AAnimatedImage::Initialize();
	}

	void MPCardSlot::Update(float DeltaTime)
	{
		AAnimatedImage::Update(DeltaTime);
	}

	void MPCardSlot::Render()
	{
		AAnimatedImage::Render();

		if (mValue < mMaxValue)
		{
			mAnimator->RenderDefaultSprite();
		}
	}

	void MPCardSlot::Release()
	{
		AAnimatedImage::Release();
	}

	void MPCardSlot::SetValue(const float_t InValue) {}
}
