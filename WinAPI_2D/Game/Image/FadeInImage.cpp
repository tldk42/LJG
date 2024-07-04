#include "FadeInImage.h"

#include "Component/Animation/UAnimator.h"
#include "Component/Animation/USpriteAnimation.h"
#include "Component/Manager/AnimManager.h"
#include "Component/Manager/SceneManager.h"

namespace LJG
{

	FadeInImage::FadeInImage(const WText& InName)
		: AAnimatedImage(InName)
	{
		mAnimator = CreateDefaultSubObject<UAnimator>();
		mAnimator->SetZOrder(0.1f);
		State_Default = CreateSprite(L"transition_fade");

		mAnimator->AddState(0, State_Default);
		mAnimator->SetOwnerActor(this);

	}

	FadeInImage::~FadeInImage() {}
}
