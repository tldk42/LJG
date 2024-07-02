#include "SceneManager.h"


#include "Game/Scene/Game1Scene.h"
#include "Game/Scene/Game2Scene.h"
#include "Game/Scene/IntroScene.h"
#include "Game/Scene/MenuScene.h"
#include "Game/Scene/TutorialScene.h"
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

	void SceneManager::MoveScene(const WText& NewSceneName)
	{
		if (!mCurrentSceneName.empty())
		{
			GetResource(mCurrentSceneName)->EndScene();
		}
		else
		{
			CreateOrLoad(NewSceneName)->LoadScene();
			mCurrentSceneName = NewSceneName;
		}
	}

	void SceneManager::SetScene(const WText& InSceneName)
	{
		CreateOrLoad(InSceneName)->LoadScene();
		mCurrentSceneName = InSceneName;
	}

	void SceneManager::Initialize()
	{
		CreateOrLoad<IntroScene>(L"Intro");
		CreateOrLoad<MenuScene>(L"Menu");
		CreateOrLoad<TutorialScene>(L"Tutorial");
		CreateOrLoad<Game1Scene>(L"Game_1");
		CreateOrLoad<Game2Scene>(L"Game_2");
	}

	void SceneManager::Update(float DeltaTime)
	{
		mManagedList[mCurrentSceneName]->Update(DeltaTime);
	}

	void SceneManager::Render()
	{
		mManagedList[mCurrentSceneName]->Render();
	}

	void SceneManager::Release()
	{}
}
