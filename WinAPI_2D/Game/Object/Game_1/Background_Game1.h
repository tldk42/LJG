#pragma once
#include "Component/USceneComponent.h"


namespace LJG
{
	class Ground;
	class UImage;
	class AAnimatedImage;

	class Background_Game1 : public USceneComponent
	{
	public:
		Background_Game1(const WText& InName);
		~Background_Game1() override;

	public:
		void Update(float DeltaTime) override;
		void Render() override;

	public:
		UImage* Image_BackgroundSheet_0;
		UImage* Image_BackgroundSheet_1;
		UImage* Image_BackgroundSheet_2;
		UImage* Image_BackgroundSheet_3;
		UImage* Image_BackgroundSheet_4;
		UImage* Image_BackgroundSheet_8;
		UImage* Image_BackgroundSheet_10;
		UImage* Image_BackgroundSheet_11;

		UImage* Image_Sky;

		UImage* Image_Grass_0;
		UImage* Image_Grass_1;

		AAnimatedImage* AnimatedImage_Wheel;

		Ground* Ground_InvisibleBox;

		std::vector<UImage*> Image_Clouds;
	};
}
