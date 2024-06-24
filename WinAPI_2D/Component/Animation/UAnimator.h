#pragma once
#include "Component/UObject.h"

namespace LJG
{
	class USpriteAnimation;
	using TransitionCond = std::vector<std::function<bool()>>;

	class UAnimator : public UObject
	{
	public:
		explicit UAnimator(const WText& InKey);
		~UAnimator() override;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

		void AddState(uint8_t InState, USpriteAnimation* InAnimation);
		void AddTransition(const uint8_t InSrc, const uint8_t InDest, const std::function<bool()>& InCond);

		void SetFlipX(const bool bEnable) { bFlipX = bEnable; }

	private:
		void SetState(const uint8_t InState, const bool bLoop);

	protected:
		bool                                           bIsPlaying;
		bool                                           bFlipX;
		uint8_t                                        mCurrentState;
		std::unordered_map<uint8_t, USpriteAnimation*> mStateMachine;
	};
}
