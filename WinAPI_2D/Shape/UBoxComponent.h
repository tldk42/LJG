#pragma once
#include "Component/UObject.h"

namespace LJG
{
	class UBoxComponent : public UObject
	{
	public:
		explicit  UBoxComponent(const WText& Inkey);
		~UBoxComponent() override = default;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

		void SetScale(const FVector2f& InScale);
		void SetColor(const FLinearColor& InColor) const;

		bool IsInArea(const FVector2f& InPos) const;

	protected:
		XDebugShape2DUPtr mDebugShape;
		FBox2f            mBox;
	};
}
