#include "URibbyAnimator.h"

#include "Component/Animation/USpriteAnimation.h"
#include "Component/Manager/AnimManager.h"
#include "data/MonsterData.h"
#include "Helper/EngineHelper.h"

namespace LJG
{

	URibbyAnimator::URibbyAnimator()
	{
		State_Intro = CreateSprite(L"shortFrog_intro");
		State_Idle  = CreateSprite(L"shortFrog_idle");


		AddState(EnumAsByte(ERibbyState::Intro), State_Intro);
		AddState(EnumAsByte(ERibbyState::Idle), State_Idle);

		State_Intro->OnAnimFinished.Bind([this](){
			SetState(EnumAsByte(ERibbyState::Idle), true);
		});
	}

	URibbyAnimator::~URibbyAnimator() {}

	void URibbyAnimator::Initialize()
	{
		UAnimator::Initialize();

		mCurrentState = EnumAsByte(ERibbyState::Intro);
		PlayDefaultTrack(false, false);
	}

	void URibbyAnimator::Update(float DeltaTime)
	{
		UAnimator::Update(DeltaTime);
	}

	void URibbyAnimator::Render()
	{
		UAnimator::Render();
	}

	void URibbyAnimator::Release()
	{
		UAnimator::Release();
	}
}
