#pragma once
#include "CommonInclude.h"

namespace LJG
{
	class Window
	{
	public:
		/**
		 * 기본 생성자로는 윈도우를 만들지 못하게 막아둔다.
		 */
		Window() = delete;
		/**
		 * 새로운 윈도우 생성을 시도
		 * @param WindowTitle 새 윈도우 제목
		 * @param WindowData 윈도우데이터 구조체
		 */
		Window(LPCWSTR WindowTitle, const FWindowData& WindowData);
		~Window();

	private:
		bool Initialize();

	public:
		static void    RegisterWindowClass(void* Handle, Window* Window);
		static Window* GetWindow(void* WindowHandle = nullptr);

	public:
		void Run();
		void Update();
		void Clear();

#pragma region Get
		inline HWND    GetHandle() const { return mWindowHandle; }
		inline int32_t GetWidth() const { return mWindowData.Width; }
		inline int32_t GetHeight() const { return mWindowData.Height; }
		inline int32_t GetResolutionWidth() const { return mResolutionWidth; }
		inline int32_t GetResolutionHeight() const { return mResolutionHeight; }
		inline bool    IsFullScreen() const { return mWindowData.bFullScreen; }
		inline bool    IsVsyncEnabled() const { return mWindowData.bVsync; }
		inline bool    IsClosed() const { return bClosed; }
#pragma endregion

#pragma region Set
		inline void SetTitle(LPCTSTR InTitle) { mWindowTitle = InTitle; }
		inline void SetVSync(const bool bEnable) { mWindowData.bVsync = bEnable; }
#pragma endregion

	private:
		HINSTANCE   mInstanceHandle;
		HWND        mWindowHandle;
		LPCWSTR     mWindowTitle;
		FWindowData mWindowData;
		bool        bClosed;

		int mResolutionWidth;
		int mResolutionHeight;

	private:
		static std::map<void*, Window*> s_WindowHandles;

		friend LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
		friend void             ResizeCallback(Window* Window, int Width, int Height);
	};
}
