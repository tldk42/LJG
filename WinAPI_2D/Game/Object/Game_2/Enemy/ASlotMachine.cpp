#include "ASlotMachine.h"

#include "Anim/USlotMachineAnimator.h"
#include "Component/UImage.h"
#include "Game/AI/Test/Blackboard_Game2.h"
#include "Shape/UBoxComponent.h"

namespace LJG
{
	ASlotMachine::ASlotMachine()
		: AEnemy(L"SlotMachine"),
		  mCurrentState(ESlotMachineState::Idle) {}

	ASlotMachine::~ASlotMachine() {}

	void ASlotMachine::Initialize()
	{
		mAnimator = CreateDefaultSubObject<USlotMachineAnimator>();
		mAnimator->SetupAttachment(this);
		mAnimator->SetOwnerActor(this);
		mAnimator->Initialize();

		APawn::Initialize();

		SetWorldLocation({200.f * 1.5f, -200.f * 1.5f});
		mDebugBox->SetScale({200.f, 400.f});

		mTimer.Reset();

		const FVector2f machineLoc = GetWorldLocation() + mSlotOffset;
		for (int32_t i = 0; i < 3; ++i)
		{
			mSlots[i] = CreateDefaultSubObject<UImage>(
				std::format(L"Slot[{}]", i + 1), L"rsc/Sprite/tallfrog_slotman_slot_TEMP.png", .5f);
			mSlots[i]->SetOwnerActor(this);
			mSlots[i]->SetWorldLocation(machineLoc + FVector2f(55.f * i, 0));
		}
	}

	void ASlotMachine::Update(float DeltaTime)
	{
		AEnemy::Update(DeltaTime);
	}

	void ASlotMachine::OnDead()
	{
		AEnemy::OnDead();
	}

	void ASlotMachine::OnHit(float InDamage)
	{
		AEnemy::OnHit(InDamage);

		BB_Game2.CurrentHP -= InDamage;

		if (BB_Game2.CurrentHP <= 0)
		{
			BB_Game2.ChangePhase();
		}
	}

	uint8_t ASlotMachine::GetState()
	{
		return 0;
	}

	void ASlotMachine::SetState(uint8_t NewState)
	{
		mCurrentState = static_cast<ESlotMachineState>(NewState);
		switch (mCurrentState)
		{
		case ESlotMachineState::Intro:
			mAnimator->SetState(NewState, false);
			break;
		case ESlotMachineState::Idle:
			mAnimator->SetState(NewState, true);
			break;
		case ESlotMachineState::Arm_Move_Start:
			break;
		case ESlotMachineState::Attack_Coin:
			break;
		case ESlotMachineState::Attack_Cow:
			break;
		case ESlotMachineState::Attack_Snake:
			break;
		case ESlotMachineState::Attack_Tiger:
			break;
		case ESlotMachineState::Dead:
			break;
		case ESlotMachineState::End:
			break;
		}
	}
}
