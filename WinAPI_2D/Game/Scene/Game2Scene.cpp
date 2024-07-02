#include "Game2Scene.h"

#include "Camera.h"
#include "AI/BehaviorTree.h"
#include "Component/Actor/APlayerCharacter.h"
#include "Game/AI/Test/TestBT.h"
#include "Game/Object/Game_2/Background_Game2.h"
#include "Game/Object/Game_2/Enemy/ARibby.h"
#include "Game/Object/Game_2/Enemy/ACroaks.h"

namespace LJG
{

	Game2Scene::Game2Scene(const WText& InName)
		: UScene(InName)
	{
	}

	Game2Scene::~Game2Scene() {}

	void Game2Scene::Initialize()
	{
		UScene::Initialize();
	}

	void Game2Scene::Update(float DeltaTime)
	{
		UScene::Update(DeltaTime);
		LocalPlayer.Update(DeltaTime);
	}

	void Game2Scene::Render()
	{
		UScene::Render();
		LocalPlayer.Render();
	}

	void Game2Scene::Release()
	{
		UScene::Release();
	}

	void Game2Scene::LoadScene()
	{
		UScene::LoadScene();

		LocalPlayer.Initialize();

		Obj_Background = Manager_Object.CreateOrLoad<Background_Game2>(L"Background");
		Enemy_Ribby    = Manager_Object.CreateOrLoad<ARibby>(L"Ribby");
		Enemy_Ribby->Initialize();
		Enemy_Ribby->SetWorldLocation({300.f, -300.f});
		Enemy_Croaks = Manager_Object.CreateOrLoad<ACroaks>(L"Croaks");
		Enemy_Croaks->Initialize();
		Enemy_Croaks->SetWorldLocation({400.f, -320.f});

		MainCam.SetWorldLocation({0, -110.f});
	}

	void Game2Scene::EndScene()
	{
		UScene::EndScene();
	}
}
