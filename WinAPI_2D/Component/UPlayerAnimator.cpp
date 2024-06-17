#include "UPlayerAnimator.h"

#include "AActor.h"
#include "PlayerData.h"
#include "UAnimation.h"
#include "UPawnMovementComponent2D.h"
#include "DirectX/XSprite2D.h"

namespace LJG
{

	void UPlayerAnimator::Initialize()
	{
		UAnimator::Initialize();

		assert(mOwnerActor);

		mMovementComponent = dynamic_cast<UPawnMovementComponent2D*>(mOwnerActor->GetComponentByID(L"MovementComponent"));
		assert(mMovementComponent);

		mIdleState = CreateDefaultSubObject<UAnimation>(L"IdleAnimSet", LoadAnimation(L"rsc/ND/Idle/LD_Idle_", 60));
		mMoveState = CreateDefaultSubObject<
			UAnimation>(L"MoveAnimSet", LoadAnimation(L"rsc/ND/Move/LD_Run_", 5, 20, true));
		mAttackState = CreateDefaultSubObject<UAnimation>(L"AttackAnimSet",
														  LoadAnimation(L"rsc/ND/Attack/LD_Combo2b_", 22));

		mIdleState->SetupAttachment(this);
		mMoveState->SetupAttachment(this);
		mAttackState->SetupAttachment(this);

		AddState(EnumAsByte(EPlayerAnimState::Idle), mIdleState);
		AddState(EnumAsByte(EPlayerAnimState::Move), mMoveState);
		AddState(EnumAsByte(EPlayerAnimState::Attack), mAttackState);


		mIdleState->AddTransition(EnumAsByte(EPlayerAnimState::Move), [this](){
			return !mMovementComponent->GetVelocity().IsNearlyZero();
		}, mMoveState);

		mMoveState->AddTransition(EnumAsByte(EPlayerAnimState::Idle), [this](){
			return mMovementComponent->GetVelocity().IsNearlyZero();
		}, mIdleState);

		SetState(EnumAsByte(EPlayerAnimState::Idle), true);
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
