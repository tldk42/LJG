#pragma once
#include "../UObject.h"

namespace LJG
{
	class UBoxComponent : public UObject

	{
	public:
		UBoxComponent();
		~UBoxComponent() override = default;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

		void SetScale(const FVector2f& InScale) const;
		void SetColor(const FLinearColor& InColor) const;

	protected:
		XDebugShape2DUPtr mDebugShape;
		FBox2f            mBox;
	};
}