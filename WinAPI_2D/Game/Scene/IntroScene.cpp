#include "IntroScene.h"

#include "FTimer.h"
#include "InputManager.h"
#include "Component/UImage.h"
#include "Component/Actor/AAnimatedImage.h"
#include "Component/Animation/USpriteAnimation.h"
#include "Component/Manager/ObjectManager.h"
#include "Component/Manager/SceneManager.h"
#include "Component/Manager/SoundManager.h"
#include "Game/Image/FadeInImage.h"
#include "Game/Image/TitleScreenImage.h"
#include "Helper/EngineHelper.h"

namespace LJG
{

	IntroScene::IntroScene(const WText& InName)
		: UScene(InName) {}

	IntroScene::~IntroScene() {}

	void IntroScene::Initialize()
	{
		UScene::Initialize();
		LoadScene();
	}

	void IntroScene::Update(float DeltaTime)
	{
		UScene::Update(DeltaTime);

		if (Manager_Input.IsKeyDown(EKeyCode::P))
		{
			Manager_Scene.MoveScene(L"Menu");
		}
	}

	void IntroScene::Render()
	{
		UScene::Render();
	}

	void IntroScene::Release()
	{
		UScene::Release();
	}

	void IntroScene::LoadScene()
	{
		LOG_CORE_TRACE("Starting Intro Scene Load....");

		backgroundImage = Manager_Object.CreateOrLoad<UImage>(L"Background",
															  L"./\\rsc\\CupHead\\Texture2D\\title_screen_background.png",
															  0.8f);
		backgroundImage->SetScale({1.4f, 1.4f});
		LOG_CORE_TRACE("Image_Background: Success");

		playerAnim = Manager_Object.CreateOrLoad<TitleScreenImage>(L"TitleScreenImage");
		playerAnim->Play(false, true);
		LOG_CORE_TRACE("Image_TitleScreen: Success");

		FadeInAnim = Manager_Object.CreateOrLoad<FadeInImage>(L"FadeInImage");
		FadeInAnim->SetScale({3.5f, 3.5f});
		LOG_CORE_TRACE("Image_FadeIn: Success");

		UAudio* audio = Manager_Audio.CreateOrLoad(L"rsc/AudioClip/MUS_BotanicPanic.wav");
		audio->Play(true);
		LOG_CORE_TRACE("Music_BotanicPanic: Success");

	}

	void IntroScene::MoveScene(WTextView InNextScene)
	{
		UScene::MoveScene(InNextScene);
		Manager_Scene.SetScene(WText(InNextScene));
		FTimer::SetTimer([&](){
			UScene::EndScene();
		}, 0.2f);
	}

	void IntroScene::EndScene()
	{
		FadeInAnim->Play(true, false);
		FTimer::SetTimer([&](){
			UScene::EndScene();
			Manager_Scene.SetScene(L"Menu");
		}, 0.8f);
	}
}
