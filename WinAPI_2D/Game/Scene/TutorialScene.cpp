#include "TutorialScene.h"

#include "Component/UImage.h"
#include "Component/Actor/APlayerCharacter.h"
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
	}

	void TutorialScene::Render()
	{
		UScene::Render();
		LocalPlayer.Render();
	}

	void TutorialScene::Release()
	{
		UScene::Release();
	}

	void TutorialScene::LoadScene()
	{

		UScene::LoadScene();
		LocalPlayer.Initialize();

		Obj_Background = Manager_Object.CreateOrLoad<Tutorial_Map>(L"Background");

	}

	void TutorialScene::EndScene()
	{
		UScene::EndScene();
	}
}
