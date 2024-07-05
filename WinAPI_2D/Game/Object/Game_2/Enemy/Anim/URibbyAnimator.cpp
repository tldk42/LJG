#include "URibbyAnimator.h"

#include "Component/Animation/USpriteAnimation.h"
#include "Component/Manager/AnimManager.h"
#include "data/MonsterData.h"
#include "Game/Object/Game_2/Enemy/ARibby.h"
#include "Helper/EngineHelper.h"

namespace LJG
{

	URibbyAnimator::URibbyAnimator()
	{
		State_Intro                    = CreateSprite(L"shortFrog_intro");
		State_Idle                     = CreateSprite(L"shortFrog_idle");
		State_Roll_Intro_Start         = CreateSprite(L"shortFrog_roll_intro_start");
		State_Roll_Intro_Loop          = CreateSprite(L"shortFrog_roll_intro_loop");
		State_Roll_Intro_End           = CreateSprite(L"shortFrog_roll_intro_end");
		State_Roll_Loop                = CreateSprite(L"shortFrog_roll_loop");
		State_Roll_End                 = CreateSprite(L"shortFrog_roll_end");
		State_Attack_Punch_Start       = CreateSprite(L"shortFrog_fist_start");
		State_Attack_Punch_Loop        = CreateSprite(L"shortFrog_fist_loop");
		State_Attack_Punch_End         = CreateSprite(L"shortFrog_fist_end");
		State_Attack_Spike_Intro_Start = CreateSprite(L"shortFrog_clap_intro_start");
		State_Attack_Spike_Intro_Loop  = CreateSprite(L"shortFrog_clap_intro_loop");
		State_Attack_Spike_Loop        = CreateSprite(L"shortFrog_clap_loop");
		// State_Dead               = CreateSprite(L"Croaks_Dead");


		AddState(EnumAsByte(ERibbyState::Intro), State_Intro);
		AddState(EnumAsByte(ERibbyState::Idle), State_Idle);
		AddState(EnumAsByte(ERibbyState::Roll_Intro_Start), State_Roll_Intro_Start);
		AddState(EnumAsByte(ERibbyState::Roll_Intro_Loop), State_Roll_Intro_Loop);
		AddState(EnumAsByte(ERibbyState::Roll_Intro_End), State_Roll_Intro_End);
		AddState(EnumAsByte(ERibbyState::Roll_Loop), State_Roll_Loop);
		AddState(EnumAsByte(ERibbyState::Roll_End), State_Roll_End);
		AddState(EnumAsByte(ERibbyState::Attack_Punch_Start), State_Attack_Punch_Start);
		AddState(EnumAsByte(ERibbyState::Attack_Punch_Loop), State_Attack_Punch_Loop);
		AddState(EnumAsByte(ERibbyState::Attack_Punch_End), State_Attack_Punch_End);
		AddState(EnumAsByte(ERibbyState::Attack_Spike_Intro_Start), State_Attack_Spike_Intro_Start);
		AddState(EnumAsByte(ERibbyState::Attack_Spike_Intro_Loop), State_Attack_Spike_Intro_Loop);
		AddState(EnumAsByte(ERibbyState::Attack_Spike_Loop), State_Attack_Spike_Loop);

		State_Intro->OnAnimFinished.Bind([this](){
			SetState(EnumAsByte(ERibbyState::Idle), true);
		});
		State_Attack_Punch_Start->OnAnimFinished.Bind([this](){
			// SetState(EnumAsByte(ERibbyState::Attack_Punch_Loop), true);
			Ribby.SetState(EnumAsByte(ERibbyState::Attack_Punch_Loop));
		});

		// Phase 2 Auto Transition
		State_Roll_Intro_Start->OnAnimFinished.Bind([this](){
			Ribby.SetState(EnumAsByte(ERibbyState::Roll_Intro_Loop));
		});
		State_Roll_Intro_End->OnAnimFinished.Bind([this](){
			Ribby.SetState(EnumAsByte(ERibbyState::Roll_Loop));
		});
		State_Roll_End->OnAnimFinished.Bind([this](){
			Ribby.SetState(EnumAsByte(ERibbyState::Idle));
		});

		State_Attack_Spike_Intro_Start->OnAnimFinished.Bind([&](){
			Ribby.SetState(EnumAsByte(ERibbyState::Attack_Spike_Intro_Loop));
		});

		State_Attack_Spike_Loop->OnAnimNotifyBegin[4].Bind(std::bind(&ARibby::SpikeBall, &Ribby));
	}

	URibbyAnimator::~URibbyAnimator() {}

	void URibbyAnimator::Initialize()
	{
		UAnimator::Initialize();

		mCurrentState = Ribby.GetState();
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
