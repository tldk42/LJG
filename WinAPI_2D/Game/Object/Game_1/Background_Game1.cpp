#include "Background_Game1.h"

#include <ranges>

#include "Component/UImage.h"
#include "Game/Ground.h"

namespace LJG
{

	Background_Game1::Background_Game1(const WText& InName)
		: USceneComponent(InName)
	{
		Image_BackgroundSheet_0 = CreateDefaultSubObject<UImage>(L"Image_BackgroundSheet_0",
																 L"rsc/CupHead/Sprite/BackgroundSheet_0.png",
																 0.5f);

		Image_BackgroundSheet_1 = CreateDefaultSubObject<UImage>(L"Image_BackgroundSheet_1",
																 L"rsc/CupHead/Sprite/BackgroundSheet_1.png",
																 0.503f);
		Image_BackgroundSheet_2 = CreateDefaultSubObject<UImage>(L"Image_BackgroundSheet_2",
																 L"rsc/CupHead/Sprite/BackgroundSheet_2.png",
																 0.504f);
		Image_BackgroundSheet_3 = CreateDefaultSubObject<UImage>(L"Image_BackgroundSheet_3",
																 L"rsc/CupHead/Sprite/BackgroundSheet_3.png",
																 0.501f);
		Image_BackgroundSheet_4 = CreateDefaultSubObject<UImage>(L"Image_BackgroundSheet_4",
																 L"rsc/CupHead/Sprite/BackgroundSheet_4.png",
																 0.502f);
		Image_BackgroundSheet_8 = CreateDefaultSubObject<UImage>(L"Image_BackgroundSheet_8",
																 L"rsc/CupHead/Sprite/BackgroundSheet_8.png",
																 0.509f);
		Image_BackgroundSheet_10 = CreateDefaultSubObject<UImage>(L"Image_BackgroundSheet_10",
																  L"rsc/CupHead/Sprite/BackgroundSheet_10.png",
																  0.508f);
		Image_BackgroundSheet_11 = CreateDefaultSubObject<UImage>(L"Image_BackgroundSheet_11",
																  L"rsc/CupHead/Sprite/BackgroundSheet_11.png",
																  0.508f);

		Image_BackgroundSheet_0->SetPosition(FVector2f(25.2000004, -01.28999993));
		Image_BackgroundSheet_1->SetPosition(FVector2f(7.19999969, 115.3));
		Image_BackgroundSheet_2->SetPosition(FVector2f(3.9, 155.5));
		Image_BackgroundSheet_3->SetPosition(FVector2f(3.16, 78.8));
		Image_BackgroundSheet_4->SetPosition(FVector2f(31.8, 109.3));
		Image_BackgroundSheet_8->SetPosition(FVector2f(-256.3, 265.4));
		Image_BackgroundSheet_10->SetPosition({-55.3f, 117.2f});
		Image_BackgroundSheet_11->SetPosition({348.4, 163.3f});

		Image_BackgroundSheet_0->SetScale({1.5f, 1.5f});
		Image_BackgroundSheet_1->SetScale({1.5f, 1.5f});
		Image_BackgroundSheet_2->SetScale({1.5f, 1.5f});
		Image_BackgroundSheet_3->SetScale({1.5f, 1.5f});
		Image_BackgroundSheet_4->SetScale({1.5f, 1.5f});
		Image_BackgroundSheet_8->SetScale({1.5f, 1.5f});
		Image_BackgroundSheet_10->SetScale({1.5f, 1.5f});
		Image_BackgroundSheet_11->SetScale({1.5f, 1.5f});


		Image_Sky = CreateDefaultSubObject<UImage>(L"Image_Sky",
												   L"rsc/CupHead/Sprite/BackgroundSheet_9.png",
												   0.9f);
		Image_Sky->SetScale({2.66f, 2.66f});
		Image_Sky->SetPosition({23.15f, 129.5f});


		Image_Grass_0 = CreateDefaultSubObject<UImage>(L"Image_Grass_0",
													   L"rsc/CupHead/Sprite/BackgroundSheet_12.png",
													   0.511f);
		Image_Grass_0->SetPosition(FVector2f(78.2736897, 78.2736897));
		Image_Grass_1 = CreateDefaultSubObject<UImage>(L"Image_Grass_1",
													   L"rsc/CupHead/Sprite/BackgroundSheet_14.png",
													   0.511f);
		Image_Grass_1->SetPosition(FVector2f(71.2000012, 155.599999));
		Image_Grass_1->SetScale({1.5f, 1.5f});


		// AnimatedImage_Wheel = CreateDefaultSubObject<AAnimatedImage>(L"Anim_Wheel");

		Ground_InvisibleBox = CreateDefaultSubObject<Ground>(L"Ground_Default");
		Ground_InvisibleBox->SetBoxSize({1560.f, 10.f});
		Ground_InvisibleBox->SetWorldLocation({0, -70.f});

		constexpr int32_t array[6] = {6, 17, 19, 18, 20, 21};
		Image_Clouds.reserve(6);
		for (int32_t i = 0; i < 6; ++i)
		{
			std::wstringstream stringstream;

			stringstream << L"rsc/CupHead/Sprite/BackgroundSheet_" << array[i] << L".png";

			WText filePath = stringstream.str();
			Image_Clouds.push_back(CreateDefaultSubObject<UImage>(L"Image_BackgroundSheet_10", filePath, 0.516f));
			// Image_Clouds[i]->SetScale({1.5f, 1.5f});
		}

		// Image_Clouds[0]->SetPosition({-64.6f, 345.5f});
		// Image_Clouds[1]->SetPosition({225.2f, 318.f});
		// Image_Clouds[2]->SetPosition({-157.8f, 162.1f});
		// Image_Clouds[3]->SetPosition({616.f, 175.f});
		// Image_Clouds[4]->SetPosition({813.f, 300.f});
		// Image_Clouds[5]->SetPosition({1234.f, 183.f});

	}

	Background_Game1::~Background_Game1() {}

	void Background_Game1::Update(float DeltaTime)
	{
		USceneComponent::Update(DeltaTime);
	}

	void Background_Game1::Render()
	{
		USceneComponent::Render();

		for (auto& obj : mChildObjects | std::views::values)
		{
			obj->Render();
		}
	}
}
