#include "SceneManager.h"

#include "Component/Scene/UScene.h"

namespace LJG
{
	std::vector<WText> SceneManager::GetSceneNames() const
	{
		std::vector<WText> returnValue;

		for (auto& scene : mManagedList)
		{
			returnValue.emplace_back(scene.second->GetName());
		}

		return returnValue;
	}
}
