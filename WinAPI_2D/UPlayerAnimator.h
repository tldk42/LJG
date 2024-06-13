#pragma once
#include "UAnimator.h"

namespace LJG
{
	class UPlayerAnimator : public UAnimator
	{
	public:
		UPlayerAnimator()           = default;
		~UPlayerAnimator() override = default ;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

	private:
		UAnimation* mIdleState;
		UAnimation* mMoveState;
		UAnimation* mAttackState;
	};

}
