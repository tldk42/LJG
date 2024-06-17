#include "UAnimator.h"

#include "AActor.h"
#include "UAnimation.h"
#include "DirectX/XSprite2D.h"

namespace LJG
{

	UAnimator::UAnimator()
		: bIsPlaying(false)
	{}

	UAnimator::~UAnimator() {}

	void UAnimator::Initialize()
	{
		UObject::Initialize();
	}

	void UAnimator::Update(float DeltaTime)
	{
		// UObject::Update(DeltaTime);

		if (mStateMachine.contains(mCurrentState))
		{
			UAnimation* currentAnim = mStateMachine[mCurrentState];
			currentAnim->Update(DeltaTime);
			if (currentAnim->GetNextAnimation() < MAXUINT8)
			{
				SetState(currentAnim->GetNextAnimation(), true);
				
			}
		}

	}

	void UAnimator::Render()
	{
		UObject::Render();

		if (mStateMachine.contains(mCurrentState))
		{
			mStateMachine[mCurrentState]->Render();
		}
	}

	void UAnimator::Release()
	{
		UObject::Release();
	}

	void UAnimator::SetState(const uint8_t InState, const bool bLoop)
	{
		const auto cachedState = mCurrentState;

		mCurrentState = InState;

		if (mStateMachine.contains(mCurrentState))
		{
			if (!bIsPlaying || cachedState != mCurrentState)
			{
				bIsPlaying = true;
				mStateMachine[mCurrentState]->PlayAnim(bLoop);
			}
			if (cachedState != mCurrentState)
				mStateMachine[cachedState]->Stop();

		}
	}

	void UAnimator::AddState(const uint8_t InState, UAnimation* InAnimation)
	{
		if (!mStateMachine.contains(InState))
		{
			mStateMachine[InState] = InAnimation;

			InAnimation->SetAnimator(this);
		}
	}

	std::vector<FAnimData> UAnimator::LoadAnimation(WTextView      InPath, const uint32_t    InMaxSprite,
													const uint32_t InCustomFrame, const bool bForceCustomFrame)
	{
		// C++11 이후에 local var를 반환하면 r-value로 간주되어서 이동생성자로 최적화 된다고하는데 과연...
		std::vector<FAnimData> animSet;

		for (uint32_t i = 1; i <= InMaxSprite; ++i)
		{
			std::wstringstream ss;
			ss << InPath << std::setw(4) << std::setfill(L'0') << i << L".png";
			std::wstring filePath = ss.str();

			animSet.emplace_back(std::make_unique<XSprite2D>(filePath),
								 1.f / (bForceCustomFrame
											? static_cast<float>(InCustomFrame)
											: static_cast<float_t>(InMaxSprite)));
		}

		return animSet;
	}
}
