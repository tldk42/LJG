#pragma once

#include "CommonInclude.h"

namespace LJG
{
	struct FAnimData;

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
}
