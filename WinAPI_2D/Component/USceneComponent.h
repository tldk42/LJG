#pragma once
#include "UObject.h"

namespace LJG
{
	class UBoxComponent;
}

namespace LJG
{
	/** Scene�� �ѷ��� �� �ִ� ������Ʈ */
	class USceneComponent : public UObject
	{
	public:
		USceneComponent();
		~USceneComponent() override;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

	public:
#pragma region Get
		[[nodiscard]] Matrix    GetWorldTransform() const;
		[[nodiscard]] FVector2f GetWorldLocation() const;
		[[nodiscard]] FVector2f GetRelativeLocation() const;
		[[nodiscard]] float     GetWorldRotation() const;
		[[nodiscard]] float     GetRelativeRotation() const;
		[[nodiscard]] FVector2f GetScale() const;
#pragma endregion

#pragma region Set
		void SetWorldLocation(const FVector2f& InLocation);
		void SetRelativeLocation(const FVector2f& InLocation);
		void AddWorldLocation(const FVector2f& InAddLocation);
		void SetWorldRotation(const float InDegree);
		void SetRelativeRotation(const float InDegree);
		void SetScale(const FVector2f& InScale);
		void SetTransform(const Matrix& InMatrix);
		void SetTransform(const FVector2f& InLocation, const float_t InRotation, const FVector2f& InScale);
#pragma endregion

	public:
		VoidDelegate OnClick_Delegate; // Editor���� Ŭ����


	protected:
		std::unordered_map<WText, USceneComponent*> mChildComponents;

	protected:
		bool bVisibility;

		Matrix mLocalTransform;
		Matrix mWorldTransform;
	};
}