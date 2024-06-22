#include "UTextBlock.h"

#include "DirectX/DXWrite.h"

namespace LJG
{
	UTextBlock::UTextBlock(const WText& InKey, WTextView InText)
		: UObject(InKey),
		  mText(InText)
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
