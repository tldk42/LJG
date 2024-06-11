#pragma once
#include "UObject.h"

namespace LJG
{
	class UAnimator : public UObject, public std::enable_shared_from_this<UAnimator>
	{
	public:
		UAnimator();
		~UAnimator() override;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

		void SetState(const uint8_t InState, const bool bLoop);
		void AddState(uint8_t InState, const UAnimationSPtr& InAnimation);

	private:
		bool                                        bIsPlaying;
		uint8_t                                     mCurrentState;
		std::unordered_map<uint8_t, UAnimationSPtr> mStateMachine;
	};
}
