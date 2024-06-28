#include "UPlayerAnimator.h"

#include "InputManager.h"
#include "Component/Actor/AActor.h"
#include "PlayerData.h"
#include "USpriteAnimation.h"
#include "DirectX/XTexture.h"
#include "Component/UPawnMovementComponent2D.h"
#include "Component/Actor/APlayerCharacter.h"
#include "Component/Manager/AnimManager.h"
#include "Helper/EngineHelper.h"

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
		State_Duck_Start  = CreateDefaultSubObject<USpriteAnimation>(L"PA_Duck_Start");
		State_Duck_Loop   = CreateDefaultSubObject<USpriteAnimation>(L"PA_Duck_Loop");
		State_Attack_Idle = CreateDefaultSubObject<USpriteAnimation>(L"PA_Attack_Idle");
		State_Attack_Move = CreateDefaultSubObject<USpriteAnimation>(L"PA_Attack_Move");


		State_Idle->SetAnimData(*Manager_Anim.CreateOrLoad(L"cuphead_idle"));
		State_Move_Ground->SetAnimData(*Manager_Anim.CreateOrLoad(L"cuphead_run"));
		State_Move_Air->SetAnimData(*Manager_Anim.CreateOrLoad(L"cuphead_idle"));
		State_Dash_Ground->SetAnimData(*Manager_Anim.CreateOrLoad(L"cuphead_idle"));
		State_Dash_Air->SetAnimData(*Manager_Anim.CreateOrLoad(L"cuphead_idle"));
		State_Jump->SetAnimData(*Manager_Anim.CreateOrLoad(L"cuphead_jump"));
		State_Duck_Start->SetAnimData(*Manager_Anim.CreateOrLoad(L"cuphead_duck"));
		State_Duck_Loop->SetAnimData(*Manager_Anim.CreateOrLoad(L"cuphead_duck_idle"));
		State_Attack_Idle->SetAnimData(*Manager_Anim.CreateOrLoad(L"cuphead_shoot_straight"));
		State_Attack_Move->SetAnimData(*Manager_Anim.CreateOrLoad(L"cuphead_run_shoot"));

		AddState(EnumAsByte(EPlayerAnimState::Idle), State_Idle);
		AddState(EnumAsByte(EPlayerAnimState::Move), State_Move_Ground);
		AddState(EnumAsByte(EPlayerAnimState::Jump), State_Jump);
		AddState(EnumAsByte(EPlayerAnimState::Duck_Start), State_Duck_Start);
		AddState(EnumAsByte(EPlayerAnimState::Duck_Idle), State_Duck_Loop);
		AddState(EnumAsByte(EPlayerAnimState::Shoot), State_Attack_Idle);
		AddState(EnumAsByte(EPlayerAnimState::Move_Shoot), State_Attack_Move);
	}

	UPlayerAnimator::~UPlayerAnimator() {}

	void UPlayerAnimator::Initialize()
	{
		UAnimator::Initialize();

		mOwnerMovementComp = static_cast<UPawnMovementComponent2D*>(GetOwnerActor()->
			GetComponentByID(L"MovementComponent"));

		auto IsMoving    = [this](){ return !mOwnerMovementComp->GetVelocity().IsNearlyZero(); };
		auto IsJumping   = [this](){ return mOwnerMovementComp->IsJumping(); };
		auto IsCrouching = [this](){ return mOwnerMovementComp->IsCrouching(); };
		auto IsAttacking = [this](){ return LocalPlayer.IsAttacking(); };

#pragma region Idle ->
		AddTransition(EnumAsByte(EPlayerAnimState::Idle), EnumAsByte(EPlayerAnimState::Move),
					  IsMoving);
		AddTransition(EnumAsByte(EPlayerAnimState::Idle), EnumAsByte(EPlayerAnimState::Jump),
					  IsJumping);
		AddTransition(EnumAsByte(EPlayerAnimState::Idle), EnumAsByte(EPlayerAnimState::Duck_Start),
					  IsCrouching);
		AddTransition(EnumAsByte(EPlayerAnimState::Idle), EnumAsByte(EPlayerAnimState::Shoot),
					  IsAttacking);
#pragma endregion

#pragma region Move ->
		AddTransition(EnumAsByte(EPlayerAnimState::Move), EnumAsByte(EPlayerAnimState::Idle),
					  [IsMoving](){ return !IsMoving(); });
		AddTransition(EnumAsByte(EPlayerAnimState::Move), EnumAsByte(EPlayerAnimState::Jump),
					  IsJumping);
		AddTransition(EnumAsByte(EPlayerAnimState::Move), EnumAsByte(EPlayerAnimState::Duck_Start),
					  IsCrouching);
		AddTransition(EnumAsByte(EPlayerAnimState::Move), EnumAsByte(EPlayerAnimState::Move_Shoot),
					  IsAttacking);
#pragma endregion

#pragma region Jump ->
		AddTransition(EnumAsByte(EPlayerAnimState::Jump), EnumAsByte(EPlayerAnimState::Move_Shoot),
					  [IsJumping, IsMoving, IsAttacking](){ return !IsJumping() && IsMoving() && IsAttacking(); });
		AddTransition(EnumAsByte(EPlayerAnimState::Jump), EnumAsByte(EPlayerAnimState::Move),
					  [IsJumping, IsMoving](){ return !IsJumping() && IsMoving(); });
		AddTransition(EnumAsByte(EPlayerAnimState::Jump), EnumAsByte(EPlayerAnimState::Idle),
					  [IsJumping](){ return !IsJumping(); });
#pragma endregion

#pragma region Crouch ->
		AddTransition(EnumAsByte(EPlayerAnimState::Duck_Start), EnumAsByte(EPlayerAnimState::Duck_Idle),
					  [&](){ return true; });
		AddTransition(EnumAsByte(EPlayerAnimState::Duck_Idle), EnumAsByte(EPlayerAnimState::Idle),
					  [IsCrouching, IsMoving](){ return !IsCrouching() && !IsMoving(); });
		AddTransition(EnumAsByte(EPlayerAnimState::Duck_Idle), EnumAsByte(EPlayerAnimState::Move),
					  [IsCrouching](){ return !IsCrouching(); });
#pragma endregion

#pragma region Shoot ->
		AddTransition(EnumAsByte(EPlayerAnimState::Shoot), EnumAsByte(EPlayerAnimState::Idle),
					  [IsAttacking](){ return !IsAttacking(); });
		AddTransition(EnumAsByte(EPlayerAnimState::Shoot), EnumAsByte(EPlayerAnimState::Jump),
					  IsJumping);
		AddTransition(EnumAsByte(EPlayerAnimState::Shoot), EnumAsByte(EPlayerAnimState::Move_Shoot),
					  IsMoving);

		AddTransition(EnumAsByte(EPlayerAnimState::Move_Shoot), EnumAsByte(EPlayerAnimState::Shoot),
					  [IsMoving](){ return !IsMoving(); });
		AddTransition(EnumAsByte(EPlayerAnimState::Move_Shoot), EnumAsByte(EPlayerAnimState::Move),
					  [IsAttacking](){ return !IsAttacking(); });
		AddTransition(EnumAsByte(EPlayerAnimState::Move_Shoot), EnumAsByte(EPlayerAnimState::Jump),
					  IsJumping);
#pragma endregion

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
	}\
\
}
