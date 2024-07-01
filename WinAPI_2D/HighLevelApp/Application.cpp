#include "Application.h"

#include "InputManager.h"
#include "Renderer.h"
#include "FTimer.h"
#include "Window.h"
#include "GUI/GUI_MapEditor.h"
#include "World/World.h"

extern LJG::FWindowData testWindowData;

namespace LJG
{
	Application::Application(LPCWSTR WindowTitle, const FWindowData& WindowData)
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
		Application::Initialize();
	}

	Application::Application()
		: mWindowTitle(L"Cuphead 모작"),
		  mWindowData(testWindowData),
		  mWindow(nullptr),
		  mTimer(nullptr),
		  mDeltaTime(0),
		  mFramesPerSec(0),
		  mUpdatesPerSec(0),
		  bIsInitialized(false),
		  bIsRunning(false),
		  bIsPaused(false)
	{}

	Application::~Application()
	{
		Application::Release();
	}

	void Application::Initialize()
	{
		// Logger를 가장 먼저 초기화 해야 함 다른 초기화중에 Logger를 사용
		Logger::Initialize();

		// 무조건 Device를 생성전에 Window Handle Instance를 반환해야 함 
		Initialize_Application();

		Renderer::Initialize();

		GWorld.Initialize();
	}

	void Application::Update(float DeltaTime)
	{
		GWorld.Update(DeltaTime);

		Renderer::Update(DeltaTime);
	}

	void Application::Render()
	{
		Renderer::Clear(FLinearColor::Gallary);

		GWorld.Render();

		Renderer::Render();
	}

	void Application::Release()
	{
		GWorld.Release();
		Renderer::Release();
	}

	void Application::Initialize_Application()
	{
		if (!bIsInitialized)
		{
			mWindow.reset(new Window(mWindowTitle, mWindowData));
			mTimer.reset(new FTimer());

			bIsInitialized = true;
		}
	}

	void Application::Start()
	{
		if (!bIsInitialized)
			Application::Initialize();

		bIsRunning = true;
		bIsPaused  = false;

		timer       = 0.f;
		updateTimer = mTimer->ElapsedMillis();

			Run();
	}

	void Application::Pause()
	{
		bIsPaused = true;
	}

	void Application::Resume()
	{
		bIsPaused = false;
	}

	void Application::Stop()
	{
		bIsRunning = true;
	}

	void Application::Run()
	{
		if (bIsInitialized)
		{
			int32_t frameCounter  = 0;
			int32_t updateCounter = 0;

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
