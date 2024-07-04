#include "UPlayerAnimator.h"

#include "InputManager.h"
#include "Component/Actor/AActor.h"
#include "PlayerData.h"
#include "USpriteAnimation.h"
#include "Component/Movement/UPlayerMovementComponent.h"
#include "Component/Actor/APlayerCharacter.h"
#include "Component/Actor/AProjectile.h"
#include "Helper/EngineHelper.h"

namespace LJG
{
	UPlayerAnimator::UPlayerAnimator()
	{
		State_Idle        = CreateSprite(L"cuphead_idle");
		State_Move_Ground = CreateSprite(L"cuphead_run");
		State_Move_Air    = CreateSprite(L"PA_Move_Air");
		State_Dash_Ground = CreateSprite(L"cuphead_dash");
		State_Dash_Air    = CreateSprite(L"cuphead_dash_air");
		State_Jump        = CreateSprite(L"cuphead_jump");
		State_Duck_Start  = CreateSprite(L"cuphead_duck");
		State_Duck_Loop   = CreateSprite(L"cuphead_duck_idle");
		State_Attack_Idle = CreateSprite(L"cuphead_shoot_straight");
		State_Attack_Move = CreateSprite(L"cuphead_run_shoot");
		State_Attack_Duck = CreateSprite(L"cuphead_duck_shoot");
		State_Attack_Idle->SetSpeed(1.5f);
		State_Attack_Move->SetSpeed(1.5f);
		State_Attack_Duck->SetSpeed(1.5f);


		State_Attack_Idle->OnAnimNotifyBegin[1].Bind(std::bind(&APlayerCharacter::Shoot, &LocalPlayer));
		State_Attack_Duck->OnAnimNotifyBegin[1].Bind(std::bind(&APlayerCharacter::Shoot, &LocalPlayer));
		State_Attack_Move->OnAnimNotifyBegin[5].Bind(std::bind(&APlayerCharacter::Shoot, &LocalPlayer));
		State_Attack_Move->OnAnimNotifyBegin[10].Bind(std::bind(&APlayerCharacter::Shoot, &LocalPlayer));
		// State_Attack_Move->OnAnimNotifyBegin[11].Bind(std::bind(&APlayerCharacter::Shoot, &LocalPlayer));
		State_Attack_Move->OnAnimNotifyBegin[15].Bind(std::bind(&APlayerCharacter::Shoot, &LocalPlayer));

		AddState(EnumAsByte(EPlayerAnimState::Idle), State_Idle);
		AddState(EnumAsByte(EPlayerAnimState::Move), State_Move_Ground);
		AddState(EnumAsByte(EPlayerAnimState::Jump), State_Jump);
		AddState(EnumAsByte(EPlayerAnimState::Duck_Start), State_Duck_Start);
		AddState(EnumAsByte(EPlayerAnimState::Duck_Idle), State_Duck_Loop);
		AddState(EnumAsByte(EPlayerAnimState::Shoot), State_Attack_Idle);
		AddState(EnumAsByte(EPlayerAnimState::Move_Shoot), State_Attack_Move);
		AddState(EnumAsByte(EPlayerAnimState::Duck_Shoot), State_Attack_Duck);
		AddState(EnumAsByte(EPlayerAnimState::Dash_Ground), State_Dash_Ground);
		AddState(EnumAsByte(EPlayerAnimState::Dash_Air), State_Dash_Air);
	}

	UPlayerAnimator::~UPlayerAnimator() {}

