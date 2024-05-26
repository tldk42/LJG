#include "App.h"

#include "Timer.h"

namespace LJG
{
	App::App(LPCWSTR WindowTitle, const FWindowData& WindowData)
		: mWindowTitle(WindowTitle),
		  mWindowData(WindowData),
		  mWindow(nullptr),
		  mTimer(nullptr),
		  bIsInitialized(false),
		  bIsRunning(false),
		  bIsPaused(false) {}

	App::~App()
	{
		if (mWindow)
		{
			mWindow->Clear();
			delete mWindow;
			mWindow = nullptr;
		}
	}

	void App::Initialize()
	{
		if (!bIsInitialized)
		{
			mWindow        = new Window(mWindowTitle, mWindowData);
			bIsInitialized = true;
		}
	}

	void App::Start()
	{
		Initialize();

		bIsRunning = true;
		bIsPaused  = false;

		Run();
	}

	void App::Pause()
	{
		bIsPaused = true;
	}

	void App::Resume()
	{
		bIsPaused = false;
	}

	void App::Stop()
	{
		bIsRunning = true;
	}

	void App::Run()
	{
		if (bIsInitialized)
		{
			mTimer = new Utils::Timer;

			float timer       = 0.f;
			float updateTimer = mTimer->ElapsedMillis();
			float currentTime;

			int32_t frameCounter  = 0;
			int32_t updateCounter = 0;

			while (bIsRunning)
			{
				mWindow->Clear();

				currentTime = mTimer->ElapsedMillis();

				if (currentTime - updateTimer > Utils::TickFrequency)
				{
					// TODO: Update

					updateCounter++;
					updateTimer += Utils::TickFrequency;
				}

				{
					Utils::Timer frameTimer;
					// TODO: Render

					frameCounter++;
					mDeltaTime = frameTimer.ElapsedMillis();
				}

				mWindow->Update();

				if (mTimer->ElapsedSeconds() - timer > 1.f)
				{
					timer += 1.f;

					mFramesPerSec  = frameCounter;
					mUpdatesPerSec = updateCounter;

					frameCounter  = 0;
					updateCounter = 0;

					// TODO: Tick
					LOG_CORE_TRACE("Å¸ÀÌ¸Ó: {:1.0f}", timer);
				}

				if (mWindow->IsClosed())
				{
					bIsRunning = false;
				}
			}
		}
	}
}
