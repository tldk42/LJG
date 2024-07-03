#include "ACroaks.h"

#include "Anim/UCroaksAnimator.h"
#include "Component/Animation/UAnimator.h"
#include "Shape/UBoxComponent.h"

namespace LJG
{

	ACroaks::ACroaks()
		: AEnemy(L"Croaks") {}

	ACroaks::~ACroaks() {}

	void ACroaks::Initialize()
	{
		mAnimator = CreateDefaultSubObject<UCroaksAnimator>();
		mAnimator->SetupAttachment(this);
		mAnimator->SetOwnerActor(this);
		mAnimator->Initialize();

		APawn::Initialize();

		mDebugBox->SetScale({440.f, 550.f});
	}

	void ACroaks::Update(float DeltaTime)
	{
		APawn::Update(DeltaTime);
	}

	void ACroaks::OnDead()
	{
		AEnemy::OnDead();
	}

	void ACroaks::OnHit(float InDamage)
	{
		AEnemy::OnHit(InDamage);
	}
}
