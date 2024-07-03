#include "ARibby.h"

#include "Game/AI/Test/RibbyBT.h"
#include "Anim/URibbyAnimator.h"
#include "Component/Animation/UAnimator.h"
#include "Shape/UBoxComponent.h"

namespace LJG
{

	ARibby::ARibby()
		: AEnemy(L"Ribby")
	{
		mCurrentHP = 408.f;
	}

	ARibby::~ARibby()
	{}

	void ARibby::Initialize()
	{
		mAnimator = CreateDefaultSubObject<URibbyAnimator>();
		mAnimator->SetupAttachment(this);
		mAnimator->SetOwnerActor(this);
		mAnimator->Initialize();

		APawn::Initialize();

		mDebugBox->SetScale({320.f, 300.f});

		mBehaviorTree = CreateDefaultSubObject<AI::RibbyBT>(this);
		mBehaviorTree->Initialize();
	}

	void ARibby::Update(float DeltaTime)
	{
		APawn::Update(DeltaTime);
	}

	void ARibby::OnDead()
	{
		AEnemy::OnDead();
	}

	void ARibby::OnHit(float InDamage)
	{
		AEnemy::OnHit(InDamage);

		mCurrentHP -= InDamage;
	}
}
