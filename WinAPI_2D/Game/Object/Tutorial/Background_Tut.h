#pragma once
#include "Component/USceneComponent.h"


namespace LJG
{
	class ExitDoor;
}
namespace LJG
{
	class ParryCircle;
}
namespace LJG
{
	class AAnimatedImage;
}
namespace LJG
{
	class UImage;
	class Ground;

	class Tutorial_Map : public USceneComponent
	{
	public:
		Tutorial_Map(const WText& InName);
		~Tutorial_Map() override;

	public:
		void Update(float DeltaTime) override;
		void Render() override;

	public:
		UImage* Image_Background;
		UImage* Image_BackgroundMask;

		Ground* Ground_Cube;
		Ground* Ground_Cube2;
		Ground* Ground_Cube3;
		Ground* Ground_Platform;
		Ground* Ground_Cylinder;
		Ground* Ground_InvisibleBox;

		ParryCircle* ParryCircle1;
		ParryCircle* ParryCircle2;
		ParryCircle* ParryCircle3;

		ExitDoor* Game2Door;

		AAnimatedImage* BackgroundFX;

		UImage* Image_Cube2Sign;
		UImage* Image_ExitDoor;
	};

}
