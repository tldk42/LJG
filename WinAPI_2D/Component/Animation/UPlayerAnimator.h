#pragma once
#include "UAnimator.h"


namespace LJG
{
	class UPawnMovementComponent2D;

	class UPlayerAnimator : public UAnimator
	{
	public:
		explicit UPlayerAnimator(const WText& InKey);
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
		UPawnMovementComponent2D* mOwnerMovementComp;

		// Anim States
		USpriteAnimation* State_Idle;
		USpriteAnimation* State_Move_Ground;
		USpriteAnimation* State_Move_Air;
		USpriteAnimation* State_Dash_Ground;
		USpriteAnimation* State_Dash_Air;
		USpriteAnimation* State_Jump;
	};
}
