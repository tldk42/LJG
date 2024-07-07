#include "MPCardSlot.h"
#include "Component/Animation/USpriteAnimation.h"
#include "Component/Animation/UAnimator.h"

namespace LJG
{
	int32_t MPCardSlot::mCounter = 0;

	MPCardSlot::MPCardSlot()
		: AAnimatedImage(std::format(L"MP Card {}", mCounter++))
	{
		USpriteAnimation* cardAnim = CreateSprite(L"hud_ch_card_flip");
		cardAnim->SetSpeed(0.6f);
		mAnimator->SetZOrder(0.01f);
		mAnimator->SeteDefaultTrack(cardAnim);
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
	}

	void MPCardSlot::Release()
	{
		AAnimatedImage::Release();
	}

	void MPCardSlot::SetValue(const float_t InValue)
	{
		mValue = InValue;
	}
}
