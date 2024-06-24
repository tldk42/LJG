#include "UPlayerAnimator.h"

#include "AActor.h"
#include "PlayerData.h"
#include "USpriteAnimation.h"
#include "DirectX/XTexture.h"
#include "Component/UPawnMovementComponent2D.h"
#include "Component/Manager/AnimManager.h"

namespace LJG
{
	UPlayerAnimator::UPlayerAnimator(const WText& InKey)
		: UAnimator(InKey)
	{
		State_Idle        = CreateDefaultSubObject<USpriteAnimation>(L"PA_Idle");
		State_Move_Ground = CreateDefaultSubObject<USpriteAnimation>(L"PA_Move_Ground");
		State_Move_Air    = CreateDefaultSubObject<USpriteAnimation>(L"PA_Move_Air");
		State_Dash_Ground = CreateDefaultSubObject<USpriteAnimation>(L"PA_Dash_Ground");
		State_Dash_Air    = CreateDefaultSubObject<USpriteAnimation>(L"PA_Dash_Air");
		State_Jump        = CreateDefaultSubObject<USpriteAnimation>(L"PA_Jump");

		State_Idle->SetAnimData(*Manager_Anim.Load(L"cuphead_idle"));
		State_Move_Ground->SetAnimData(*Manager_Anim.Load(L"cuphead_run"));
		State_Move_Air->SetAnimData(*Manager_Anim.Load(L"cuphead_idle"));
		State_Dash_Ground->SetAnimData(*Manager_Anim.Load(L"cuphead_idle"));
		State_Dash_Air->SetAnimData(*Manager_Anim.Load(L"cuphead_idle"));
		State_Jump->SetAnimData(*Manager_Anim.Load(L"cuphead_jump"));

		AddState(EnumAsByte(EPlayerAnimState::Idle), State_Idle);
		AddState(EnumAsByte(EPlayerAnimState::Move), State_Move_Ground);
		AddState(EnumAsByte(EPlayerAnimState::Jump), State_Jump);

	}

	UPlayerAnimator::~UPlayerAnimator() {}

	void UPlayerAnimator::Initialize()
	{
		UAnimator::Initialize();

		mOwnerMovementComp = static_cast<UPawnMovementComponent2D*>(GetOwnerActor()->
			GetComponentByID(L"MovementComponent"));

		AddTransition(EnumAsByte(EPlayerAnimState::Idle), EnumAsByte(EPlayerAnimState::Move),
					  [&](){ return !mOwnerMovementComp->GetVelocity().IsNearlyZero(); });
		AddTransition(EnumAsByte(EPlayerAnimState::Idle), EnumAsByte(EPlayerAnimState::Jump),
					  [&](){ return mOwnerMovementComp->IsJumping(); });
		AddTransition(EnumAsByte(EPlayerAnimState::Move), EnumAsByte(EPlayerAnimState::Idle),
					  [&](){ return mOwnerMovementComp->GetVelocity().IsNearlyZero(); });
		AddTransition(EnumAsByte(EPlayerAnimState::Move), EnumAsByte(EPlayerAnimState::Jump),
					  [&](){ return mOwnerMovementComp->IsJumping(); });
		AddTransition(EnumAsByte(EPlayerAnimState::Jump), EnumAsByte(EPlayerAnimState::Idle),
					  [&](){ return !mOwnerMovementComp->IsJumping(); });
		AddTransition(EnumAsByte(EPlayerAnimState::Jump), EnumAsByte(EPlayerAnimState::Move),
					  [&](){ return !mOwnerMovementComp->IsJumping(); });

		mCurrentState = EnumAsByte(EPlayerAnimState::Idle);
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
