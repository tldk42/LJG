#include "Application_Base.h"

#include "DXWrite.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "Renderer.h"
#include "UObject.h"
#include "UTimer.h"
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

		ObjectManager::Initialize();
	}

	void Application_Base::Update(float DeltaTime)
	{
		InputManager::Get()->Update(DeltaTime);

		ObjectManager::Update(DeltaTime);
	}

	void Application_Base::Render()
	{
		// const std::wstring frameInfo = std::format(L"FPS: {:d}, Time: {:.2f}", mFramesPerSec, mTimer->ElapsedSeconds());
		// FpsText.get()->Text          = frameInfo;


		ObjectManager::Render();
		Renderer::Get()->Render();
	}

	void Application_Base::Release()
	{
		ObjectManager::Release();
		Renderer::Get()->Release();
	}

	void Application_Base::Initialize_Internal()
	{
		if (!bIsInitialized)
		{
			mWindow.reset(new Window(mWindowTitle, mWindowData));
			mTimer.reset(new UTimer());
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
			timer       = 0.f;
			updateTimer = mTimer->ElapsedMillis();

			int32_t frameCounter  = 0;
			int32_t updateCounter = 0;

			// FpsText                 = std::make_unique<FWriteData>();
			// FpsText.get()->RectSize = {0, 0, mWindowData.Width, mWindowData.Height};

			// DXWrite::AddText(std::move(FpsText));

			// FWriteData TestWriteData;
			// TestWriteData.RectSize = {300, 300, mWindowData.Width, mWindowData.Height};
			// TestWriteData.Text     = L"HELLO WORLD";
			// DXWrite::AddText(TestWriteData);

			while (bIsRunning)
			{
				mWindow->Clear();

				currentTime = mTimer->ElapsedMillis();

				if (currentTime - updateTimer > TickFrequency)
				{
					// TODO: Update

					updateCounter++;
					updateTimer += TickFrequency;
				}

				{
					UTimer frameTimer;

					Update(mDeltaTime);

					// TODO: Render
					Renderer::Get()->Clear();
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
