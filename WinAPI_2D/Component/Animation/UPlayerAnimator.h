#pragma once
#include "UAnimator.h"

namespace LJG
{
	class AProjectile;
	class UPlayerMovementComponent;

	class UPlayerAnimator : public UAnimator
	{
	public:
		explicit UPlayerAnimator();
		~UPlayerAnimator() override;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

	private:
		// Properties
		UPlayerMovementComponent* mOwnerMovementComp;

		// Anim States
		USpriteAnimation* State_Idle;
		USpriteAnimation* State_Move_Ground;
		USpriteAnimation* State_Move_Air;
		USpriteAnimation* State_Dash_Ground;
		USpriteAnimation* State_Dash_Air;
		USpriteAnimation* State_Jump;
		// USpriteAnimation* State_Parry;
		USpriteAnimation* State_Duck_Start;
		USpriteAnimation* State_Duck_Loop;
		USpriteAnimation* State_Attack_Idle;
		USpriteAnimation* State_Attack_Up;
		USpriteAnimation* State_Attack_Move;
		USpriteAnimation* State_Attack_Move_Diagonal;
		USpriteAnimation* State_Attack_Duck;

		bool bParryAnimApplied;
	};
}
