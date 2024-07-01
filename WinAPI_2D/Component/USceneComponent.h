#pragma once
#include "UObject.h"


namespace LJG
{
	class UBoxComponent;

	/** Scene에 뿌려질 수 있는 오브젝트 */
	class USceneComponent : public UObject
	{
	public:
		explicit USceneComponent(const WText& InKey);
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
		virtual void SetWorldLocation(const FVector2f& InLocation);
		virtual void AddWorldLocation(const FVector2f& InAddLocation);
		virtual void SetWorldRotation(const float InDegree);
		virtual void SetScale(const FVector2f& InScale);
		virtual void SetTransform(const Matrix& InMatrix);
		virtual void SetTransform(const FVector2f& InLocation, const float_t InRotation, const FVector2f& InScale);

		void SetRelativeLocation(const FVector2f& InLocation);
		void SetRelativeRotation(const float InDegree);

#pragma endregion

	public:

	protected:
		std::unordered_map<WText, USceneComponent*> mChildComponents;

	protected:
		bool bVisibility;

		Matrix mLocalTransform;
		Matrix mWorldTransform;
	};
}
