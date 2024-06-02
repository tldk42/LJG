#include "Application_Base.h"

#include "Context.h"
#include "DXWrite.h"
#include "InputManager.h"
#include "Renderer.h"
#include "Timer.h"
#include "Vertex.h"

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

		Initialize_Internal();

		InputManager::Create();
		Renderer::Create(mWindowData, mWindow->GetHandle());
	}

	void Application_Base::Update() {}

	void Application_Base::Render()
	{
		std::wstring frameInfo = std::format(L"FPS: {:d}, Time: {:.2f}", mFramesPerSec, mTimer->ElapsedSeconds());
		FpsText.Text           = frameInfo;

		Renderer::GetRenderer()->Render();
	}

	void Application_Base::Release() {}

	void Application_Base::Initialize_Internal()
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

			timer       = 0.f;
			updateTimer = mTimer->ElapsedMillis();

			int32_t frameCounter  = 0;
			int32_t updateCounter = 0;

			FpsText.RectSize = {0, 0, mWindowData.Width, mWindowData.Height};

			DXWrite::AddText(FpsText);

			Vertex testVert;
			testVert.Initialize();

			while (bIsRunning)
			{
				mWindow->Clear();

				currentTime = mTimer->ElapsedMillis();

				if (currentTime - updateTimer > Utils::TickFrequency)
				{
					// TODO: Update
					testVert.Update();
					Update();

					updateCounter++;
					updateTimer += Utils::TickFrequency;
				}

				{
					Utils::Timer frameTimer;
					// TODO: Render
					Renderer::GetRenderer()->Clear();
					testVert.Render();
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
				}

				if (mWindow->IsClosed())
				{
					bIsRunning = false;
				}
			}
		}
	}
}
