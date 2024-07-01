#include "MenuScene.h"

#include "InputManager.h"
#include "Component/UImage.h"
#include "Component/Manager/SceneManager.h"

namespace LJG
{

	MenuScene::MenuScene(const WText& InName)
		: UScene(InName) {}

	MenuScene::~MenuScene() {}

	void MenuScene::Initialize()
	{
		UScene::Initialize();
	}

	void MenuScene::Update(float DeltaTime)
	{
		UScene::Update(DeltaTime);

		if (Manager_Input.IsKeyDown(EKeyCode::P))
		{
			Manager_Scene.MoveScene(L"Tutorial");
		}
	}

	void MenuScene::Render()
	{
		UScene::Render();
	}

	void MenuScene::Release()
	{
		UScene::Release();
	}

	void MenuScene::LoadScene()
	{
		LOG_CORE_TRACE("Starting Menu Scene Load....");
		backgroundImage = Manager_Object.CreateOrLoad<UImage>(L"Background",
															  L"./\\rsc\\CupHead\\Sprite\\MainMenuBackground_0.png",
															  0.8f);
		backgroundImage->SetScale({1.3f, 1.3f});
	}

	void MenuScene::EndScene()
	{
		UScene::EndScene();
		Manager_Scene.SetScene(L"Tutorial");
		// FTimer::SetTimer([&](){
		// 	UScene::EndScene();
		// 	Manager_Scene.SetScene(L"Menu");
		// }, 1.f);
	}
}
