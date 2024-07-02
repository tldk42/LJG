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

		void PlayDefaultTrack(bool bReverse = false, bool bLoop = false);
		void AddState(uint8_t InState, USpriteAnimation* InAnimation);
		void AddTransition(const uint8_t InSrc, const uint8_t InDest, const std::function<bool()>& InCond);

		void SetFlipX(const bool bEnable) { bFlipX = bEnable; }
		void SetZOrder(const float_t InZOrder) const;

	protected:
		void SetState(const uint8_t InState, const bool bLoop);

	protected:
		XSprite2DUPtr                                  mSprite2D;
		bool                                           bIsPlaying;
		bool                                           bFlipX;
		uint8_t                                        mCurrentState;
		std::unordered_map<uint8_t, USpriteAnimation*> mStateMachine;
	};
}
