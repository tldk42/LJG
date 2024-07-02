#include "UCroaksAnimator.h"

#include "Component/Animation/USpriteAnimation.h"
#include "Component/Manager/AnimManager.h"
#include "Game/GameData.h"
#include "Helper/EngineHelper.h"

namespace LJG
{
	UCroaksAnimator::UCroaksAnimator()
	{
		State_Intro = CreateDefaultSubObject<USpriteAnimation>(L"Croaks_Intro");
		State_Idle  = CreateDefaultSubObject<USpriteAnimation>(L"Croaks_Idle");

		State_Intro->SetAnimData(*Manager_Anim.CreateOrLoad(L"tallfrog_intro"));
		State_Idle->SetAnimData(*Manager_Anim.CreateOrLoad(L"tallfrog_idle"));


		AddState(EnumAsByte(ECroaksState::Intro), State_Intro);
		AddState(EnumAsByte(ECroaksState::Idle), State_Idle);

		State_Intro->OnAnimFinished.Bind([this](){
			SetState(EnumAsByte(ECroaksState::Idle), true);
		});
	}

	UCroaksAnimator::~UCroaksAnimator() {}

	void UCroaksAnimator::Initialize()
	{
		UAnimator::Initialize();

		mCurrentState = EnumAsByte(ERibbyState::Intro);
		PlayDefaultTrack(false, false);
	}

	void UCroaksAnimator::Update(float DeltaTime)
	{
		UAnimator::Update(DeltaTime);
	}

	void UCroaksAnimator::Render()
	{
		UAnimator::Render();
	}

	void UCroaksAnimator::Release()
	{
		UAnimator::Release();
	}

}

