#pragma once

#include <nlohmann/json.hpp>

#include "HighLevelApp/Application.h"
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

		static nlohmann::json LoadFile(const WText& InFileName)
		{
			std::ifstream file(InFileName + L".json", std::ios::in);
			if (std::filesystem::exists(InFileName + L".json"))
			{
				nlohmann::json jsonData;
				file >> jsonData;
				file.close();

				return jsonData;
			}
			return nullptr;
		}
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
		return App.GetDeltaSeconds();
	}

	inline int32_t GetFramePerSeconds()
	{
		return App.GetFramePerSeconds();
	}

	template <typename EnumType>
	inline uint8_t EnumAsByte(EnumType value)
	{
		return static_cast<uint8_t>(value);
	}

	/** UObject 유효성 검사 */
	template <typename T>
	inline bool IsValid(T ValuePtr)
	{
		return ValuePtr != nullptr;
	}

	inline WText Text2WText(const Text& InString)
	{
		USES_CONVERSION;
		return WText(A2W(InString.c_str()));
	}

	inline Text WText2Text(const WText& InWString)
	{
		USES_CONVERSION;
		return Text(W2A(InWString.c_str()));
	}
}
