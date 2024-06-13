#include "Application_Base.h"

#include "AHUD.h"
#include "APawn.h"
#include "DXWrite.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "Renderer.h"
#include "UTextBlock.h"
#include "FTimer.h"
#include "Window.h"

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
		Logger::Initialize();

		Initialize_Internal();

		InputManager::Create();
		Renderer::Create(mWindowData, mWindow->GetHandle());

		ObjectManager::Get();
		ObjectManager::Initialize();
	}

	void Application_Base::Update(float DeltaTime)
	{
		InputManager::Get()->Update(DeltaTime);

		ObjectManager::Update(DeltaTime);
	}

	void Application_Base::Render()
	{
		Renderer::Clear();

		ObjectManager::Render();

		Renderer::Get()->Render();
	}

	void Application_Base::Release()
	{
		Renderer::Get()->Release();
	}

	void Application_Base::Initialize_Internal()
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

	void Application_Base::Run()
	{
		if (bIsInitialized)
		{
			int32_t frameCounter  = 0;
			int32_t updateCounter = 0;

			APawn* pc  = ObjectManager::Get().CreateObject<APawn>(L"PC");
			AHUD*              hud = ObjectManager::Get().CreateObject<AHUD>(L"HUD");

			while (bIsRunning)
			{
				mWindow->Clear();

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
						hud->UpdateFpsText(
							std::format(L"FPS: {:d}, Time: {:.2f}", mFramesPerSec, mTimer->ElapsedSeconds()));

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
