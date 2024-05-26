#include "InputManager.h"

#include "EngineHelper.h"
#include "Math/Vector2D.h"


namespace LJG
{
	std::vector<Key> InputManager::s_Keys          = {};
	FVector2D        InputManager::s_MousePosition = {};

	void InputManager::Initialize()
	{
		CreateKeys();
		// ClearKeys();
		// ClearMouse();
	}

	void InputManager::Update()
	{
		UpdateKeys();
		UpdateMouseWindowPosition();
	}

	void InputManager::SetMousePosition(const FVector2D& Position) {}

	void InputManager::CreateKeys()
	{
		s_Keys.clear();
		s_Keys.reserve(static_cast<UINT>(EKeyCode::End));

		for (size_t i = 0; i < static_cast<UINT>(EKeyCode::End); ++i)
		{
			s_Keys.emplace_back(static_cast<EKeyCode>(i), EKeyState::None, false);
		}
	}

	void InputManager::UpdateKeys()
	{
		for (Key& key : s_Keys)
		{
			UpdateKey(key);
		}
	}

	void InputManager::UpdateKey(Key& InKey)
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

	void InputManager::UpdateKeyDown(Key& InKey)
	{
		InKey.State    = (InKey.State == EKeyState::Pressed) ? EKeyState::Pressed : EKeyState::Down;
		InKey.bPressed = true;
	}

	void InputManager::UpdateKeyUp(Key& InKey)
	{
		InKey.State    = (InKey.State == EKeyState::Pressed) ? EKeyState::Up : EKeyState::None;
		InKey.bPressed = false;
	}

	void InputManager::UpdateMouseWindowPosition()
	{
		const HWND WindowHandle = EngineHelper::GetWindowHandle();
		if (!WindowHandle)
		{
			LOG_CORE_FATAL("Window Handle ��ȯ ����");
			return;
		}

		POINT mousePoint;
		GetCursorPos(&mousePoint); // Ŀ�� ��ǥ �޾ƿ���
		ScreenToClient(WindowHandle, &mousePoint); // Ŀ���� ��ǥ�� Ŭ���̾�Ʈ ������ �������� ����ش�.

		s_MousePosition.X = mousePoint.x;
		s_MousePosition.Y = mousePoint.y;
	}

	void InputManager::ClearKeys()
	{
		for (Key& key : s_Keys)
		{
			switch (key.State)
			{
			case EKeyState::Down:
			case EKeyState::Pressed:
				key.State = EKeyState::Up;
				break;
			case EKeyState::Up:
				key.State = EKeyState::None;
			case EKeyState::None:
				break;
			}

			key.bPressed = false;
		}
	}

	void InputManager::ClearMouse() {}

	bool InputManager::IsKeyDown_Implements(const EKeyCode InKey)
	{
		return GetAsyncKeyState(ASCII[static_cast<UINT>(InKey)]) & 0x8000;
	}
}
