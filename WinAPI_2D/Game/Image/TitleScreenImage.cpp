#include "TitleScreenImage.h"

#include "Game/Animator/TitleScreenAnimator.h"

namespace LJG
{

	TitleScreenImage::TitleScreenImage(const WText& InName)
		: AAnimatedImage(InName)
	{
		mAnimator = CreateDefaultSubObject<TitleScreenAnimator>();
		mAnimator->SetOwnerActor(this);
	}

	TitleScreenImage::~TitleScreenImage()
	{
	
	}
	
}
