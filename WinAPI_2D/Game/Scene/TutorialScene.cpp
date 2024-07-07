#include "TutorialScene.h"

#include "FTimer.h"
#include "Component/UImage.h"
#include "Component/Actor/APlayerCharacter.h"
#include "Component/Manager/SceneManager.h"
#include "Game/Object/Common/InGame_HUD.h"
#include "Game/Object/Tutorial/Background_Tut.h"
#include "Shape/UBoxComponent.h"

namespace LJG
{

	TutorialScene::TutorialScene(const WText& InName)
		: UScene(InName) {}

	TutorialScene::~TutorialScene() {}

	void TutorialScene::Initialize()
	{
		UScene::Initialize();
	}

	void TutorialScene::Update(float DeltaTime)
	{
		UScene::Update(DeltaTime);
		LocalPlayer.Update(DeltaTime);
		GAME_HUD.Update(DeltaTime);
	}

	void TutorialScene::Render()
	{
		UScene::Render();
		LocalPlayer.Render();
		GAME_HUD.Render();
	}

	void TutorialScene::Release()
	{
		GAME_HUD.Release();
		UScene::Release();
	}

	void TutorialScene::LoadScene()
	{
		UScene::LoadScene();
		Manager_Collision.EnableLayerCheck(ETraceType::Pawn, ETraceType::Ground, true);
		Manager_Collision.EnableLayerCheck(ETraceType::Pawn, ETraceType::Interact, true);
		Manager_Collision.EnableLayerCheck(ETraceType::Projectile, ETraceType::Interact, true);

		LocalPlayer.Initialize();
		GAME_HUD.Initialize();

		Obj_Background = CreateDefaultSubObject<Tutorial_Map>(L"Background");
	}

	void TutorialScene::EndScene()
	{
		TutorialScene::Release();
		Manager_Scene.SetScene(L"Game_2");
	}
}
