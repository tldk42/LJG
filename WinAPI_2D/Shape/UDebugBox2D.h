#pragma once
#include "../UObject.h"

namespace LJG
{
	class UDebugBox2D : public UObject

	{
	public:
		UDebugBox2D();
		~UDebugBox2D() override = default;

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
	};
}
