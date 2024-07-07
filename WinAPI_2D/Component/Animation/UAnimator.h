#pragma once
#include "Component/UObject.h"

namespace LJG
{
	class USpriteAnimation;
	using TransitionCond = std::vector<std::function<bool()>>;

	class UAnimator : public UObject
	{
	public:
		explicit UAnimator();
		~UAnimator() override;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

		void RenderDefaultSprite() const;

		inline bool       IsAnyMontagePlaying() const { return bIsMontagePlaying; }
		USpriteAnimation* GetDefaultTrack() const { return mStateMachine.at(0); }
		XSprite2D*        GetSprite2D() const { return mSprite2D.get(); }

		void SetMontageTrack(const uint8_t InType, USpriteAnimation* InAnimation);
		void SeteDefaultTrack(USpriteAnimation* InAnimation);
		void AddState(uint8_t InState, USpriteAnimation* InAnimation);
		void AddTransition(const uint8_t InSrc, const uint8_t InDest, const std::function<bool()>& InCond);

		void SetScale(const FVector2f& InScale) const;
		void SetFlipX(const bool bEnable) { bFlipX = bEnable; }
		void SetZOrder(const float_t InZOrder) const;

		bool GetFlip() const { return bFlipX; }

		void SetState(const uint8_t InState, const bool bLoop);

		void PlayDefaultTrack(bool bReverse = false, bool bLoop = false);
		void PlayMontageAnim(const uint8_t MontageType);

	protected:
		void BlinkEffect();

	protected:
		XSprite2DUPtr                                  mSprite2D;
		bool                                           bIsPlaying;
		bool                                           bFlipX;
		bool                                           bIsMontagePlaying;
		uint8_t                                        mMontageState;
		uint8_t                                        mCurrentState;
		std::unordered_map<uint8_t, USpriteAnimation*> mStateMachine;
		std::unordered_map<uint8_t, USpriteAnimation*> mMontages;
	};
}
