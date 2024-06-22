#pragma once
#include "UObject.h"

namespace LJG
{
	struct FAnimData_Deprecated;

	class UAnimator : public UObject
	{

	public:
		explicit  UAnimator(const WText& InKey);
		~UAnimator() override;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

		void SetState(const uint8_t InState, const bool bLoop);
		void AddState(uint8_t InState, UAnimation* InAnimation);
		void SetFlipX(const bool bEnable) { bFlipX = bEnable; }
		bool FlipX() const { return bFlipX; }

	public:
		static std::vector<FAnimData_Deprecated> LoadAnimation(WTextView      InPath, const uint32_t InMaxSprite,
													const uint32_t InCustomFrame     = 60,
													const bool     bForceCustomFrame = false);

	private:
		bool                                             bIsPlaying;
		bool                                             bFlipX;
		uint8_t                                          mCurrentState;
		std::unordered_map<uint8_t, UAnimation*>         mStateMachine;
	};
}
