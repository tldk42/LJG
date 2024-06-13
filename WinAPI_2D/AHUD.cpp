#include "AHUD.h"

#include "UImage.h"
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
		mFpsText->SetupAttachment(this);
		mFpsText->SetOwnerActor(this);

		mBackgroundImage = CreateDefaultSubObject<UImage>(L"BackgroundImage", L"rsc/ND/Background/GroundStone.png");
		mBackgroundImage->SetupAttachment(this);
		mBackgroundImage->SetOwnerActor(this);
		mBackgroundImage->Initialize();
		mBackgroundImage->SetPosition({0, -256.f});
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

	void AHUD::UpdateFpsText(WTextView InText) const
	{
		mFpsText->SetText(InText);
	}
}
