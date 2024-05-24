#pragma once
#include "CommonInclude.h"

namespace LJG
{
	class Window
	{
	public:
		/**
		 * �⺻ �����ڷδ� �����츦 ������ ���ϰ� ���Ƶд�.
		 */
		Window() = delete;
		/**
		 * ���ο� ������ ������ �õ�
		 * @param WindowTitle �� ������ ����
		 * @param WindowData �����쵥���� ����ü
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
