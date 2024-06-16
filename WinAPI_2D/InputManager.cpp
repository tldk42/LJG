#include "InputManager.h"
#include "Helper/EngineHelper.h"


namespace LJG
{
	InputManager::InputManager()
		: mMousePosition(), bEnableDebug(false)
	{
		#ifdef _DEBUG
		bEnableDebug = true;
		#endif
	}

	void InputManager::Initialize()
	{
		Get().CreateKeys();

		Get().ClearKeys();
		Get().ClearMouse();
	}

	void InputManager::Update(float DeltaTime)
	{
		Get().UpdateKeys();
		Get().UpdateMouseWindowPosition();

		Get().Debug_Input();
	}


	void InputManager::CreateKeys()
	{
		mKeys.clear();
		mKeys.reserve(static_cast<UINT>(EKeyCode::End));

		for (size_t i = 0; i < static_cast<UINT>(EKeyCode::End); ++i)
		{
			mKeys.emplace_back(static_cast<EKeyCode>(i), EKeyState::None, false);
		}
	}

	void InputManager::UpdateKeys()
	{
		for (FKeyData& key : mKeys)
		{
			UpdateKey(key);
		}
	}

	void InputManager::UpdateKey(FKeyData& InKey)
	{
		if (GetFocus()) // ���� �����쿡 ��Ŀ�� ��?
		{
			IsKeyDown_Implements(InKey.KeyCode) ? UpdateKeyDown(InKey) : UpdateKeyUp(InKey);
		}
		else // ��Ŀ���� �ٸ� �����쿡 ������ ��� Input Clear
		{
			ClearKeys();
		}
	}

	void InputManager::UpdateKeyDown(FKeyData& InKey)
	{
		if (InKey.State <= EKeyState::Up)
		{
			InKey.State     = EKeyState::Down;
			InKey.PressTime = steady_clock::now();
		}
		else
		{
			InKey.State         = EKeyState::Pressed;
			InKey.PressDuration = std::chrono::duration_cast<milliseconds>(
				steady_clock::now() - InKey.PressTime);
		}
		InKey.bPressed = true;
	}

	void InputManager::UpdateKeyUp(FKeyData& InKey)
	{
		if (InKey.State == EKeyState::Pressed)
		{
			InKey.State         = EKeyState::Up;
			InKey.ReleaseTime   = steady_clock::now(); // TODO Release �ʿ��ϸ� ����
			InKey.PressDuration = milliseconds(0);
		}
		else
		{
			InKey.State = EKeyState::None;
		}
		InKey.bPressed = false;
	}

	void InputManager::UpdateMouseWindowPosition()
	{
		const HWND WindowHandle = GetHWND();

		POINT mousePoint;
		GetCursorPos(&mousePoint);                 // Ŀ�� ��ǥ �޾ƿ���
		ScreenToClient(WindowHandle, &mousePoint); // Ŀ���� ��ǥ�� Ŭ���̾�Ʈ ������ �������� ����ش�.

		mMousePosition.X = mousePoint.x;
		mMousePosition.Y = mousePoint.y;
	}

	void InputManager::ClearKeys()
	{
		for (FKeyData& key : mKeys)
		{
			switch (key.State)
			{
			case EKeyState::Down:
			case EKeyState::Pressed:
				key.State = EKeyState::Up;
				break;
			case EKeyState::Up:
				key.State = EKeyState::None;
				break;
			case EKeyState::None:
				break;
			}

			key.PressDuration = std::chrono::milliseconds(0);
			key.bPressed      = false;
		}
	}

	void InputManager::ClearMouse()
	{
		mMousePosition = FVector2f::UnitVector;
	}

	bool InputManager::IsKeyDown_Implements(const EKeyCode InKey)
	{
		return GetAsyncKeyState(ASCII[static_cast<UINT>(InKey)]) & 0x8000;
	}

	void InputManager::Debug_Input() const
	{
		if (bEnableDebug)
		{
			for (const FKeyData& key : mKeys)
			{
				if (key.PressDuration.count() > 0)
				{
					std::cout << "Key " << ASCIIString[static_cast<int>(key.KeyCode)] << " was pressed for " <<
					key.PressDuration.count() * (1.f / 1000.f) << " seconds\n";
				}
			}
		}
	}
}
