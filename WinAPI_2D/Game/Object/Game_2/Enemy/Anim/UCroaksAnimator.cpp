#include "UCroaksAnimator.h"

#include "Component/Animation/USpriteAnimation.h"
#include "Component/Manager/AnimManager.h"
#include "data/MonsterData.h"
#include "Helper/EngineHelper.h"

namespace LJG
{
	UCroaksAnimator::UCroaksAnimator()
	{

		State_Intro            = CreateSprite(L"tallfrog_intro");
		State_Idle             = CreateSprite(L"tallfrog_idle");
		// State_Roll_Left        = CreateSprite(L"Croaks_Roll_Right");
		// State_Roll_Right       = CreateSprite(L"Croaks_Roll_Left");
		// State_Attack_Butterfly = CreateSprite(L"Croaks_Attack_Butterfly");
		// State_Attack_Fan       = CreateSprite(L"Croaks_Attack_Fan");
		// State_Dead             = CreateSprite(L"Croaks_Dead");
		


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
