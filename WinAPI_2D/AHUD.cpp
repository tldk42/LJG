#include "AHUD.h"

#include "Component/UImage.h"
#include "Component/UTextBlock.h"

namespace LJG
{

	AHUD::AHUD(const WText& InKey)
		: AActor(InKey)
	{
		AHUD::Initialize();
	}

	void AHUD::Initialize()
	{
		AActor::Initialize();

		mFpsText = CreateDefaultSubObject<UTextBlock>(L"FpsTextBlock", L"");
		mFpsText->SetupAttachment(this);
		mFpsText->SetOwnerActor(this);;

		mBackgroundImage = CreateDefaultSubObject<UImage>(L"0", L"rsc/BG/lv_2-1_sky-loop.png", 0.8f);
		mBackgroundImage->SetupAttachment(this);
		mBackgroundImage->SetOwnerActor(this);
		mBackgroundImage->Initialize();
		mBackgroundImage->SetPosition({0, 0.f});


		mSampleImage = CreateDefaultSubObject<UImage>(L"2", L"rsc/BG/lv2-1_bg_close-hills-loop.png", 0.5f);
		mSampleImage->SetupAttachment(this);
		mSampleImage->SetOwnerActor(this);
		mSampleImage->Initialize();
		mSampleImage->SetPosition({0, 0.f});

		mSampleImage2 = CreateDefaultSubObject<UImage>(L"7", L"rsc/BG/lv2-1_bg_outside_A.png", 0.3f);
		mSampleImage2->SetupAttachment(this);
		mSampleImage2->SetOwnerActor(this);
		mSampleImage2->Initialize();
		mSampleImage2->SetPosition({512, 0.f});
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
