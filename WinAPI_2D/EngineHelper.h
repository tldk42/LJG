#pragma once

#include "CommonInclude.h"

namespace LJG
{
	class EngineHelper
	{
	public:
		EngineHelper() = delete;

	public:
		static void ShowMessageBox(HWND WindowHandle, LPCWSTR Text, LPCWSTR Title);
		static void ShowErrorMessageBox(HWND WindowHandle, bool bQuit);
	};
}
