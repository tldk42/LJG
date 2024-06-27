#pragma once
#include "Manager.h"

namespace LJG
{
	#define Manager_Scene SceneManager::Get()
	
	class UScene;

	class SceneManager : public ManagerBase<UScene, SceneManager>
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
