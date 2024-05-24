#include "Window.h"

#include "Context.h"
#include "EngineHelper.h"

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

namespace LJG
{
	std::map<void*, Window*> Window::s_WindowHandles{};

	LRESULT CALLBACK WndProc(HWND HWnd, UINT Message, WPARAM WParam, LPARAM LParam)
	{
		LRESULT result = NULL;

		Window* window = Window::GetWindow(HWnd);

		if (window == nullptr)
			return DefWindowProc(HWnd, Message, WParam, LParam);
		switch (Message)
		{
		case WM_SETFOCUS:
			break;
		case WM_KILLFOCUS:
			break;
		case WM_CLOSE:
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_KEYDOWN:
		case WM_KEYUP:
		case WM_SYSKEYDOWN:
		case WM_SYSKEYUP:
			break;
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
		case WM_MBUTTONDOWN:
		case WM_MBUTTONUP:
			break;
		case WM_SIZE:
			ResizeCallback(window, LOWORD(LParam), HIWORD(LParam));
			break;
		default:
			result = DefWindowProc(HWnd, Message, WParam, LParam);
		}

		return result;
	}

	Window::Window(LPCWSTR WindowTitle, const FWindowData& WindowData)
		: mWindowHandle(nullptr),
		  mWindowTitle(WindowTitle),
		  mWindowData(WindowData),
		  bClosed(false)
	{
		mResolutionWidth  = mWindowData.Width;
		mResolutionHeight = mWindowData.Height;

		if (!Initialize())
		{
			return;
		}
	}

	Window::~Window()
	{
	}

	bool Window::Initialize()
	{
		Logger::Initialize();
		LOG_CORE_INFO("윈도우 초기화 시작...");

		mInstanceHandle = reinterpret_cast<HINSTANCE>(&__ImageBase);

		WNDCLASS winClass{};
		winClass.hInstance     = mInstanceHandle;
		winClass.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		winClass.lpfnWndProc   = static_cast<WNDPROC>(WndProc);
		winClass.lpszClassName = L"Cobra Engine";
		winClass.hCursor       = LoadCursor(nullptr, IDC_ARROW);
		winClass.hIcon         = LoadIcon(nullptr, IDI_WINLOGO);

		if (FAILED(RegisterClass(&winClass)))
		{
			EngineHelper::ShowErrorMessageBox(mWindowHandle, true);
			LOG_CORE_ERROR("%s %s", __FILE__, __LINE__);

			return false;
		}


		RECT  size  = {0, 0, mWindowData.Width, mWindowData.Height};
		DWORD style = WS_OVERLAPPED | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_BORDER;

		AdjustWindowRect(&size, style, false);
		// TODO: 한글 처리 
		mWindowHandle = CreateWindowEx(
			WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
			winClass.lpszClassName,
			mWindowTitle,
			WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
			GetSystemMetrics(SM_CXSCREEN) / 2 - mWindowData.Width / 2,
			GetSystemMetrics(SM_CYSCREEN) / 2 - mWindowData.Height / 2 - 40,
			// TODO: This requires some... attention
			size.right + (-size.left), size.bottom + (-size.top),
			nullptr,
			nullptr,
			mInstanceHandle,
			nullptr
		);

		if (!mWindowHandle)
		{
			LOG_CORE_ERROR("%s %s", __FILE__, __LINE__);
			return false;
		}

		RegisterWindowClass(mWindowHandle, this);

		LOG_CORE_INFO("윈도우 생성 완료");

		ShowWindow(mWindowHandle, SW_SHOW);
		SetFocus(mWindowHandle);

		SetTitle(mWindowTitle);


		Context::Create(mWindowData, mWindowHandle);

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

	void Window::Run()
	{
		while (!bClosed)
		{
			Update();
			Context::Get()->Present();
		}
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

	void Window::Clear()
	{
	}

	void ResizeCallback(Window* Window, int Width, int Height)
	{
	}
}
