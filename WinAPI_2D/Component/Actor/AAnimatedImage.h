#pragma once
#include "AActor.h"

namespace LJG
{
	class AAnimatedImage : public AActor
	{
	public:
		explicit AAnimatedImage(const WText& InKey);
		~AAnimatedImage() override;

	public:
	#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
	#pragma endregion

		virtual void Play(bool bReverse = false, bool bEnableLoop = false);

		void SetScale(const FVector2f& InScale) override;

	protected:
		UAnimator* mAnimator;
	};
}
