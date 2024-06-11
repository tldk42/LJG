#include "UAnimState.h"
#include "UAnimation2D.h"

namespace LJG
{
	UAnimState::UAnimState(const std::wstring& InStateName)
		: mStateName(InStateName)
	{
	}

	UAnimState::~UAnimState()
	{
		UAnimState::Release();
	}

	void UAnimState::Initialize()
	{
		UObject::Initialize();
	}

	void UAnimState::Update(float DeltaTime)
	{
		UObject::Update(DeltaTime);

		for (auto& anim : mAnimSet)
		{
			anim.second->Update(DeltaTime);
		}
	}

	void UAnimState::Render()
	{
		UObject::Render();

		if (mAnimSet.contains(mCurrentState))
			mAnimSet[mCurrentState]->Render();
	}

	void UAnimState::Release()
	{
		for (auto& anim : mAnimSet)
		{
			anim.second = nullptr;
		}
		mAnimSet.clear();
	}

	void UAnimState::AddAnimation(const std::wstring& InAnimName, UAnimation2D* InAnimation)
	{
		if (!mAnimSet.contains(InAnimName))
		{
			mAnimSet[InAnimName].reset(InAnimation);
		}
	}

	void UAnimState::SetState(const std::wstring& InState)
	{
		mCurrentState = InState;
	}
}
