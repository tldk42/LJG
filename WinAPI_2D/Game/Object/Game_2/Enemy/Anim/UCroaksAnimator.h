#pragma once
#include "Component/Animation/UAnimator.h"

namespace LJG
{
	class UPawnMovementComponent2D;

	class UCroaksAnimator : public UAnimator
	{
	public:
		explicit UCroaksAnimator();
		~UCroaksAnimator() override;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

	private:
		// Properties


		// Anim States
		USpriteAnimation* State_Intro;

		USpriteAnimation* State_Idle;

		USpriteAnimation* State_Roll_Left;
		USpriteAnimation* State_Roll_Right;

		USpriteAnimation* State_Attack_Spit_Start;
		USpriteAnimation* State_Attack_Spit_Loop;
		USpriteAnimation* State_Attack_Spit_End;

		USpriteAnimation* State_Attack_Fan_Start;
		USpriteAnimation* State_Attack_Fan_Loop1;
		USpriteAnimation* State_Attack_Fan_Loop2;
		USpriteAnimation* State_Attack_Fan_End;

		USpriteAnimation* State_Morph_Intro;
		USpriteAnimation* State_Morph_Loop;
		USpriteAnimation* State_Morph_Outro;

		USpriteAnimation* State_Dead;
	};
}
