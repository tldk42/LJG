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
		mAnimator->SetZOrder(0.1f);
		mAnimator->SeteDefaultTrack(CreateSprite(L"transition_fade"));
	}

	FadeInImage::~FadeInImage() {}
}
