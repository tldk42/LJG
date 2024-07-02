#include "Background_Tut.h"

#include <ranges>

#include "Camera.h"
#include "Component/UImage.h"
#include "Game/Ground.h"

namespace LJG
{
	Tutorial_Map::Tutorial_Map(const WText& InName)
		: USceneComponent(InName)
	{
		Image_Background = CreateDefaultSubObject<UImage>(L"Background",
														  L"rsc/CupHead/Texture2D/tutorial_room_back_layer_0001.png",
														  0.8f);
		Image_Background->SetScale({1.25, 1.25});
		Image_BackgroundMask = CreateDefaultSubObject<UImage>(
			L"Mask", L"rsc/CupHead/Texture2D/tutorial_room_front_layer_0001.png", 0.1f);
		Image_BackgroundMask->SetScale({1.25, 1.25});

		Ground_Cube = CreateDefaultSubObject<Ground>(L"Cube");
		Ground_Cube->SetTexture(L"Cube", L"rsc/CupHead/Sprite/tutorial_cube.png");
		Ground_Cube->SetBoxSize({200.f, 150.f});
		Ground_Cube->SetWorldLocation({964.4f, -24.3f});

		Ground_InvisibleBox = CreateDefaultSubObject<Ground>(L"Ground_Default");
		Ground_InvisibleBox->SetBoxSize({10000.f, 10.f});
		Ground_InvisibleBox->SetWorldLocation({0, -200.f});
	}

	Tutorial_Map::~Tutorial_Map() {}

	void Tutorial_Map::Update(float DeltaTime)
	{
		USceneComponent::Update(DeltaTime);

		Image_Background->SetPosition(MainCam.GetWorldLocation());
		Image_BackgroundMask->SetPosition(MainCam.GetWorldLocation());
	}

	void Tutorial_Map::Render()
	{
		for (auto& obj : mChildObjects | std::views::values)
		{
			obj->Render();
		}
		
		// Image_Background->Render();
		// Image_BackgroundMask->Render();
		// Ground_InvisibleBox->Render();
		// Ground_Cube->Render();
	}

}
