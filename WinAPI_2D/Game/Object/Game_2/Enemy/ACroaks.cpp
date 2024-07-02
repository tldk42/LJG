#include "ACroaks.h"

#include "Anim/UCroaksAnimator.h"
#include "Component/Animation/UAnimator.h"
#include "Shape/UBoxComponent.h"

namespace LJG
{

	ACroaks::ACroaks(const WText& InKey)
		: APawn(InKey) {}

	ACroaks::~ACroaks() {}

	void ACroaks::Initialize()
	{
		mAnimator = CreateDefaultSubObject<UCroaksAnimator>();
		mAnimator->SetupAttachment(this);
		mAnimator->SetOwnerActor(this);
		mAnimator->Initialize();

		APawn::Initialize();

		mDebugBox->SetScale({300.f, 400.f});
	}

	void ACroaks::Update(float DeltaTime)
	{
		APawn::Update(DeltaTime);
	}
}
