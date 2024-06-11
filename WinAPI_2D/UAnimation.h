#pragma once
#include "CommonInclude.h"

namespace LJG
{
	struct FAnimData
	{
		XSprite2DSPtr Sprite = nullptr;
		float         Time   = 1.f;

		FAnimData(XSprite2D* InSprite2D, float InTime)
			: Sprite(InSprite2D),
			  Time(InTime) {}
	};

	class UAnimation : public ICoreAPI
	{
	public:
		UAnimation(std::vector<FAnimData>& InAnims);
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

		void SetAnimator(UAnimatorSPtr InAnimator) { mOwnerAnimator = InAnimator; }

	private:
		bool                     bLoop;
		bool                     bIsPlaying;
		UINT                     mFrames;
		steady_clock::time_point mPlayTime;

		UAnimatorWPtr mOwnerAnimator;

		FVector2f    mPosition;
		FVector2f    mScale;
		FLinearColor mColor;

		std::vector<FAnimData> mAnimDatas;
	};
}
