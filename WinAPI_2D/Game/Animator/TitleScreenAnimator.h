#pragma once
#include "Component/Animation/UAnimator.h"

namespace LJG
{
	class TitleScreenAnimator : public UAnimator
	{
	public:
		explicit TitleScreenAnimator();
		~TitleScreenAnimator() override;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

	private:
		USpriteAnimation* State_Default;
	};
}
