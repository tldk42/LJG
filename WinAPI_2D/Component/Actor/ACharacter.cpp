#include "ACharacter.h"

#include "Camera.h"
#include "Component/UPawnMovementComponent2D.h"
#include "DirectX/Context.h"

namespace LJG
{

	ACharacter::ACharacter(const WText& InKey)
		: APawn(InKey)
	{
		ACharacter::Initialize();
	}

	ACharacter::~ACharacter() {}

	void ACharacter::Initialize()
	{
		mCamera = CreateDefaultSubObject<ACamera>(L"Camera");
		mCamera->SetOwnerActor(this);
		mCamera->SetProjection(Context::GetViewportSize().X, Context::GetViewportSize().Y);
	}

	void ACharacter::Update(float DeltaTime)
	{
		APawn::Update(DeltaTime);

		if (!mMovementComponent->GetVelocity().IsNearlyZero())
		{
			mCamera->SetPosition(FMath::Lerp(mCamera->GetWorldLocation(), GetWorldLocation(), 5.f * DeltaTime));
		}
	}
}
