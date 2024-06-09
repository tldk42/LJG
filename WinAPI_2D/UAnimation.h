#pragma once
#include "CommonInclude.h"

namespace LJG
{
	struct FAnimData
	{
		USprite2DSPtr Sprite = nullptr;
		float         Time   = 1.f;

		FAnimData(USprite2D* InSprite2D, float InTime)
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

		void PlayAnim(UINT InFrame);
		void Pause();
		void Stop();

	private:
		bool                     bIsPlaying;
		UINT                     mFrames;
		steady_clock::time_point mPlayTime;

		FVector2f    mPosition;
		FVector2f    mScale;
		FLinearColor mColor;

		std::vector<FAnimData> mAnimDatas;


	};
}
