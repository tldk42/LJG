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
		UPawnMovementComponent2D* mOwnerMovementComp;

		
		// Anim States
		USpriteAnimation* State_Intro;

		USpriteAnimation* State_Idle;
		
		USpriteAnimation* State_Roll_Left;
		USpriteAnimation* State_Roll_Right;
		
		USpriteAnimation* State_Attack_Butterfly;
		USpriteAnimation* State_Attack_Fan;

		USpriteAnimation* State_Dead;
	};
}
