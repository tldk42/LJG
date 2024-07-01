#pragma once
#include "Manager.h"
#include "Component/Scene/UScene.h"

namespace LJG
{
	#define Manager_Scene SceneManager::Get()

	class SceneManager : public ManagerBase<UScene, SceneManager>, public ICoreAPI
	{
	public:
		std::vector<WText> GetSceneNames() const;
		UScene*            GetCurrentScene() { return GetResource<UScene>(mCurrentSceneName); }
		void               MoveScene(const WText& NewSceneName);
		void               SetScene(const WText& InSceneName);

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

	private:
		WText mCurrentSceneName;

	private:
		friend class TSingleton<SceneManager>;
		SceneManager()  = default;
		~SceneManager() = default;

	public:
		SceneManager(const SceneManager&)            = delete;
		SceneManager& operator=(const SceneManager&) = delete;
	};
}
