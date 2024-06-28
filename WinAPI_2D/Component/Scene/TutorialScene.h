#pragma once
#include "UScene.h"

namespace LJG
{
	class TutorialScene : public UScene
	{
	public:
		TutorialScene();
		~TutorialScene() override;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion
	};
}
