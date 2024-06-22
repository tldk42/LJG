#pragma once
#include "CommonInclude.h"
#include "UObject.h"
#include "USceneComponent.h"

namespace LJG
{
	struct FAnimData_Deprecated
	{
		XSprite2DUPtr Sprite = nullptr;
		float         Time   = 1.f;
	};

	class UAnimation : public USceneComponent
	{
		using TransitionCondition = std::function<bool()>;

	public:
		UAnimation(const WText& InKey, std::vector<FAnimData_Deprecated>&& InAnims);
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
		void AddTransition(const uint8_t InAnimName, const TransitionCondition& InRule, UAnimation* InAnim);
		void AddTransitionCondition(const uint8_t InAnimName, const TransitionCondition& InRule);

		uint8_t     GetNextAnimation();
		UAnimation* FindAdjAnim(const uint8_t InAnimName);

	private:
		bool                     bLoop;
		bool                     bIsPlaying;
		UINT                     mFrames;
		steady_clock::time_point mPlayTime; // 총 재생 시간

		std::vector<FAnimData_Deprecated> mAnimDatas; // 1 프레임 스프라이트 집합

	private:
		UAnimator* mOwnerAnimator;

		uint8_t mCandidateState;

		std::unordered_map<uint8_t, UAnimation*>                      mTransitions; // StateName <-> State Anim
		std::unordered_map<uint8_t, std::vector<TransitionCondition>> mTransitionRules; // StateName <-> Transition Rule
	};
}
