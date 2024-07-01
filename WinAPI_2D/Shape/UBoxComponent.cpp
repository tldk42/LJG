#include "UBoxComponent.h"

#include "Tracer.h"
#include "Component/Actor/AActor.h"
#include "../Shape/XShape2D_Box.h"

namespace LJG
{
	UBoxComponent::UBoxComponent(const WText& Inkey, const ETraceType InTraceType)
		: USceneComponent(Inkey),
		  Type(InTraceType)
	{
		BoxTypes.AddComponent(this);
		UBoxComponent::Initialize();
	}

	UBoxComponent::~UBoxComponent()
	{
		BoxTypes.RemoveComponent(this);
	}

	void UBoxComponent::Initialize()
	{
		mDebugShape = std::make_unique<XShape2D_Box>();
		mDebugShape->Initialize();

		mBox.Min = mDebugShape->GetLocation() - mDebugShape->GetScale() / 2.f;
		mBox.Max = mDebugShape->GetLocation() + mDebugShape->GetScale() / 2.f;
	}

	void UBoxComponent::Update(float DeltaTime)
	{
		mDebugShape->Update(DeltaTime);

		if (mOwnerActor)
		{
			SetWorldLocation(mOwnerActor->GetWorldLocation());
		}
	}

	void UBoxComponent::Render()
	{
		mDebugShape->Render();
	}

	void UBoxComponent::Release()
	{
		mDebugShape->Release();
	}

	void UBoxComponent::SetWorldLocation(const FVector2f& InLocation)
	{
		USceneComponent::SetWorldLocation(InLocation);

		mDebugShape->SetWorldLocation(GetWorldLocation());

		mBox.Min = GetWorldLocation() - mDebugShape->GetScale() / 2.f;
		mBox.Max = GetWorldLocation() + mDebugShape->GetScale() / 2.f;
	}

	void UBoxComponent::SetScale(const FVector2f& InScale)
	{
		USceneComponent::SetScale(InScale);
		
		mDebugShape->SetScale(InScale);

		mBox.Min = GetWorldLocation() - mDebugShape->GetScale() / 2.f;
		mBox.Max = GetWorldLocation() + mDebugShape->GetScale() / 2.f;
	}

	void UBoxComponent::SetColor(const FLinearColor& InColor) const
	{
		mDebugShape->SetColor(InColor);
	}

	bool UBoxComponent::IsInArea(const FVector2f& InPos) const
	{
		return (InPos >= mBox.Min && InPos <= mBox.Max);
	}
}
