#include "Window.h"

#include "Context.h"
#include "EngineHelper.h"
#include "InputManager.h"

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

namespace LJG
{
	std::map<void*, Window*> Window::s_WindowHandles{};

	LRESULT CALLBACK WndProc(HWND HWnd, UINT Message, WPARAM WParam, LPARAM LParam)
	{
		Window* window = Window::GetWindow(HWnd);

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

	Window::~Window() {}

	bool Window::Initialize()
	{
		LOG_CORE_INFO("������ �ʱ�ȭ ����...");

		// Hinstance�� �����´�.
		// (������ winMain���� ù��° ���ڷ� �Ѱ� ������ ��Ŀ���� �����ϴ� __ImageBase �ĺ��ڸ� �̿��Ͽ� �̷������� ���� ���� �ִ�.
		// mInstanceHandle = reinterpret_cast<HINSTANCE>(GetModuleHandle(nullptr)); �� ����� �����Ѵ�.
		mInstanceHandle = reinterpret_cast<HINSTANCE>(&__ImageBase);


		WNDCLASS winClass{};
		winClass.hInstance     = mInstanceHandle;
		winClass.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		winClass.lpfnWndProc   = static_cast<WNDPROC>(WndProc);
		winClass.lpszClassName = L"Jacob Window";
		winClass.hCursor       = LoadCursor(nullptr, IDC_ARROW);
		winClass.hIcon         = LoadIcon(nullptr, IDI_WINLOGO);


		// WNDCLASS Ŀ�� ���
		if (FAILED(RegisterClass(&winClass)))
		{
			LOG_CORE_ERROR("%s %s", __FILE__, __LINE__);

			return false;
		}


		RECT  size  = {0, 0, mWindowData.Width, mWindowData.Height};
		DWORD style = WS_OVERLAPPED | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_BORDER;

		// �������� ũ�Ⱑ Ŭ���̾�Ʈ ������ �ǵ��� ����
		AdjustWindowRect(&size, style, false);

		mWindowHandle = CreateWindowEx(
			WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
			winClass.lpszClassName,
			mWindowTitle,
			WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
			// GetSystemMetrics�� �ý��� ���� ������ ��ȯ nIndex���� SM_���� �����ϴ� ������� �ִ´�. ex) 2560 x 1600 (���߾ӿ� ������)
			GetSystemMetrics(SM_CXSCREEN) / 2 - mWindowData.Width / 2,       // 1280 - 450 = 830 (��)
			GetSystemMetrics(SM_CYSCREEN) / 2 - mWindowData.Height / 2 - 40, // 800 - 300 = 500 (��)
			size.right + (-size.left),                                       // ������ ��: 900
			size.bottom + (-size.top),                                       // ������ ����: 600
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
		LOG_CORE_INFO("������ ���� �Ϸ�");

		ShowWindow(mWindowHandle, SW_SHOW);
		SetFocus(mWindowHandle);

		SetTitle(mWindowTitle);

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

	void ResizeCallback(Window* Window, UINT Width, UINT Height)
	{
		if (!Window->OnResize.empty())
		{
			for (ResizeDelegate& delegate : Window->OnResize)
			{
				delegate(Width, Height);
			}
		}
	}
}
