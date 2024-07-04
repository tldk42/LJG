#include "TitleScreenAnimator.h"

#include "Component/Manager/AnimManager.h"
#include "Helper/EngineHelper.h"

namespace LJG
{

	TitleScreenAnimator::TitleScreenAnimator()
	{
		State_Default = CreateSprite(L"cuphead_title_screen");

		AddState(0, State_Default);
	}

	TitleScreenAnimator::~TitleScreenAnimator() {}

	void TitleScreenAnimator::Initialize()
	{
		UAnimator::Initialize();

		mCurrentState = 0;
	}

	void TitleScreenAnimator::Update(float DeltaTime)
	{
		UAnimator::Update(DeltaTime);
	}

	void TitleScreenAnimator::Render()
	{
		UAnimator::Render();
	}

	void TitleScreenAnimator::Release()
	{
		UAnimator::Release();
	}
}
