#include "AHUD.h"

#include "UTextBlock.h"

namespace LJG
{

	AHUD::AHUD()
	{
		AHUD::Initialize();
	}

	void AHUD::Initialize()
	{
		AActor::Initialize();

		mFpsText = CreateDefaultSubObject<UTextBlock>(L"FpsTextBlock", L"");
	}

	void AHUD::Update(float DeltaTime)
	{
		AActor::Update(DeltaTime);
	}

	void AHUD::Render()
	{
		AActor::Render();
	}

	void AHUD::Release()
	{
		AActor::Release();
	}

	void AHUD::UpdateFpsText(WTextView InText)
	{
		mFpsText->SetText(InText);
	}
}
