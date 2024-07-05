#include "UBoxComponent.h"

#include "CollisionManager.h"
#include "Component/Actor/AActor.h"
#include "../Shape/XShape2D_Box.h"

namespace LJG
{
	uint32_t UBoxComponent::s_CollisionID = 0;

	UBoxComponent::UBoxComponent(const WText& Inkey, const ETraceType InTraceType)
		: USceneComponent(Inkey),
		  Type(InTraceType),
		  mcollisionID(s_CollisionID++)
	{
		Manager_Collision.EnrollLayer(this);
		UBoxComponent::Initialize();
	}

	UBoxComponent::~UBoxComponent()
	{
		Manager_Collision.ReleaseLayer(this);
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

	void UBoxComponent::OnCollisionEnter(FHitResult_Box2D& HitResult)
	{
		OnCollisionEnter_Delegate.Execute(HitResult);
	}

	void UBoxComponent::OnCollision(FHitResult_Box2D& HitResult)
	{
		OnCollisionStay_Delegate.Execute(HitResult);
	}

	void UBoxComponent::OnCollisionExit(FHitResult_Box2D& HitResult)
	{
		OnCollisionExit_Delegate.Execute(HitResult);
	}

	void UBoxComponent::SetWorldLocation(const FVector2f& InLocation)
	{
		USceneComponent::SetWorldLocation(InLocation);

		mDebugShape->SetWorldLocation(GetWorldLocation());

		mBox.Min = GetWorldLocation() - mDebugShape->GetScale() / 2.f;
		mBox.Max = GetWorldLocation() + mDebugShape->GetScale() / 2.f;
	}

	void UBoxComponent::SetWorldRotation(const float InDegree)
	{
		USceneComponent::SetWorldRotation(InDegree);

		mDebugShape->SetWorldRotation(InDegree);
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
