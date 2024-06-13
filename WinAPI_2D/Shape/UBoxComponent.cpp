#include "UBoxComponent.h"
#include "../AActor.h"
#include "../Shape/XDebugShape2D.h"

namespace LJG
{
	UBoxComponent::UBoxComponent()
	{
		UBoxComponent::Initialize();
	}

	void UBoxComponent::Initialize()
	{
		mDebugShape = std::make_unique<XDebugShape2D>();
		mDebugShape->Initialize();
	}

	void UBoxComponent::Update(float DeltaTime)
	{
		mDebugShape->Update(DeltaTime);
		mDebugShape->SetWorldTransform(
			mOwnerActor->GetActorLocation(),
			mOwnerActor->GetActorRotation(),
			FVector2f::UnitVector);
	}

	void UBoxComponent::Render()
	{
		mDebugShape->Render();
	}

	void UBoxComponent::Release()
	{
		mDebugShape->Release();
	}

	void UBoxComponent::SetScale(const FVector2f& InScale) const
	{
		mDebugShape->SetScale(InScale);
	}

	void UBoxComponent::SetColor(const FLinearColor& InColor) const
	{
		mDebugShape->SetColor(InColor);
	}
}
