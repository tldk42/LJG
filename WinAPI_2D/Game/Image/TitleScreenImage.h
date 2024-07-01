#pragma once
#include "Component/Actor/AAnimatedImage.h"

namespace LJG
{
	class TitleScreenImage : public AAnimatedImage
	{
	public:
		explicit TitleScreenImage(const WText& InName);
		~TitleScreenImage() override;
	};
}
