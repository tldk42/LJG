#pragma once
#include <Windows.h>

namespace LJG
{
	class Window
	{
	public:
		bool InitializeWindow(HINSTANCE hInstance);

		virtual void Run();

	protected:
		void CreateRegisterClass();
		HWND CreateWin(HINSTANCE hInstance, int nCmdShow);

	private:
		HINSTANCE mHinstance;
		HWND      mHwnd;
	};

}
