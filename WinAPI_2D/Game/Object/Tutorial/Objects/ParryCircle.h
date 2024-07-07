#pragma once
#include "FTimer.h"
#include "Component/Actor/Interactable/AInteractObject.h"


namespace LJG
{
	class UImage;

	class ParryCircle : public AInteractObject
	{
	public:
		ParryCircle(const WText& InKey);
		~ParryCircle() override;

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
		bool IsParriable() const { return bCanBeParry; }

	private:
		XTexture* mCircle_Pink;
		XTexture* mCircle_Gray;

		UImage* mParryCircle;
		bool    bCanBeParry = true;

		float_t mElapsedTime = 0.f;
	};
}
