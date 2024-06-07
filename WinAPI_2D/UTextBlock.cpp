#include "UTextBlock.h"

namespace LJG
{
	UTextBlock::UTextBlock(const std::wstring& InText)
	{
		mText.reset(new FWriteData({}, InText));
	}

}
