#pragma once
#include "Component/Actor/Interactable/AInteractObject.h"

namespace LJG
{
	class UImage;
}
namespace LJG
{
	class ExitDoor : public AInteractObject
	{
	public:
		ExitDoor(const WText& InKey);
		~ExitDoor() override;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

#pragma region Interact Interface
		void OnBeginInteract(struct FHitResult_Box2D& HitResult) override;
		void OnEndInteract(struct FHitResult_Box2D& HitResult) override;
#pragma endregion

		void SetWorldLocation(const FVector2f& InLocation) override;
		void SetScale(const FVector2f& InScale) override;
	public:
		inline bool CanEnter() const { return bCanEnter; }

	private:
		UImage* mDoor;
		bool    bCanEnter;
	};
}
