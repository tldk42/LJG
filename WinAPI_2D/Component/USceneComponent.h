#pragma once
#include "UObject.h"

namespace LJG
{
	class UBoxComponent;
}
namespace LJG
{
	/** Scene에 뿌려질 수 있는 오브젝트 */
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
		[[nodiscard]] FVector2f GetWorldLocation() const;
		[[nodiscard]] FVector2f GetRelativeLocation() const;
		[[nodiscard]] float     GetWorldRotation() const;
		[[nodiscard]] float     GetRelativeRotation() const;
		[[nodiscard]] FVector2f GetScale() const;
#pragma endregion

#pragma region Set
		void SetWorldLocation(const FVector2f& InLocation);
		void SetRelativeLocation(const FVector2f& InLocation);
		void SetWorldRotation(const float InDegree);
		void SetRelativeRotation(const float InDegree);
		void SetScale(const FVector2f& InScale);
#pragma endregion

	public:
		VoidDelegate OnClick_Delegate; // Editor에서 클릭시


	protected:
		std::unordered_map<WText, USceneComponent*> mChild;

	protected:
		Matrix mLocalTransform;
		Matrix mWorldTransform;


	};
}
