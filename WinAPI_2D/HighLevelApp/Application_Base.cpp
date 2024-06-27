#include "Application_Base.h"

#include "AHUD.h"
#include "Component/Actor/APawn.h"
#include "InputManager.h"
#include "Component/Manager/ObjectManager.h"
#include "Renderer.h"
#include "FTimer.h"
#include "Window.h"
#include "Component/UAudio.h"
#include "Component/Actor/ACharacter.h"
#include "Component/Animation/USpriteAnimation.h"
#include "Component/Manager/AnimManager.h"
#include "Component/Manager/GUIManager.h"
#include "Component/Manager/SoundManager.h"
#include "Component/Manager/TextureManager.h"
#include "DirectX/XTexture.h"
#include "GUI/GUI_FileBrowser.h"
#include "GUI/GUI_Hierarchy.h"
#include "GUI/GUI_Inspector.h"
#include "GUI/GUI_Inspector_MapEdit.h"
#include "GUI/GUI_MapEditor.h"

namespace LJG
{
	Application_Base::Application_Base(LPCWSTR WindowTitle, const FWindowData& WindowData)
		: mWindowTitle(WindowTitle),
		  mWindowData(WindowData),
		  mWindow(nullptr),
		  mTimer(nullptr),
		  mDeltaTime(0),
		  mFramesPerSec(0),
		  mUpdatesPerSec(0),
		  bIsInitialized(false),
		  bIsRunning(false),
		  bIsPaused(false)
	{
		Application_Base::Initialize();
	}

	Application_Base::~Application_Base()
	{
		Application_Base::Release();
	}

	void Application_Base::Initialize()
	{
		// Logger를 가장 먼저 초기화 해야 함 다른 초기화중에 Logger를 사용
		Logger::Initialize();
		InputManager::Initialize();
		SoundManager::Initialize();

		// 무조건 Device를 생성전에 Window Handle Instance를 반환해야 함 
		Initialize_Application();

		Renderer::Initialize();

		GUIManager::Initialize();

		Manager_Object.Initialize();

		AnimManager::LoadAllAnims();
	}

	void Application_Base::Update(float DeltaTime)
	{
		InputManager::Update(DeltaTime);

		SoundManager::Update(DeltaTime);

		Manager_Object.Update(DeltaTime);

		GUIManager::Update(DeltaTime);

		Renderer::Update(DeltaTime);
	}

	void Application_Base::Render()
	{
		// RenderTarget (Background 또는 기본 바탕색) 지워주고
		Renderer::Clear(FLinearColor::Gallary);

		// 모든 렌더링 오브젝트 Draw
		Manager_Object.Render();

		// GUI Draw
		GUIManager::Render();

		// TODO: UI Draw

		// Back Buffer -> Present
		Renderer::Render();
	}

	void Application_Base::Release()
	{
		GUIManager::Release();

		Renderer::Release();

		SoundManager::Release();
	}

	void Application_Base::Initialize_Application()
	{
		if (!bIsInitialized)
		{
			mWindow.reset(new Window(mWindowTitle, mWindowData));
			mTimer.reset(new FTimer());

			bIsInitialized = true;
		}
	}

	void Application_Base::Start()
	{
		bIsRunning = true;
		bIsPaused  = false;

		timer       = 0.f;
		updateTimer = mTimer->ElapsedMillis();

		Run();
	}

	void Application_Base::Pause()
	{
		bIsPaused = true;
	}

	void Application_Base::Resume()
	{
		bIsPaused = false;
	}

	void Application_Base::Stop()
	{
		bIsRunning = true;
	}

	Application_Base& Application_Base::Get(LPCWSTR WindowTitle, const FWindowData& WindowData)
	{
		static Application_Base instance(WindowTitle, WindowData);
		return instance;
	}

	void Application_Base::Run()
	{
		if (bIsInitialized)
		{
			int32_t frameCounter  = 0;
			int32_t updateCounter = 0;

			// TGUI_Inspector*   gui         = Manager_GUI.Create<TGUI_Inspector>(L"Inspector");
			// GUI_Inspector_MapEdit* mapInspec   = Manager_GUI.CreateOrLoad<GUI_Inspector_MapEdit>(L"MapInspector");
			// GUI_FileBrowser*       fileBrowser = Manager_GUI.CreateOrLoad<GUI_FileBrowser>(L"FileBrowser");
			// GUI_MapEditor*         mapEditor   = Manager_GUI.CreateOrLoad<GUI_MapEditor>(L"MapEditor");
			// GUI_Hierarchy*         hierarchy   = Manager_GUI.CreateOrLoad<GUI_Hierarchy>(L"Hierarchy");
			AHUD*       hud = Manager_Object.CreateOrLoad<AHUD>(L"HUD");
			ACharacter* pc  = Manager_Object.CreateOrLoad<ACharacter>(L"PC");

			UAudio* audio = Manager_Audio.CreateOrLoad(L"rsc/AudioClip/MUS_BotanicPanic.wav");
			// audio->Play(true);

			while (bIsRunning)
			{
				currentTime = mTimer->ElapsedMillis();

#pragma region Update Per 1 / 60 Seconds
				if (currentTime - updateTimer > TickFrequency)
				{
					// TODO: Update

					updateCounter++;
					updateTimer += TickFrequency;
				}
#pragma endregion

#pragma region Update Every Frame
				{
					FTimer frameTimer;
					{
						Update(mDeltaTime);
						// hud->UpdateFpsText(
						// 	std::format(L"FPS: {:d}, Time: {:.2f}", mFramesPerSec, mTimer->ElapsedSeconds()));

						Render();
					}
					frameCounter++;
					mDeltaTime = frameTimer.ElapsedSeconds();
				}
				mWindow->Update();

#pragma endregion

#pragma region Update Per Seconds
				if (mTimer->ElapsedSeconds() - timer > 1.f)
				{
					timer += 1.f;

					mFramesPerSec  = frameCounter;
					mUpdatesPerSec = updateCounter;

					frameCounter  = 0;
					updateCounter = 0;

					// TODO: Tick
				}
#pragma endregion

				if (mWindow->IsClosed())
				{
					bIsRunning = false;
				}
			}
		}

	}
}
