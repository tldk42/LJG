#include "Game2Scene.h"

#include "Camera.h"
#include "AI/BehaviorTree.h"
#include "Component/Actor/APlayerCharacter.h"
#include "Component/Manager/SceneManager.h"
#include "Game/Object/Game_2/Background_Game2.h"
#include "Game/Object/Game_2/Enemy/ARibby.h"
#include "Game/Object/Game_2/Enemy/ACroaks.h"
#include "Shape/CollisionManager.h"

namespace LJG
{

	Game2Scene::Game2Scene(const WText& InName)
		: UScene(InName)
	{}

	Game2Scene::~Game2Scene() {}

	void Game2Scene::Initialize()
	{
		UScene::Initialize();
	}

	void Game2Scene::Update(float DeltaTime)
	{
		UScene::Update(DeltaTime);
		Croaks.Update(DeltaTime);
		Ribby.Update(DeltaTime);
		LocalPlayer.Update(DeltaTime);
	}

	void Game2Scene::Render()
	{
		UScene::Render();
		Croaks.Render();
		Ribby.Render();
		LocalPlayer.Render();
	}

	void Game2Scene::Release()
	{
		UScene::Release();
	}

	void Game2Scene::LoadScene()
	{
		UScene::LoadScene();
		Manager_Collision.EnableLayerCheck(ETraceType::Pawn, ETraceType::Ground, true);

		LocalPlayer.Initialize();

		Obj_Background = Manager_Object.CreateOrLoad<Background_Game2>(L"Background");
		Ribby.Initialize();
		Ribby.SetWorldLocation({300.f, -300.f});
		Croaks.Initialize();
		Croaks.SetWorldLocation({400.f, -250.f});

		MainCam.SetWorldLocation({0, -110.f});
	}

	void Game2Scene::EndScene()
	{
		UScene::EndScene();
	}
}