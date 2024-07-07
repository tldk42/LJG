#include "UCroaksAnimator.h"

#include "Component/Animation/USpriteAnimation.h"
#include "data/MonsterData.h"
#include "Game/Object/Game_2/Enemy/ACroaks.h"
#include "Game/Object/Game_2/Enemy/ASlotMachine.h"
#include "Helper/EngineHelper.h"

namespace LJG
{
	UCroaksAnimator::UCroaksAnimator()
	{
		State_Intro = CreateSprite(L"tallfrog_intro");
		State_Idle  = CreateSprite(L"tallfrog_idle");

		State_Attack_Spit_Start = CreateSprite(L"tallfrog_spit_start");
		State_Attack_Spit_Loop  = CreateSprite(L"tallfrog_spit_loop");
		State_Attack_Spit_End   = CreateSprite(L"tallfrog_spit_end");

		State_Attack_Fan_Start = CreateSprite(L"tallfrog_fan_intro");
		State_Attack_Fan_Loop1 = CreateSprite(L"tallfrog_fan_loop1");
		State_Attack_Fan_Loop2 = CreateSprite(L"tallfrog_fan_loop2");
		State_Attack_Fan_End   = CreateSprite(L"tallfrog_fan_outro");

		State_Morph_Intro = CreateSprite(L"tallfrog_morph_start");
		State_Morph_Loop  = CreateSprite(L"tallfrog_morph_loop");
		State_Morph_Outro = CreateSprite(L"tallfrog_morph_end");

		State_Attack_Fan_Start->SetSpeed(1.f);
		State_Attack_Fan_Loop1->SetSpeed(3.f);
		State_Attack_Fan_Loop2->SetSpeed(5.f);
		State_Attack_Fan_End->SetSpeed(3.f);

		AddState(EnumAsByte(ECroaksState::Intro), State_Intro);
		AddState(EnumAsByte(ECroaksState::Idle), State_Idle);

		AddState(EnumAsByte(ECroaksState::Attack_Spit_Start), State_Attack_Spit_Start);
		AddState(EnumAsByte(ECroaksState::Attack_Spit_Loop), State_Attack_Spit_Loop);
		AddState(EnumAsByte(ECroaksState::Attack_Spit_End), State_Attack_Spit_End);

		AddState(EnumAsByte(ECroaksState::Attack_Fan_Start), State_Attack_Fan_Start);
		AddState(EnumAsByte(ECroaksState::Attack_Fan_Loop1), State_Attack_Fan_Loop1);
		AddState(EnumAsByte(ECroaksState::Attack_Fan_Loop2), State_Attack_Fan_Loop2);
		AddState(EnumAsByte(ECroaksState::Attack_Fan_End), State_Attack_Fan_End);

		AddState(EnumAsByte(ECroaksState::Morph_Intro), State_Morph_Intro);
		AddState(EnumAsByte(ECroaksState::Morph_Loop), State_Morph_Loop);
		AddState(EnumAsByte(ECroaksState::Morph_Outro), State_Morph_Outro);


		// On Animation Finished
		State_Intro->OnAnimFinished.Bind([this](){
			SetState(EnumAsByte(ECroaksState::Idle), true);
		});
		State_Attack_Spit_Start->OnAnimFinished.Bind([&](){
			Croaks.SetState(EnumAsByte(ECroaksState::Attack_Spit_Loop));
		});

		State_Morph_Intro->OnAnimFinished.Bind([&](){
			Croaks.SetState(EnumAsByte(ECroaksState::Morph_Loop));
		});
		State_Morph_Outro->OnAnimFinished.Bind([&](){
			SlotMachine.SetActive(true);
			SlotMachine.SetState(EnumAsByte(ESlotMachineState::Intro));
			Croaks.SetActive(false);
		});

		State_Attack_Fan_Start->OnAnimFinished.Bind([this](){
			Croaks.SetState(EnumAsByte(ECroaksState::Attack_Fan_Loop1));
		});

		// Notify
		State_Attack_Spit_Loop->OnAnimNotifyBegin[2].Bind([&](){
			Croaks.Spit();
		});

		State_Attack_Fan_Loop1->OnAnimNotifyBegin[4].Bind([&](){
			Croaks.AddFanCounter();
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
