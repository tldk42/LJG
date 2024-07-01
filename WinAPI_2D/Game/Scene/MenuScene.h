#pragma once
#include "Component/Scene/UScene.h"

namespace LJG
{
	class UImage;

	class MenuScene : public UScene
	{
	public:
		explicit MenuScene(const WText& InName);
		~MenuScene() override;

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
		UImage* backgroundImage;
	};
}
