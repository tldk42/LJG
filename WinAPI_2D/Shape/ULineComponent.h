#pragma once
#include "Component/USceneComponent.h"

namespace LJG
{
	class XShape2D_Line;

	class ULineComponent : public USceneComponent
	{
	public:
		explicit ULineComponent(const WText& Inkey);
		~ULineComponent() override = default;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

		void SetScale(const FVector2f& InScale);
		void SetColor(const FLinearColor& InColor) const;

	protected:
		Math::TLine    mLine;
		XShape2D_LineUPtr mLineShape;
	};
}
