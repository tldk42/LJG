#pragma once
#include "UObject.h"

namespace LJG
{
	class UTextBlock : public UObject
	{
	public:
		explicit UTextBlock(WTextView InText);
		~UTextBlock() override = default;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion


		inline void SetLocation(const FVector2f& InRect) { mPosition = InRect; }
		inline void SetText(WTextView InText) { mText = WText(InText); }

		[[nodiscard]] inline const FVector2f& GetLocation() const { return mPosition; }
		[[nodiscard]] inline WTextView        GetText() const { return mText; }

	private:
		FVector2f mPosition;
		FVector2f mScale;
		WText     mText;
	};

}
