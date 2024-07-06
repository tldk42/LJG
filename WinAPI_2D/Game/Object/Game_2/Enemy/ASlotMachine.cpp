#include "ASlotMachine.h"

namespace LJG
{
	ASlotMachine::ASlotMachine()
		: AEnemy(L"SlotMachine"),
		  mCurrentState(ESlotMachineState::Idle) {}

	ASlotMachine::~ASlotMachine() {}

	void ASlotMachine::Initialize()
	{
		AEnemy::Initialize();
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
			break;
		case ESlotMachineState::Idle:
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
