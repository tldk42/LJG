#include "SceneManager.h"

#include "Component/Scene/UScene.h"
#include "Helper/EngineHelper.h"

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

	void SceneManager::MoveScene(const Text& NewSceneName)
	{
		if (!mCurrentSceneName.empty())
		{
			GetResource(Text2WText(mCurrentSceneName))->EndScene();
		}
		CreateOrLoad(Text2WText(NewSceneName))->LoadScene();

	}

	void SceneManager::Initialize()
	{
		CreateOrLoad(L"data/scenes/Intro");
		CreateOrLoad(L"data/scenes/menu");
		CreateOrLoad(L"data/scenes/Tutorial");
		CreateOrLoad(L"data/scenes/game1_1");
	}

	void SceneManager::Update(float DeltaTime) {}
	void SceneManager::Render() {}
	void SceneManager::Release() {}
}
