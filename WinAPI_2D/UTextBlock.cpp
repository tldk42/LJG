#include "UTextBlock.h"

#include "DXWrite.h"

namespace LJG
{
	UTextBlock::UTextBlock(WTextView InText)
		: mText(InText)
	{}

	void UTextBlock::Initialize()
	{
		UObject::Initialize();
	}

	void UTextBlock::Update(float DeltaTime)
	{
		UObject::Update(DeltaTime);
	}

	void UTextBlock::Render()
	{
		DXWrite::Get()->Draw(mPosition, mText);
	}

	void UTextBlock::Release()
	{
		UObject::Release();
	}

}
