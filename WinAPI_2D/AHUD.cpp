#include "AHUD.h"

#include "Component/UImage.h"
#include "Component/UTextBlock.h"
#include "Helper/EngineHelper.h"

namespace LJG
{

	AHUD::AHUD()
		: AActor(L"HUD")
	{
		AHUD::Initialize();
	}

	void AHUD::Initialize()
	{
		AActor::Initialize();

		mFpsText = CreateDefaultSubObject<UTextBlock>(L"FpsTextBlock", L"");
		mFpsText->SetupAttachment(this);
		mFpsText->SetOwnerActor(this);;

	}

	void AHUD::Update(float DeltaTime)
	{
		AActor::Update(DeltaTime);

		mFpsText->SetText(std::format(L"FPS: {:d}", GetFramePerSeconds()));
	}

	void AHUD::Render()
	{
		AActor::Render();
	}

	void AHUD::Release()
	{
		AActor::Release();
	}
}
