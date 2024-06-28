#pragma once
#include "CommonInclude.h"
#include "Component/Manager/Manager.h"

namespace LJG
{
	#define App Application::Get()

	class Application : public ICoreAPI, public TSingleton<Application>
	{
	public:
		explicit Application(LPCWSTR WindowTitle, const FWindowData& WindowData);

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

	public:
		[[nodiscard]] float_t GetDeltaSeconds() const { return mDeltaTime; }
		[[nodiscard]] int32_t GetFramePerSeconds() const { return mFramesPerSec; }

	protected:
		virtual void Initialize_Application();
		virtual void Run();

	protected:
#pragma region Window
		LPCWSTR     mWindowTitle;
		FWindowData mWindowData;
		WindowUPtr  mWindow;
#pragma endregion

#pragma region Time
		FTimerUPtr mTimer;

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

	private:
		friend class TSingleton<Application>;

		Application();
		~Application() override;

	public:
		Application(const Application&)            = delete;
		Application& operator=(const Application&) = delete;
	};
}
