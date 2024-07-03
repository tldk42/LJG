#pragma once
#include "CollisionManager.h"
#include "Component/USceneComponent.h"

namespace LJG
{
	DECLARE_DYNAMIC_DELEGATE(FOnCollisionEnter, FHitResult_Box2D&)

	DECLARE_DYNAMIC_DELEGATE(FOnCollisionStay, FHitResult_Box2D&)

	DECLARE_DYNAMIC_DELEGATE(FOnCollisionExit, FHitResult_Box2D&)

	class UBoxComponent : public USceneComponent, public ICollisionAPI
	{
	public:
		explicit UBoxComponent(const WText& Inkey, const ETraceType InTraceType);
		~UBoxComponent() override;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

		FBox2f     GetBox() const { return mBox; }
		ETraceType GetTraceType() override { return Type; }
		uint32_t   GetCollisionID() override { return mcollisionID; }
		void       OnCollisionEnter(FHitResult_Box2D& HitResult) override;
		void       OnCollision(FHitResult_Box2D& HitResult) override;
		void       OnCollisionExit(FHitResult_Box2D& HitResult) override;

		void SetWorldLocation(const FVector2f& InLocation) override;
		void SetScale(const FVector2f& InScale) override;
		void SetColor(const FLinearColor& InColor) const;

		bool IsInArea(const FVector2f& InPos) const;

	public:
		FOnCollisionEnter OnCollisionEnter_Delegate;
		FOnCollisionStay  OnCollisionStay_Delegate;
		FOnCollisionExit  OnCollisionExit_Delegate;

	protected:
		XShape2D_BoxUPtr mDebugShape;
		FBox2f           mBox;
		ETraceType       Type;
		uint32_t         mcollisionID;

	private:
		static uint32_t s_CollisionID;
	};
}
