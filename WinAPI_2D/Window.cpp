#include "Window.h"
#include <imgui.h>
#include "DirectX/Context.h"
#include "Helper/EngineHelper.h"

EXTERN_C IMAGE_DOS_HEADER     __ImageBase;
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace LJG
{
	float_t g_GlobalScaleX = 1.0f;
	float_t g_GlobalScaleY = 1.0f;

	std::map<void*, Window*> Window::s_WindowHandles{};

	LRESULT CALLBACK WndProc(HWND HWnd, UINT Message, WPARAM WParam, LPARAM LParam)
	{
		Window* window = Window::GetWindow(HWnd);

		if (ImGui_ImplWin32_WndProcHandler(HWnd, Message, WParam, LParam))
			return true;

		if (window == nullptr)
			return DefWindowProc(HWnd, Message, WParam, LParam);

		switch (Message)
		{
		case WM_SIZE:
			ResizeCallback(window, LOWORD(LParam), HIWORD(LParam));
			break;
		case WM_CLOSE:
			DestroyWindow(HWnd);
			UnregisterClass(L"Jacob Window", nullptr);
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		}

		return DefWindowProc(HWnd, Message, WParam, LParam);
	}

	Window::Window(LPCWSTR WindowTitle, const FWindowData& WindowData)
		: mWindowHandle(nullptr),
		  mWindowTitle(WindowTitle),
		  mWindowData(WindowData),
		  bClosed(false)
	{
		if (!Initialize())
		{
			return;
		}
	}

	Window::~Window()
	{}

	bool Window::Initialize()
	{
		LOG_CORE_INFO("윈도우 초기화 시작...");

		// Hinstance를 가져온다.
		// (원래는 winMain에서 첫번째 인자로 넘겨 받지만 링커에서 제공하는 __ImageBase 식별자를 이용하여 이런식으로 구할 수도 있다.
		// mInstanceHandle = reinterpret_cast<HINSTANCE>(GetModuleHandle(nullptr)); 이 방법도 존재한다.
		mInstanceHandle = reinterpret_cast<HINSTANCE>(&__ImageBase);

		WNDCLASS winClass{};
		winClass.hInstance     = mInstanceHandle;
		winClass.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		winClass.lpfnWndProc   = static_cast<WNDPROC>(WndProc);
		winClass.lpszClassName = L"Jacob Window";
		winClass.hCursor       = LoadCursor(nullptr, IDC_ARROW);
		winClass.hIcon         = LoadIcon(nullptr, IDI_WINLOGO);


		// WNDCLASS 커널 등록
		if (FAILED(RegisterClass(&winClass)))
		{
			LOG_CORE_ERROR("%s %s", __FILE__, __LINE__);

			return false;
		}


		RECT  size  = {0, 0, mWindowData.Width, mWindowData.Height};
		DWORD style = WS_OVERLAPPED | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_BORDER;

		// 윈도우의 크기가 클라이언트 영역이 되도록 조정
		AdjustWindowRect(&size, style, false);

		mWindowHandle = CreateWindowEx(
			WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
			winClass.lpszClassName,
			mWindowTitle,
			WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
			// GetSystemMetrics는 시스템 설정 정보를 반환 nIndex에는 SM_으로 시작하는 상수값을 넣는다. ex) 2560 x 1600 (정중앙에 생성됨)
			GetSystemMetrics(SM_CXSCREEN) / 2 - mWindowData.Width / 2,       // 1280 - 450 = 830 (좌)
			GetSystemMetrics(SM_CYSCREEN) / 2 - mWindowData.Height / 2, // 800 - 300 = 500 (상)
			size.right + (-size.left),                                       // 윈도우 폭: 900
			size.bottom + (-size.top),                                       // 윈도우 높이: 600
			nullptr,
			nullptr,
			mInstanceHandle,
			nullptr
		);


		if (!mWindowHandle)
		{
			EngineHelper::ShowErrorMessageBox(mWindowHandle, true);
			LOG_CORE_ERROR("%s %s", __FILE__, __LINE__);
			return false;
		}

		RegisterWindowClass(mWindowHandle, this);
		LOG_CORE_INFO("윈도우 생성 완료");

		ShowWindow(mWindowHandle, SW_SHOW);
		SetFocus(mWindowHandle);

		SetTitle(mWindowTitle);

		OnResize.Bind([this](UINT Width, UINT Height){
			SetWindowSize(Width, Height);
		});

		return true;
	}

	void Window::RegisterWindowClass(void* Handle, Window* Window)
	{
		s_WindowHandles[Handle] = Window;
	}

	Window* Window::GetWindow(void* WindowHandle)
	{
		if (!WindowHandle)
		{
			return s_WindowHandles.begin()->second;
		}

		return s_WindowHandles[WindowHandle];
	}

	void Window::Update()
	{
		MSG message;

		while (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE) > 0)
		{
			if (message.message == WM_QUIT)
			{
				bClosed = true;
				return;
			}

			TranslateMessage(&message);
			DispatchMessage(&message);
		}
	}

	void Window::Clear() {}

	void Window::SetWindowSize(UINT InWidth, UINT InHeight)
	{
		mWindowData.Width  = InWidth;
		mWindowData.Height = InHeight;

		RECT  size  = {0, 0, mWindowData.Width, mWindowData.Height};
		DWORD style = WS_OVERLAPPED | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_BORDER;
		AdjustWindowRect(&size, style, false);
	}

	void ResizeCallback(Window* Window, UINT Width, UINT Height)
	{
		g_GlobalScaleX = static_cast<float_t>(Width) / static_cast<float_t>(GetWindowWidth());
		g_GlobalScaleY = static_cast<float_t>(Height) / static_cast<float_t>(GetWindowHeight());

		Window->OnResize.Execute(Width, Height);
	}
}
