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

	private:
		friend class TSingleton<SceneManager>;
		SceneManager()  = default;
		~SceneManager() = default;

	public:
		SceneManager(const SceneManager&)            = delete;
		SceneManager& operator=(const SceneManager&) = delete;
	};
}
