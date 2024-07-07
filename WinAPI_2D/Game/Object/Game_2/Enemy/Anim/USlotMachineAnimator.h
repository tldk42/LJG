#pragma once
#include "Component/Animation/UAnimator.h"

namespace LJG
{
	class USlotMachineAnimator : public UAnimator
	{
	public:
		explicit USlotMachineAnimator();
		~USlotMachineAnimator() override;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

		// Anim States
		USpriteAnimation* State_Intro;

		USpriteAnimation* State_Idle;

		USpriteAnimation* Arm_Move_Start;
		USpriteAnimation* Arm_Move_Idle;

		USpriteAnimation* State_Dead;
	};
}
