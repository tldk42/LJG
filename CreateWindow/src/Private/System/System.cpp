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
		// 입력 처리
		if ()

			// 렌더링 처리
			if (FAILED(mGraphics->Render()))
			{
			}

		return true;
	}

	HRESULT System::CreateMainWindow()
	{
		SYSTEM_INS = this;

		// 윈도우 클래스 등록
		WNDCLASSEX wcx;
		// 윈도우 관련 변수 초기화
		wcx.cbSize      = sizeof(wcx);
		wcx.style       = CS_HREDRAW | CS_VREDRAW; // 사이즈 변경시 다시 그려짐
		wcx.lpfnWndProc = MsgProc;                 // 윈도우 프로시저 포인터
		wcx.cbClsExtra  = 0;                       // 클래스 추가 메모리
		wcx.cbWndExtra  = 0;                       // 윈도우 추가 메모리
		wcx.hInstance   = mHinstance;              // 핸들 인스턴스

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

		// 창 스타일 지정
		constexpr DWORD style = FULL_SCREEN
			                        ? (WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP)
			                        : WS_OVERLAPPEDWINDOW;

		// 윈도우 창 생성
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
			// 순수 클라이언트 영역
			RECT clientRect;
			GetClientRect(mHwnd, &clientRect);

			// 실제 크기는 타이틀과 테두리가 포함되므로 다시 계산.
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
