#include "Background_Tut.h"

#include <ranges>

#include "Camera.h"
#include "Component/UImage.h"
#include "Component/Actor/AAnimatedImage.h"
#include "Component/Actor/APlayerCharacter.h"
#include "Component/Animation/USpriteAnimation.h"
#include "Component/Movement/UPawnMovementComponent2D.h"
#include "Game/Ground.h"
#include "Objects/ExitDoor.h"
#include "Objects/ParryCircle.h"

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
			L"Mask", L"rsc/CupHead/Texture2D/tutorial_room_front_layer_0001.png", 0.2f);
		Image_BackgroundMask->SetScale({1.25, 1.25});

		Ground_Cube = CreateDefaultSubObject<Ground>(L"Cube");
		Ground_Cube->SetTexture(L"Cube", L"rsc/CupHead/Sprite/tutorial_cube.png");
		Ground_Cube->SetScale({0.8f, 0.8f});
		Ground_Cube->SetBoxSize({180.f, 140.f});
		Ground_Cube->SetWorldLocation({1000.f, -280.f});

		Ground_Cube2 = CreateDefaultSubObject<Ground>(L"Cube2");
		Ground_Cube2->SetTexture(L"Cube2", L"rsc/CupHead/Sprite/tutorial_plynth_after_pyramid_is_destroyed.png");
		Ground_Cube2->SetScale({0.8f, 0.8f});
		Ground_Cube2->SetBoxSize({180.f, 180.f});
		Ground_Cube2->SetWorldLocation({3469.f, -260.f});

		Ground_Cube3 = CreateDefaultSubObject<Ground>(L"Cube3");
		Ground_Cube3->SetTexture(L"Cube3", L"rsc/CupHead/Sprite/tutorial_cube.png");
		Ground_Cube3->SetScale({0.8f, 0.8f});
		Ground_Cube3->SetBoxSize({180.f, 140.f});
		Ground_Cube3->SetWorldLocation({5480.f, -280.f});

		Ground_Cylinder = CreateDefaultSubObject<Ground>(L"Cylinder");
		Ground_Cylinder->SetTexture(L"Cylinder", L"rsc/CupHead/Sprite/tutorial_cylinder_1.png");
		Ground_Cylinder->SetScale({0.8f, 0.8f});
		Ground_Cylinder->SetBoxSize({180.f, 220.f});
		Ground_Cylinder->SetWorldLocation({4563.f, -240.f});

		Ground_Platform = CreateDefaultSubObject<Ground>(L"Platform");
		Ground_Platform->SetTexture(L"Platform", L"rsc/CupHead/Sprite/tutorial_cylinder_and_platform.png");
		Ground_Platform->SetScale({0.56f, 0.56f});
		Ground_Platform->SetBoxSize({700.f, 10.f});
		Ground_Platform->SetWorldLocation({1806.f, 0.f});

		Ground_InvisibleBox = CreateDefaultSubObject<Ground>(L"Ground_Default");
		Ground_InvisibleBox->SetBoxSize({100000.f, 30.f});
		Ground_InvisibleBox->SetWorldLocation({0, -350.f});

		USpriteAnimation* fxAnim = CreateSprite(L"cuphead_screen_fx");
		fxAnim->SetSpeed(0.1f);
		BackgroundFX = CreateDefaultSubObject<AAnimatedImage>(L"BackgroundFX");
		BackgroundFX->SetAnimation(fxAnim);
		BackgroundFX->SetScale({1.25, 1.25});
		BackgroundFX->SetZOrder(0.6f);
		BackgroundFX->Play(false, true);

		ParryCircle1 = CreateDefaultSubObject<ParryCircle>(L"Parry Circle1");
		ParryCircle2 = CreateDefaultSubObject<ParryCircle>(L"Parry Circle2");
		ParryCircle3 = CreateDefaultSubObject<ParryCircle>(L"Parry Circle3");
		ParryCircle1->SetWorldLocation({3820, 45.f});
		ParryCircle2->SetWorldLocation({4020, 45.f});
		ParryCircle3->SetWorldLocation({4220, 45.f});

		Game2Door = CreateDefaultSubObject<ExitDoor>(L"ExitDoor");
		Game2Door->SetWorldLocation({6000, -180});
	}

	Tutorial_Map::~Tutorial_Map() {}

	void Tutorial_Map::Update(float DeltaTime)
	{
		USceneComponent::Update(DeltaTime);

		BackgroundFX->SetWorldLocation(MainCam.GetWorldLocation());
		Image_Background->SetWorldLocation(MainCam.GetWorldLocation());
		Image_BackgroundMask->SetWorldLocation(MainCam.GetWorldLocation());

		if (!LocalPlayer.GetMovementComponent()->GetVelocity().IsNearlyZero())
		{
			MainCam.SetPosition(FMath::Lerp(MainCam.GetWorldLocation(), LocalPlayer.GetWorldLocation(), 5.f * DeltaTime));
		}

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
