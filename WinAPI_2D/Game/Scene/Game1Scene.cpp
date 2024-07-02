#include "Game1Scene.h"

#include "Component/Actor/APlayerCharacter.h"
#include "Game/Object/Game_1/Background_Game1.h"

namespace LJG
{

	Game1Scene::Game1Scene(const WText& InName)
		: UScene(InName) {}

	Game1Scene::~Game1Scene() {}

	void Game1Scene::Initialize()
	{
		UScene::Initialize();
	}

	void Game1Scene::Update(float DeltaTime)
	{
		UScene::Update(DeltaTime);
		LocalPlayer.Update(DeltaTime);
	}

	void Game1Scene::Render()
	{
		UScene::Render();
		LocalPlayer.Render();
	}

	void Game1Scene::Release()
	{
		UScene::Release();
	}

	void Game1Scene::LoadScene()
	{
		UScene::LoadScene();

		LocalPlayer.Initialize();

		Obj_Background = Manager_Object.CreateOrLoad<Background_Game1>(L"Background");
	}

	void Game1Scene::EndScene()
	{
		UScene::EndScene();
	}
}
