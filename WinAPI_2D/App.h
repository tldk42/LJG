#pragma once
#include "Timer.h"
#include "Window.h"

namespace LJG
{
	class App
	{
	public:
		App() = delete;
		explicit App(LPCWSTR WindowTitle, const FWindowData& WindowData);
		virtual  ~App();

		virtual void Initialize();

	public:
		void Start();
		void Pause();
		void Resume();
		void Stop();

	private:
		void Run();

	private:
		LPCWSTR     mWindowTitle;
		FWindowData mWindowData;
		Window*     mWindow;

		Utils::Timer* mTimer;
		float_t       mDeltaTime;
		int32_t       mFramesPerSec;
		int32_t       mUpdatesPerSec;

		bool bIsInitialized;
		bool bIsRunning;
		bool bIsPaused;
	};
}
