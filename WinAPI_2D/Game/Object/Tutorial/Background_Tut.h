#pragma once
#include "Component/USceneComponent.h"


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
		Ground* Ground_InvisibleBox;

		UImage* Image_Platform;
		UImage* Image_ExitDoor;
	};

}
