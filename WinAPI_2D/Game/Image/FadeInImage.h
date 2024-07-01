#pragma once
#include "Component/Actor/AAnimatedImage.h"

namespace LJG
{
	class USpriteAnimation;

	class FadeInImage : public AAnimatedImage
	{
	public:
		explicit FadeInImage(const WText& InName);
		~FadeInImage() override;

	public:
		USpriteAnimation* State_Default;
	};
}
