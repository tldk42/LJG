#include "USceneComponent.h"

#include "InputManager.h"
#include "Shape/UBoxComponent.h"

namespace LJG
{

	USceneComponent::USceneComponent()
		: mLocalTransform(XMMatrixIdentity()),
		  mWorldTransform(XMMatrixIdentity())
	{
		Initialize();
	}

	USceneComponent::~USceneComponent() = default;
		
	void USceneComponent::Initialize()
	{
		UObject::Initialize();

	}

	void USceneComponent::Update(float DeltaTime)
	{
		UObject::Update(DeltaTime);
		
	}

	void USceneComponent::Render()
	{
		UObject::Render();
	}

	void USceneComponent::Release()
	{
		UObject::Release();
	}

	FVector2f USceneComponent::GetWorldLocation() const
	{
		return Mat2LocVector2(mWorldTransform);
	}

	FVector2f USceneComponent::GetRelativeLocation() const
	{
		return Mat2LocVector2(mLocalTransform);
	}

	float USceneComponent::GetWorldRotation() const
	{
		return Mat2RotDegree(mWorldTransform);
	}

	float USceneComponent::GetRelativeRotation() const
	{
		return Mat2RotDegree(mLocalTransform);
	}

	FVector2f USceneComponent::GetScale() const
	{
		return Mat2ScaleVector2(mWorldTransform);
	}

	void USceneComponent::SetWorldLocation(const FVector2f& InLocation)
	{
		mWorldTransform.r[3] = XMVectorSet(InLocation.X, InLocation.Y, 0.f, 1.f);
	}

	void USceneComponent::SetRelativeLocation(const FVector2f& InLocation)
	{
		mLocalTransform.r[3] = XMVectorSet(InLocation.X, InLocation.Y, 0.f, 1.f);
	}

	void USceneComponent::SetWorldRotation(const float InDegree)
	{
		mWorldTransform = RotationMatrix(InDegree) * mWorldTransform;
	}

	void USceneComponent::SetRelativeRotation(const float InDegree)
	{
		mLocalTransform = RotationMatrix(InDegree) * mLocalTransform;
	}

	void USceneComponent::SetScale(const FVector2f& InScale)
	{
		mLocalTransform = ScaleMatrix(InScale.X, InScale.Y) * mLocalTransform;
		mWorldTransform = ScaleMatrix(InScale.X, InScale.Y) * mWorldTransform;
	}
}
