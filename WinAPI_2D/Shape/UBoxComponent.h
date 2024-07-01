#pragma once
#include "Component/USceneComponent.h"

namespace LJG
{
	class UBoxComponent : public USceneComponent
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
		ETraceType GetTraceType() const { return Type; }

		void SetWorldLocation(const FVector2f& InLocation) override;
		void SetScale(const FVector2f& InScale) override;
		void SetColor(const FLinearColor& InColor) const;

		bool IsInArea(const FVector2f& InPos) const;

	protected:
		XShape2D_BoxUPtr mDebugShape;
		FBox2f           mBox;
		ETraceType       Type;
	};
}
