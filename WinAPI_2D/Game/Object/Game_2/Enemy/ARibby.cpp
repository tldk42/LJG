#include "ARibby.h"

#include "Anim/URibbyAnimator.h"
#include "Component/Animation/UAnimator.h"
#include "Shape/UBoxComponent.h"

namespace LJG
{

	ARibby::ARibby(const WText& InName)
		: APawn(InName) {}

	ARibby::~ARibby() {}

	void ARibby::Initialize()
	{
		mAnimator = CreateDefaultSubObject<URibbyAnimator>();
		mAnimator->SetupAttachment(this);
		mAnimator->SetOwnerActor(this);
		mAnimator->Initialize();

		APawn::Initialize();

		mDebugBox->SetScale({300.f, 400.f});
	}

	void ARibby::Update(float DeltaTime)
	{
		APawn::Update(DeltaTime);
	}
}
