#pragma once
#include "Component/Scene/UScene.h"

namespace LJG
{
	class Background_Game1;

	class Game1Scene : public UScene
	{
	public:
		explicit Game1Scene(const WText& InName);
		~Game1Scene() override;

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
		Background_Game1* Obj_Background;

	};
}
