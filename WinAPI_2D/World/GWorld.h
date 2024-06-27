#pragma once
#include "Component/Manager/Manager.h"


namespace LJG
{
	class UScene;
	class ACamera;

	class GWorld : public TSingleton<GWorld>, public ICoreAPI
	{
	public:
		static void SpawnWorld();

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

	public:
		void BeginScene();
		void EndScene();
		void MoveScene();

	protected:
		std::unordered_map<WText, UScene*> mScenes;
		ACamera*                           mWorldCamera;
	};
}
