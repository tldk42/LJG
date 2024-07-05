#include "UFireflyAnimator.h"

#include "Component/Actor/AActor.h"
#include "Component/Animation/USpriteAnimation.h"
#include "Component/Movement/UPawnMovementComponent2D.h"
#include "data/MonsterData.h"
#include "Game/Object/Game_2/Enemy/Movement/UFlyingMovementComponent.h"
#include "Helper/EngineHelper.h"

namespace LJG
{

	UFireflyAnimator::UFireflyAnimator()
	{
		State_Idle = CreateSprite(L"firefly_idle");
		State_Down = CreateSprite(L"firefly_down");
		State_Up   = CreateSprite(L"firefly_up");
		State_Left = CreateSprite(L"firefly_left");
		State_Dead = CreateSprite(L"firefly_dead");

		AddState(EnumAsByte(EFireflyState::Idle), State_Idle);
		AddState(EnumAsByte(EFireflyState::Down), State_Down);
		AddState(EnumAsByte(EFireflyState::Up), State_Up);
		AddState(EnumAsByte(EFireflyState::Left), State_Left);
		AddState(EnumAsByte(EFireflyState::Dead), State_Dead);

		State_Dead->OnAnimFinished.Bind([&](){
			mOwnerActor->SetActive(false);
		});
	}

	UFireflyAnimator::~UFireflyAnimator() {}

	void UFireflyAnimator::Initialize()
	{
		UAnimator::Initialize();

		mOwnerMovementComp = static_cast<UFlyingMovementComponent*>(GetOwnerActor()->
			GetComponentByID(L"FlyingMovementComponent"));

		// Order
		// 1. Left
		// 2. Down
		// 3. Up
		auto IsIdle = [this]{ return mOwnerMovementComp->GetVelocity().IsNearlyZero(); };
		auto IsLeft = [this]{ return mOwnerMovementComp->GetVelocity().X > 0.f; };
		auto IsDown = [this]{ return mOwnerMovementComp->GetVelocity().Y < 0.f; };
		auto IsUp   = [this]{ return mOwnerMovementComp->GetVelocity().Y > 0.f; };


		// Idle -> Move
		AddTransition(EnumAsByte(EFireflyState::Idle), EnumAsByte(EFireflyState::Left),
					  IsLeft);
		AddTransition(EnumAsByte(EFireflyState::Idle), EnumAsByte(EFireflyState::Down),
					  IsDown);
		AddTransition(EnumAsByte(EFireflyState::Idle), EnumAsByte(EFireflyState::Up),
					  IsUp);

		// Moving -> Idle
		AddTransition(EnumAsByte(EFireflyState::Left), EnumAsByte(EFireflyState::Idle),
					  IsIdle);
		AddTransition(EnumAsByte(EFireflyState::Down), EnumAsByte(EFireflyState::Idle),
					  IsIdle);
		AddTransition(EnumAsByte(EFireflyState::Up), EnumAsByte(EFireflyState::Idle),
					  IsIdle);

		PlayDefaultTrack(false, true);
	}

	void UFireflyAnimator::Update(float DeltaTime)
	{
		UAnimator::Update(DeltaTime);
	}

	void UFireflyAnimator::Render()
	{
		UAnimator::Render();
	}

	void UFireflyAnimator::Release()
	{
		UAnimator::Release();
	}
}
