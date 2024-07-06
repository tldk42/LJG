#pragma once
#include "Component/Actor/AAnimatedImage.h"

namespace LJG
{
	class AWindSprite : public AAnimatedImage
	{
	public:
		explicit AWindSprite();
		~AWindSprite() override;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

		void Play(bool bReverse, bool bEnableLoop) override;

	private:
		FBox2f mWindArea;
	};

}
