#pragma once
#include "Component/USceneComponent.h"

namespace LJG
{
	class XShape2D_Line;

	class FHitResult;
	DECLARE_DYNAMIC_DELEGATE(FOnComponentBeginOverlap, const FVector2f, const FVector2f, FHitResult&)

	DECLARE_DYNAMIC_DELEGATE(FOnComponentEndOverlap)

	class ULineComponent : public USceneComponent
	{
	public:
		explicit ULineComponent(const WText& Inkey);
		~ULineComponent() override;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

		void SetScale(const FVector2f& InScale) override;
		void SetColor(const FLinearColor& InColor) const;

	public:
		FOnComponentBeginOverlap OnComponentBeginOverlap;
		FOnComponentEndOverlap   OnComponentEndOverlap;
		Math::TLine       mLine;

	protected:
		XShape2D_LineUPtr mLineShape;
	};
}
