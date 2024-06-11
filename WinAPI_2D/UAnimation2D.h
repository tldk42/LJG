#pragma once
#include "UObject.h"

namespace LJG
{
	struct FAnimData2D
	{
		XSprite2DSPtr Sprite = nullptr;
		float         Time   = 1.f;

		FAnimData2D(XSprite2D* InSprite2D, float InTime)
			: Sprite(InSprite2D),
			  Time(InTime)
		{
		}
	};

	class UAnimation2D : public UObject
	{
	public:
		UAnimation2D(std::vector<FAnimData2D>& InAnims);
		~UAnimation2D() override;

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

		void SetPosition(const FVector2f& InPosition);
		void SetScale(const FVector2f& InScale);

	private:
		bool                     bIsPlaying;
		UINT                     mIndex;
		steady_clock::time_point mPlayTime;

		FVector2f    mPosition;
		FVector2f    mScale;
		FLinearColor mColor;

		std::vector<FAnimData2D> mAnimDatas;
	};
}
