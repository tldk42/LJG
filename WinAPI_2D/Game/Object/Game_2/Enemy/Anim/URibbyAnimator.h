#pragma once
#include "Component/Animation/UAnimator.h"

namespace LJG
{
	class UPawnMovementComponent2D;

	class URibbyAnimator : public UAnimator
	{
	public:
		explicit URibbyAnimator();
		~URibbyAnimator() override;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

	private:
		// Properties
		UPawnMovementComponent2D* mOwnerMovementComp;

		// Anim States
		USpriteAnimation* State_Intro;

		USpriteAnimation* State_Idle;

		USpriteAnimation* State_Roll_Left;
		USpriteAnimation* State_Roll_Right;

		USpriteAnimation* State_Attack_Punch_Start;
		USpriteAnimation* State_Attack_Punch_Loop;
		USpriteAnimation* State_Attack_Spike;

		USpriteAnimation* Dead;

	};
}
