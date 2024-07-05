#pragma once
#include "Component/Scene/UScene.h"


namespace LJG
{
	class Background_Game2;
	class ACroaks;

	namespace AI
	{
		class Game2BT;
	};

	class Game2Scene : public UScene
	{
	public:
		explicit Game2Scene(const WText& InName);
		~Game2Scene() override;

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
		Background_Game2* Obj_Background;
		ACroaks*          Enemy_Croaks;
	};
}
