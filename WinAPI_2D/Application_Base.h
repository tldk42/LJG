#pragma once
#include "CommonInclude.h"
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
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

#pragma region Application Handle
		void Start();
		void Pause();
		void Resume();
		void Stop();
#pragma endregion

	protected:
		virtual void Initialize_Internal();
		virtual void Run();

	protected:
#pragma region Window
		LPCWSTR     mWindowTitle;
		FWindowData mWindowData;
		Window*     mWindow;
#pragma endregion

#pragma region Time
		Utils::Timer* mTimer;
		FWriteData    FpsText;

		float_t mDeltaTime;
		float_t timer;
		float_t updateTimer;
		float_t currentTime;
		int32_t mFramesPerSec;
		int32_t mUpdatesPerSec;
#pragma endregion

#pragma region flag
		bool bIsInitialized;
		bool bIsRunning;
		bool bIsPaused;
#pragma endregion

	};
}
