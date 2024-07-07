#pragma once
#include "AActor.h"

namespace LJG
{
	class USpriteAnimation;
}
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
		void         PlayMontage() const;

		void SetMontage(USpriteAnimation* InAnim) const;
		void SetAnimation(USpriteAnimation* InAnim) const;
		void SetScale(const FVector2f& InScale) override;
		void SetZOrder(const float_t InZOrder) const;

	protected:
		UAnimator* mAnimator;
	};
}
