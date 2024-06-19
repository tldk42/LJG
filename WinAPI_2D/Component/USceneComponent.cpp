#include "USceneComponent.h"

#include "InputManager.h"
#include "Shape/UBoxComponent.h"

namespace LJG
{
	USceneComponent::USceneComponent()
		: mLocalTransform(XMMatrixIdentity()),
		  mWorldTransform(XMMatrixIdentity())
	{
		USceneComponent::Initialize();
	}

	USceneComponent::~USceneComponent() = default;

	void USceneComponent::Initialize()
	{
		UObject::Initialize();
	}

	void USceneComponent::Update(float DeltaTime)
	{
		UObject::Update(DeltaTime);

		for (const auto& sceneComponent : mChildComponents)
		{
			sceneComponent.second->SetTransform(mWorldTransform);
		}
	}

	void USceneComponent::Render()
	{
		UObject::Render();
	}

	void USceneComponent::Release()
	{
		UObject::Release();
	}

	Matrix USceneComponent::GetWorldTransform() const
	{
		return mWorldTransform;
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

	void USceneComponent::AddWorldLocation(const FVector2f& InAddLocation)
	{
		const auto cache     = Mat2LocVector2(mWorldTransform);
		mWorldTransform.r[3] = XMVectorSet(cache.X + InAddLocation.X, cache.Y + InAddLocation.Y, 0.f, 1.f);
	}

	void USceneComponent::SetWorldRotation(const float InDegree)
	{
		const XMMATRIX newRotationMatrix = RotationMatrix(InDegree);

		const XMVECTOR cachedScale = XMVectorSet(XMVectorGetX(mWorldTransform.r[0]),
												 XMVectorGetY(mWorldTransform.r[1]),
												 XMVectorGetZ(mWorldTransform.r[2]), 0.0f);
		const XMVECTOR cachedTranslation = mWorldTransform.r[3];

		mWorldTransform      = XMMatrixScalingFromVector(cachedScale) * newRotationMatrix;
		mWorldTransform.r[3] = cachedTranslation;
	}

	void USceneComponent::SetRelativeRotation(const float InDegree)
	{
		const XMMATRIX newRotationMatrix = RotationMatrix(InDegree);

		const XMVECTOR cachedScale = XMVectorSet(XMVectorGetX(mLocalTransform.r[0]),
												 XMVectorGetY(mLocalTransform.r[1]),
												 XMVectorGetZ(mLocalTransform.r[2]), 0.0f);
		const XMVECTOR cachedTranslation = mLocalTransform.r[3];

		mLocalTransform      = XMMatrixScalingFromVector(cachedScale) * newRotationMatrix;
		mLocalTransform.r[3] = cachedTranslation;
	}

	void USceneComponent::SetScale(const FVector2f& InScale)
	{
		XMVECTOR scale, rotation, translation;
		XMMatrixDecompose(&scale, &rotation, &translation, mLocalTransform);

		const XMMATRIX newScaleMatrix = XMMatrixScaling(InScale.X, InScale.Y, 1.0f);

		XMMATRIX rotationMatrix = XMMatrixRotationQuaternion(rotation);
		mLocalTransform         = newScaleMatrix * rotationMatrix;

		mLocalTransform.r[3] = translation;

		XMMatrixDecompose(&scale, &rotation, &translation, mWorldTransform);
		rotationMatrix       = XMMatrixRotationQuaternion(rotation);
		mWorldTransform      = newScaleMatrix * rotationMatrix;
		mWorldTransform.r[3] = translation;
	}

	void USceneComponent::SetTransform(const Matrix& InMatrix)
	{
		mWorldTransform = InMatrix;
	}

	void USceneComponent::SetTransform(const FVector2f& InLocation, const float_t InRotation, const FVector2f& InScale)
	{
		const XMMATRIX translation = TranslationMatrix(InLocation.X, InLocation.Y);
		const XMMATRIX rotation    = RotationMatrix(InRotation);
		const XMMATRIX scale       = ScaleMatrix(InScale.X, InScale.Y);

		const XMMATRIX transform = scale * rotation * translation;

		mWorldTransform = transform;
	}
}
