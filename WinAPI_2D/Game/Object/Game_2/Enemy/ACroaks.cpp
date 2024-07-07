#include "ACroaks.h"

#include "AFirefly.h"
#include "ARibby.h"
#include "AWindSprite.h"
#include "FTimer.h"
#include "Anim/UCroaksAnimator.h"
#include "Component/Animation/UAnimator.h"
#include "Game/AI/Test/Blackboard_Game2.h"
#include "Helper/EngineHelper.h"
#include "Shape/UBoxComponent.h"

namespace LJG
{

	ACroaks::ACroaks()
		: AEnemy(L"Croaks"),
		  mCurrentState(ECroaksState::Idle) {}

	ACroaks::~ACroaks() {}

	void ACroaks::Initialize()
	{
		mAnimator = CreateDefaultSubObject<UCroaksAnimator>();
		mAnimator->SetupAttachment(this);
		mAnimator->SetOwnerActor(this);
		mAnimator->Initialize();

		APawn::Initialize();

		SetWorldLocation({250.f * 1.5f, -127.9f * 1.5f});
		mDebugBox->SetScale({200.f, 400.f});

		mWindImage = CreateDefaultSubObject<AWindSprite>();
		mWindImage->SetActive(false);
		mWindImage->SetOwnerActor(this);

		mTimer.Reset();

		SetActive(true);
	}

	void ACroaks::Update(float DeltaTime)
	{
		APawn::Update(DeltaTime);
	}

	void ACroaks::OnDead()
	{
		AEnemy::OnDead();
	}

	void ACroaks::OnHit(float InDamage)
	{
		AEnemy::OnHit(InDamage);

		BB_Game2.CurrentHP -= InDamage;

		if (BB_Game2.CurrentHP <= 0)
		{
			BB_Game2.ChangePhase();
		}

	}

	uint8_t ACroaks::GetState()
	{
		return EnumAsByte(mCurrentState);
	}

	void ACroaks::SetState(uint8_t NewState)
	{
		mCurrentState = static_cast<ECroaksState>(NewState);

		switch (mCurrentState)
		{

		case ECroaksState::Intro:
			break;
		case ECroaksState::Idle:
			mTimer.Reset();
			mAnimator->SetState(NewState, true);
			break;
		case ECroaksState::Roll_Left:
			break;
		case ECroaksState::Roll_Right:
			break;
		case ECroaksState::Attack_Spit_Start:
			mTimer.Reset();
			mLastLaunchTime = 0.f;
			mAnimator->SetState(NewState, false);
			break;
		case ECroaksState::Attack_Spit_Loop:
			mAnimator->SetState(NewState, true);
			break;
		case ECroaksState::Attack_Spit_End:
			mTimer.Reset();
			break;

		case ECroaksState::Attack_Fan_Start:
		case ECroaksState::Attack_Fan_End:
			mAnimator->SetState(NewState, false);
			break;
		case ECroaksState::Attack_Fan_Loop1:
			mAnimator->SetState(NewState, true);
			mWindImage->SetActive(true);
			mWindImage->Play(false, true);
			break;
		case ECroaksState::Attack_Fan_Loop2:
			mAnimator->SetState(NewState, true);
			break;

		case ECroaksState::Dead:
			break;
		case ECroaksState::End:
			break;
		case ECroaksState::Morph_Intro:
			mAnimator->SetState(NewState, false);
			mWindImage->SetActive(false);
			break;
		case ECroaksState::Morph_Loop:
			mAnimator->SetState(NewState, true);
			break;
		case ECroaksState::Morph_Outro:
			mAnimator->SetState(NewState, false);
			break;
		}
	}

	void ACroaks::TryAttack_Spit()
	{
		const float_t elapsedSeconds = mTimer.ElapsedSeconds();
		if (elapsedSeconds > 6.f)
		{
			SetState(EnumAsByte(ERibbyState::Idle));
			Ribby.SetTurn();
		}
	}

	void ACroaks::Spit() const
	{
		AFirefly* firefly = Manager_Object.Spawn<AFirefly>();
		firefly->Initialize();
		firefly->SetWorldLocation({GetWorldLocation().X - 163.f, GetWorldLocation().Y + 203.f});
		firefly->SetSkyTarget({FMath::GenerateRandomfloat(-450, 200), FMath::GenerateRandomfloat(150, 250)});
	}

}
