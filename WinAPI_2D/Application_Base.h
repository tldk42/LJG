#pragma once
#include "Timer.h"
#include "Window.h"

namespace LJG
{
	class Application_Base : public ICoreAPI
	{
	public:
		Application_Base() = delete;
		explicit Application_Base(LPCWSTR WindowTitle, const FWindowData& WindowData);
		virtual  ~Application_Base();

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update() override;
		void Render() override;
		void Release() override;
#pragma endregion

		void Start();
		void Pause();
		void Resume();
		void Stop();

	protected:
		virtual void Initialize_Application();
		virtual void Run();

	protected:
#pragma region Window
		LPCWSTR     mWindowTitle;
		FWindowData mWindowData;
		Window*     mWindow;
#pragma endregion

#pragma region Time
		Utils::Timer* mTimer;
		float_t       mDeltaTime;
		int32_t       mFramesPerSec;
		int32_t       mUpdatesPerSec;
#pragma endregion

#pragma region Properties
		bool bIsInitialized;
		bool bIsRunning;
		bool bIsPaused;
#pragma endregion
	};
}
