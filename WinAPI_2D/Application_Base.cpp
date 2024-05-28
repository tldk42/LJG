#include "Application_Base.h"

#include "Context.h"
#include "InputManager.h"
#include "Renderer.h"
#include "Timer.h"

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
	}

	Application_Base::~Application_Base()
	{
		if (mWindow)
		{
			mWindow->Clear();
			delete mWindow;
			mWindow = nullptr;
		}
	}

	void Application_Base::Initialize()
	{
		Logger::Initialize();

		Initialize_Application();

		InputManager::Create();
		Renderer::Create(mWindowData, mWindow->GetHandle());
	}

	void Application_Base::Update()
	{
	}

	void Application_Base::Render()
	{
		Renderer::GetRenderer()->Render();
	}

	void Application_Base::Release()
	{
	}

	void Application_Base::Initialize_Application()
	{
		if (!bIsInitialized)
		{
			mWindow        = new Window(mWindowTitle, mWindowData);
			bIsInitialized = true;
		}
	}

	void Application_Base::Start()
	{
		bIsRunning = true;
		bIsPaused  = false;

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
					Update();

					updateCounter++;
					updateTimer += Utils::TickFrequency;
				}

				{
					Utils::Timer frameTimer;
					// TODO: Render
					Render();

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