	void UPlayerAnimator::Initialize()
	{
		UAnimator::Initialize();

		mOwnerMovementComp = static_cast<UPlayerMovementComponent*>(GetOwnerActor()->
			GetComponentByID(L"PlayerMovementComp"));

		auto IsMoving    = [this](){ return !mOwnerMovementComp->GetVelocity().IsNearlyZero(); };
		auto IsJumping   = [this](){ return mOwnerMovementComp->IsJumping(); };
		auto IsCrouching = [this](){ return mOwnerMovementComp->IsCrouching(); };
		auto IsAttacking = [this](){ return LocalPlayer.IsAttacking(); };
		auto IsDashing   = [this](){ return mOwnerMovementComp->IsDashing(); };

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

#pragma region Dash ->
		AddTransition(EnumAsByte(EPlayerAnimState::Idle), EnumAsByte(EPlayerAnimState::Dash_Ground),
					  IsDashing);
		AddTransition(EnumAsByte(EPlayerAnimState::Move), EnumAsByte(EPlayerAnimState::Dash_Ground),
					  IsDashing);
		AddTransition(EnumAsByte(EPlayerAnimState::Dash_Ground), EnumAsByte(EPlayerAnimState::Move),
					  [IsDashing, IsMoving](){ return !IsDashing() && IsMoving(); });
		AddTransition(EnumAsByte(EPlayerAnimState::Dash_Ground), EnumAsByte(EPlayerAnimState::Idle),
					  [IsDashing, IsMoving](){ return !IsDashing() && !IsMoving(); });

		AddTransition(EnumAsByte(EPlayerAnimState::Jump), EnumAsByte(EPlayerAnimState::Dash_Air),
					  IsDashing);

		AddTransition(EnumAsByte(EPlayerAnimState::Dash_Air), EnumAsByte(EPlayerAnimState::Jump),
					  [IsDashing, IsJumping](){ return !IsDashing() && IsJumping(); });
		AddTransition(EnumAsByte(EPlayerAnimState::Dash_Air), EnumAsByte(EPlayerAnimState::Move),
					  [IsDashing, IsJumping, IsMoving](){ return !IsDashing() && !IsJumping() && IsMoving(); });
		AddTransition(EnumAsByte(EPlayerAnimState::Dash_Air), EnumAsByte(EPlayerAnimState::Idle),
					  [IsDashing, IsJumping, IsMoving](){ return !IsDashing() && !IsJumping() && !IsMoving(); });

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
		AddTransition(EnumAsByte(EPlayerAnimState::Duck_Idle), EnumAsByte(EPlayerAnimState::Jump),
					  IsJumping);
		AddTransition(EnumAsByte(EPlayerAnimState::Duck_Idle), EnumAsByte(EPlayerAnimState::Duck_Shoot),
					  IsAttacking);
#pragma endregion

#pragma region Shoot ->
		AddTransition(EnumAsByte(EPlayerAnimState::Shoot), EnumAsByte(EPlayerAnimState::Idle),
					  [IsAttacking](){ return !IsAttacking(); });
		AddTransition(EnumAsByte(EPlayerAnimState::Shoot), EnumAsByte(EPlayerAnimState::Jump),
					  IsJumping);
		AddTransition(EnumAsByte(EPlayerAnimState::Shoot), EnumAsByte(EPlayerAnimState::Move_Shoot),
					  IsMoving);
		AddTransition(EnumAsByte(EPlayerAnimState::Shoot), EnumAsByte(EPlayerAnimState::Duck_Shoot),
					  IsCrouching);

		AddTransition(EnumAsByte(EPlayerAnimState::Move_Shoot), EnumAsByte(EPlayerAnimState::Shoot),
					  [IsMoving](){ return !IsMoving(); });
		AddTransition(EnumAsByte(EPlayerAnimState::Move_Shoot), EnumAsByte(EPlayerAnimState::Move),
					  [IsAttacking](){ return !IsAttacking(); });
		AddTransition(EnumAsByte(EPlayerAnimState::Move_Shoot), EnumAsByte(EPlayerAnimState::Jump),
					  IsJumping);

		AddTransition(EnumAsByte(EPlayerAnimState::Duck_Shoot), EnumAsByte(EPlayerAnimState::Shoot),
					  [IsCrouching](){ return !IsCrouching(); });
		AddTransition(EnumAsByte(EPlayerAnimState::Duck_Shoot), EnumAsByte(EPlayerAnimState::Duck_Idle),
					  [IsAttacking](){ return !IsAttacking(); });
#pragma endregion

		mCurrentState = EnumAsByte(EPlayerAnimState::Idle);
		PlayDefaultTrack(false, true);
	}

	void UPlayerAnimator::Update(float DeltaTime)
	{
		for (auto& obj : mProjectiles)
		{
			obj->Update(DeltaTime);
		}

		UAnimator::Update(DeltaTime);
	}

	void UPlayerAnimator::Render()
	{

		for (auto& obj : mProjectiles)
		{
			obj->Render();
		}
		UAnimator::Render();
	}

	void UPlayerAnimator::Release()
	{
		UAnimator::Release();
	}


}
