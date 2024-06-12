#include "UPlayerAnimator.h"
#include "PlayerData.h"
#include "UAnimation.h"
#include "XSprite2D.h"

namespace LJG
{

	void UPlayerAnimator::Initialize()
	{
		UAnimator::Initialize();

		mIdleState = CreateDefaultSubObject<UAnimation>(L"IdleAnimSet", LoadAnimation(L"rsc/ND/Idle/LD_Idle_", 60));
		mMoveState = CreateDefaultSubObject<
			UAnimation>(L"MoveAnimSet", LoadAnimation(L"rsc/ND/Move/LD_Run_", 5, 20, true));
		mAttackState = CreateDefaultSubObject<UAnimation>(L"AttackAnimSet",
														  LoadAnimation(L"rsc/ND/Attack/LD_Combo2b_", 22));

		AddState(EnumAsByte(EPlayerAnimState::Idle), mIdleState);
		AddState(EnumAsByte(EPlayerAnimState::Move), mMoveState);
		AddState(EnumAsByte(EPlayerAnimState::Attack), mAttackState);
	}

	void UPlayerAnimator::Update(float DeltaTime)
	{
		UAnimator::Update(DeltaTime);
	}

	void UPlayerAnimator::Render()
	{
		UAnimator::Render();
	}

	void UPlayerAnimator::Release()
	{
		UAnimator::Release();
	}
}
