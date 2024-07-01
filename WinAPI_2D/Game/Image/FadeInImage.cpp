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
		mAnimator = CreateDefaultSubObject<UAnimator>(L"Animator");
		mAnimator->SetZOrder(0.1f);
		State_Default = CreateDefaultSubObject<USpriteAnimation>(L"Default");

		State_Default->SetAnimData(*Manager_Anim.CreateOrLoad(L"transition_fade"));
		// State_Default->OnAnimFinished.Bind([](){ Manager_Scene.GetCurrentScene()->MoveScene(L"Menu"); });
		mAnimator->AddState(0, State_Default);
		mAnimator->SetOwnerActor(this);

	}

	FadeInImage::~FadeInImage() {}
}
