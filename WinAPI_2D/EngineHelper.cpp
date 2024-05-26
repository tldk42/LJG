#include "EngineHelper.h"

namespace LJG
{
	void EngineHelper::ShowMessageBox(HWND WindowHandle, LPCWSTR Text, LPCWSTR Title)
	{
		if (WindowHandle)
		{
			MessageBox(WindowHandle, Text, Title, MB_OK | MB_ICONINFORMATION);
		}
	}

	void EngineHelper::ShowErrorMessageBox(HWND WindowHandle, bool bQuit)
	{
		LPVOID lpMsgBuf = nullptr;

		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
			nullptr, GetLastError(), 0,
			(LPTSTR)&lpMsgBuf, 0, nullptr);

		MessageBox(WindowHandle, static_cast<LPCTSTR>(lpMsgBuf), TEXT("Error"), MB_OK | MB_ICONERROR);

		LocalFree(lpMsgBuf);
		if (bQuit)
		{
			PostQuitMessage(GetLastError());
		}
	}

	HWND EngineHelper::GetWindowHandle(void* WindowHandle)
	{
		return Window::GetWindow(WindowHandle)->GetHandle();
	}
}
