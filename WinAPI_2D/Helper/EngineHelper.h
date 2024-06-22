#pragma once

#include "HighLevelApp/Application_Base.h"
#include "CommonInclude.h"
#include "Window.h"

namespace LJG
{
	struct FAnimData_Deprecated;

	class EngineHelper
	{
	public:
		EngineHelper() = delete;

	public:
#pragma region Handle Error
		static void ShowMessageBox(HWND WindowHandle, LPCWSTR Text, LPCWSTR Title);
		static void ShowErrorMessageBox(HWND WindowHandle, bool bQuit);
#pragma endregion

		static HWND GetWindowHandle(void* WindowHandle = nullptr);
	};

	inline HWND GetHWND(void* WindowHandle = nullptr)
	{
		return Window::GetWindow(WindowHandle)->GetHandle();
	}

	inline uint32_t GetWindowWidth(void* WindowHandle = nullptr)
	{
		return Window::GetWindow(WindowHandle)->GetWidth();
	}

	inline uint32_t GetWindowHeight(void* WindowHandle = nullptr)
	{
		return Window::GetWindow(WindowHandle)->GetHeight();
	}

	inline bool IsFullScreen(void* WindowHandle = nullptr)
	{
		return Window::GetWindow(WindowHandle)->IsFullScreen();
	}

	inline bool IsVsyncEnabled(void* WindowHandle = nullptr)
	{
		return Window::GetWindow(WindowHandle)->IsVsyncEnabled();
	}

	inline float_t GetDeltaSeconds()
	{
		return Application_Base::Get().GetDeltaSeconds();
	}
}
