#include "System/System.h"
#include "Graphics/Graphics.h"


namespace LJG
{
	std::wstring System::AppName = L"DX11 Sample";

	System::System()
		: mHinstance(nullptr),
		  mHwnd(nullptr),
		  mGraphics(nullptr),
		  mInput(nullptr),
		  mWindowWidth(0),
		  mWindowHeight(0)
	{
	}

	bool System::Initialize()
	{
		CreateMainWindow();
	}

	void System::Release()
	{
		ExitWindow();
	}

	void System::Run()
	{
		MSG* message;
		ZeroMemory(&message, sizeof(MSG));

		while (message->message != WM_QUIT)
		{
			if (PeekMessage(message, nullptr, 0U, 0U, PM_REMOVE))
			{
				TranslateMessage(message);
				DispatchMessage(message);
			}
			else
			{
				Update();
			}
		}
	}

	LRESULT System::MessageHandler(HWND Hwnd, UINT Message, WPARAM WParam, LPARAM LParam)
	{
		switch (Message)
		{
		case WM_SIZE:
			break;
		case WM_COMMAND:
			break;
		case WM_PAINT:
			PAINTSTRUCT paintstruct;
			HDC hdc = BeginPaint(mHwnd, &paintstruct);
			EndPaint(mHwnd, &paintstruct);

			break;
		case WM_KEYDOWN:
			mInput->KeyDown(wParam);
			break;
		case WM_KEYUP:
			mInput->KeyUp(wParam);
			break;
		default:
			return DefWindowProc(Hwnd, Message, WParam, LParam);
		}
	}

	bool System::Update()
	{
		// �Է� ó��
		if ()

			// ������ ó��
			if (FAILED(mGraphics->Render()))
			{
			}

		return true;
	}

	HRESULT System::CreateMainWindow()
	{
		SYSTEM_INS = this;

		// ������ Ŭ���� ���
		WNDCLASSEX wcx;
		// ������ ���� ���� �ʱ�ȭ
		wcx.cbSize      = sizeof(wcx);
		wcx.style       = CS_HREDRAW | CS_VREDRAW; // ������ ����� �ٽ� �׷���
		wcx.lpfnWndProc = MsgProc;                 // ������ ���ν��� ������
		wcx.cbClsExtra  = 0;                       // Ŭ���� �߰� �޸�
		wcx.cbWndExtra  = 0;                       // ������ �߰� �޸�
		wcx.hInstance   = mHinstance;              // �ڵ� �ν��Ͻ�

		wcx.hIcon         = nullptr;
		wcx.hCursor       = LoadCursor(nullptr, IDC_ARROW);
		wcx.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));

		wcx.lpszMenuName  = nullptr;
		wcx.lpszClassName = AppName.c_str();
		wcx.hIconSm       = nullptr;

		if (FAILED(RegisterClassEx(&wcx)))
		{
			return FALSE;
		}

		// â ��Ÿ�� ����
		constexpr DWORD style = FULL_SCREEN
			                        ? (WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP)
			                        : WS_OVERLAPPEDWINDOW;

		// ������ â ����
		mHwnd = CreateWindow(
			AppName.c_str(),
			AppName.c_str(),
			style,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			mWindowWidth,
			mWindowHeight,
			GetDesktopWindow(),
			nullptr,
			mHinstance,
			nullptr);

		if (!mHwnd)
		{
			return FALSE;
		}

		if (!FULL_SCREEN)
		{
			// ���� Ŭ���̾�Ʈ ����
			RECT clientRect;
			GetClientRect(mHwnd, &clientRect);

			// ���� ũ��� Ÿ��Ʋ�� �׵θ��� ���ԵǹǷ� �ٽ� ���.
			MoveWindow(mHwnd,
			           0,
			           0,
			           mWindowWidth + (mWindowWidth - clientRect.right),
			           mWindowHeight + (mWindowHeight - clientRect.bottom),
			           TRUE);
		}

		return TRUE;
	}

	void System::ExitWindow()
	{
	}

	LRESULT WINAPI MsgProc(HWND Hwnd, UINT Message, WPARAM WParam, LPARAM LParam)
	{
	}
}
