#pragma once
#include <string>
#include "../framework.h"

namespace LJG
{
	class System
	{
	public:
		System();
		~System() = default;

		System(const System&)  = delete;
		System(const System&&) = delete;

		bool Initialize();
		void Release();
		void Run();

		LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

	private:
		bool    Update();
		HRESULT CreateMainWindow();
		void    ExitWindow();

	private:
		// 프로그램 통합 이름
		static std::wstring AppName;

#pragma region Variables
		HINSTANCE mHinstance;
		HWND      mHwnd;

		class Graphics* mGraphics;
		class Input*    mInput;

		float mWindowWidth;
		float mWindowHeight;
#pragma endregion
	};

	static LRESULT CALLBACK MsgProc(HWND Hwnd, UINT Message, WPARAM WParam, LPARAM LParam);
	static System*          SYSTEM_INS = nullptr;
}
