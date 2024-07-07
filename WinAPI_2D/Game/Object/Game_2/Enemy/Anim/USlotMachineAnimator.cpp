#include "USlotMachineAnimator.h"

#include "data/MonsterData.h"
#include "Helper/EngineHelper.h"
#include "Component/Animation/USpriteAnimation.h"
#include "Game/Object/Game_2/Enemy/ASlotMachine.h"
namespace LJG
{

	USlotMachineAnimator::USlotMachineAnimator()
	{
		State_Intro    = CreateSprite(L"slotmachine_open");
		State_Idle     = CreateSprite(L"slotmachine_idle");
		Arm_Move_Start = CreateSprite(L"tallfrog_slotman_arm_move_intro");
		Arm_Move_Idle  = CreateSprite(L"tallfrog_slotman_arm_loop");
		// State_Dead     = CreateSprite(L"");

		AddState(EnumAsByte(ESlotMachineState::Intro), State_Intro);
		AddState(EnumAsByte(ESlotMachineState::Idle), State_Idle);
		AddState(EnumAsByte(ESlotMachineState::Arm_Move_Start), Arm_Move_Start);
		AddState(EnumAsByte(ESlotMachineState::Arm_Move_Idle), Arm_Move_Idle);

		State_Intro->OnAnimFinished.Bind([&](){
			SlotMachine.SetState(EnumAsByte(ESlotMachineState::Idle));
		});
		Arm_Move_Start->OnAnimFinished.Bind([&](){
			SlotMachine.SetState(EnumAsByte(ESlotMachineState::Arm_Move_Idle));
		});
	}

	USlotMachineAnimator::~USlotMachineAnimator() {}

	void USlotMachineAnimator::Initialize()
	{
		UAnimator::Initialize();
	}

	void USlotMachineAnimator::Update(float DeltaTime)
	{
		UAnimator::Update(DeltaTime);
	}

	void USlotMachineAnimator::Render()
	{
		UAnimator::Render();
	}

	void USlotMachineAnimator::Release()
	{
		UAnimator::Release();
	}
}
