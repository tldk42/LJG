#include "Background_Game2.h"

#include <ranges>

#include "Component/UImage.h"
#include "Game/Ground.h"

namespace LJG
{

	Background_Game2::Background_Game2(const WText& InName)
		: USceneComponent(InName)
	{
		// Image_JazzbarStage = CreateDefaultSubObject<UImage>(L"Image_JazzbarStage",
		// 													L"rsc/CupHead/Sprite/Game_1/Map/jazzbar(D)_stage.png",
		// 													0.7f);
		//
		// Image_JazzbarMid = CreateDefaultSubObject<UImage>(L"Image_JazzbarMid",
		// 												  L"rsc/CupHead/Sprite/Game_1/Map/jazzbar(C)_mid.png",
		// 												  0.6f);
		// Image_JazzbarBooth = CreateDefaultSubObject<UImage>(L"Image_JazzbarBooth",
		// 													L"rsc/CupHead/Sprite/Game_1/Map/jazzbar(E)_booths.png",
		// 													0.8);
		// Image_JazzbarTables = CreateDefaultSubObject<UImage>(L"Image_JazzbarTables",
		// 													 L"rsc/CupHead/Sprite/Game_1/Map/jazzbar(B)_tables.png",
		// 													 0.09);
		// Image_JazzbarPlants = CreateDefaultSubObject<UImage>(L"Image_JazzbarPlants",
		// 													 L"rsc/CupHead/Sprite/Game_1/Map/jazzbar(A)_plants.png",
		// 													 0.08);

		Ground_InvisibleBox = CreateDefaultSubObject<Ground>(L"Ground_Default");
		Ground_InvisibleBox->SetBoxSize({1560.f, 10.f});
		Ground_InvisibleBox->SetWorldLocation({0, -350.f});


		// Image_JazzbarStage->SetScale({1.5f, 1.5f});
		// Image_JazzbarMid->SetScale({1.5f, 1.5f});
		// Image_JazzbarBooth->SetScale({1.5f, 1.5f});
		// Image_JazzbarTables->SetScale({1.5f, 1.5f});
		// Image_JazzbarPlants->SetScale({1.5f, 1.5f});
		//
		// Image_JazzbarMid->SetPosition(FVector2f(0.f, -66.2f) * 1.5f);
		// Image_JazzbarPlants->SetPosition(FVector2f(-21.1f, -294.8f) * 1.5f);
		// Image_JazzbarTables->SetPosition(FVector2f(10.7f, -271.2f) * 1.5f);
	}

	Background_Game2::~Background_Game2() {}

	void Background_Game2::Update(float DeltaTime)
	{
		USceneComponent::Update(DeltaTime);
	}

	void Background_Game2::Render()
	{
		USceneComponent::Render();
	}
}
