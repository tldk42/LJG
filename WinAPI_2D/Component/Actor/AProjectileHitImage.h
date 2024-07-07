#pragma once
#include "AAnimatedImage.h"

namespace LJG
{
	class AProjectileHitImage : public AAnimatedImage
	{
	public:
		explicit AProjectileHitImage();
		~AProjectileHitImage() override;

	public:
	#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
	#pragma endregion

	private:
		static int32_t mCounter;
	};
}
