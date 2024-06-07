#pragma once
#include "CommonInclude.h"

namespace LJG
{
	class UTextBlock
	{
	public:
		explicit UTextBlock(const std::wstring& InText);
		~UTextBlock() = default;

	public:
		FORCEINLINE void SetLocation(const RECT& InRect) const { mText->RectSize = InRect; }
		FORCEINLINE void SetText(const std::wstring& InText) const { mText->Text = InText; }

		[[nodiscard]] FORCEINLINE const RECT&         GetLocation() const { return mText->RectSize; }
		[[nodiscard]] FORCEINLINE const std::wstring& GetText() const { return mText->Text; }

	private:
		FWriteDataUPtr mText;
	};

}
