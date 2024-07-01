#pragma once
#include "Component/Manager/Manager.h"


namespace LJG
{
	#define GWorld World::Get()

	DECLARE_DYNAMIC_DELEGATE(FOnDebugModeChanged);

	class UScene;
	class ACamera;

	class World : public TSingleton<World>, public ICoreAPI
	{
	public:
		void SpawnGameMode();

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

	public:
		void MoveScene(const WText& InSceneName);

	public:
		FOnDebugModeChanged OnDebugModeChanged;
		
	private:
		std::unordered_map<WText, UScene*> mScenes;
		bool                               bDebug;

	};
}
