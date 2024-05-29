#pragma once
#include "CommonInclude.h"

namespace LJG
{
	class Window
	{
	public:
		Window() = delete;
		Window(LPCWSTR WindowTitle, const FWindowData& WindowData);
		virtual ~Window();

	private:
		bool Initialize();

	private:
		static void RegisterWindowClass(void* Handle, Window* Window);

	public:
		static Window* GetWindow(void* WindowHandle = nullptr);
		void           AddResizeCallback(ResizeDelegate Function);

	public:
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

		std::vector<ResizeDelegate> OnResize;

		int mResolutionWidth;
		int mResolutionHeight;

	private:
		static std::map<void*, Window*> s_WindowHandles;

		friend LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
		friend void             ResizeCallback(Window* Window, UINT Width, UINT Height);
	};
}
