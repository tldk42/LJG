#pragma once
#include "Component/USceneComponent.h"


namespace LJG
{
	class Ground;
	class UImage;
	class AAnimatedImage;

	class Background_Game2 : public USceneComponent
	{
	public:
		Background_Game2(const WText& InName);
		~Background_Game2() override;

	public:
		void Update(float DeltaTime) override;
		void Render() override;

	public:
		UImage* Image_JazzbarStage;
		UImage* Image_JazzbarMid;
		UImage* Image_JazzbarBooth;
		UImage* Image_JazzbarTables;
		UImage* Image_JazzbarPlants;

		Ground* Ground_InvisibleBox;
	};
}
