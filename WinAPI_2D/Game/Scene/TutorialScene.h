#pragma once
#include "Component/Scene/UScene.h"


namespace LJG
{
	class Tutorial_Map;
	class UBoxComponent;

	class TutorialScene : public UScene
	{
	public:
		explicit TutorialScene(const WText& InName);
		~TutorialScene() override;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

		void LoadScene() override;
		void EndScene() override;

	private:
		Tutorial_Map* Obj_Background;

	};
}
