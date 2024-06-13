#pragma once
#include "CommonInclude.h"
#include "UObject.h"

namespace LJG
{
	struct FAnimData
	{
		XSprite2DUPtr Sprite = nullptr;
		float         Time   = 1.f;
	};

	class UAnimation : public UObject
	{
	public:
		UAnimation(std::vector<FAnimData>&& InAnims);
		~UAnimation() override;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

		void PlayAnim(bool InbLoop);
		void Pause();
		void Stop();

		void SetAnimator(UAnimator* InAnimator) { mOwnerAnimator = InAnimator; }

	private:
		bool                     bLoop;
		bool                     bIsPlaying;
		UINT                     mFrames;
		steady_clock::time_point mPlayTime;

		UAnimator* mOwnerAnimator;

		FVector2f    mPosition;
		FVector2f    mScale;
		FLinearColor mColor;

		std::vector<FAnimData> mAnimDatas;
	};
}
