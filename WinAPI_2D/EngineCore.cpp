#include "EngineCore.h"

#include "Context.h"
#include "InputManager.h"

namespace LJG
{
	EngineCore* EngineCore::s_Engine = nullptr;

	EngineCore::EngineCore(LPCWSTR WindowTitle, const FWindowData& WindowData)
		: Application_Base(WindowTitle, WindowData)
	{
	}

	void EngineCore::Initialize()
	{
		if (!s_Engine || !bIsInitialized)
		{
			Logger::Initialize();

			Initialize_Application();
			assert(mWindow);

			Context::Create(mWindowData, mWindow->GetHandle());
			InputManager::Initialize();

			s_Engine = this;
		}
	}

	void EngineCore::Update()
	{
	}

	void EngineCore::Render()
	{
	}

	void EngineCore::Release()
	{
	}

	void EngineCore::Run()
	{
		Application_Base::Run();
	}
}
