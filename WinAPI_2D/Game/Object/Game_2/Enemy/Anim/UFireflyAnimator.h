#pragma once
#include "Component/Animation/UAnimator.h"

namespace LJG
{
	class UFlyingMovementComponent;

	class UFireflyAnimator : public UAnimator
	{
	public:
		explicit UFireflyAnimator();
		~UFireflyAnimator() override;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

	private:
		UFlyingMovementComponent* mOwnerMovementComp;

		USpriteAnimation* State_Idle;
		USpriteAnimation* State_Down;
		USpriteAnimation* State_Up;
		USpriteAnimation* State_Left;

		USpriteAnimation* State_Dead;
	};
}
