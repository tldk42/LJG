#include "InputManager.h"

#include "EngineHelper.h"
#include "Math/Vector2D.h"


namespace LJG
{
	InputManagerUPtr InputManager::s_InputManager = nullptr;

	InputManager::InputManager()
		: mMousePosition() {}

	void InputManager::Create()
	{
		if (!s_InputManager)
		{
			s_InputManager.reset(new InputManager());
			assert(s_InputManager);

			s_InputManager->Initialize();
		}
	}

	void InputManager::Initialize()
	{
		CreateKeys();
		ClearKeys();
		ClearMouse();
	}

	void InputManager::Update(float DeltaTime)
	{
		UpdateKeys();
		UpdateMouseWindowPosition();
	}

	void InputManager::Render() {}

	void InputManager::Release() {}

	void InputManager::SetMousePosition(const FVector2D& Position) {}

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
		if (GetFocus()) // 현재 윈도우에 포커싱 중?
		{
			IsKeyDown_Implements(InKey.KeyCode) ? UpdateKeyDown(InKey) : UpdateKeyUp(InKey);
		}
		else // 포커싱이 다른 윈도우에 있으면 모든 Input Clear
		{
			ClearKeys();
		}
	}

	void InputManager::UpdateKeyDown(FKeyData& InKey)
	{
		InKey.State    = (InKey.State == EKeyState::Pressed) ? EKeyState::Pressed : EKeyState::Down;
		InKey.bPressed = true;
	}

	void InputManager::UpdateKeyUp(FKeyData& InKey)
	{
		InKey.State    = (InKey.State == EKeyState::Pressed) ? EKeyState::Up : EKeyState::None;
		InKey.bPressed = false;
	}

	void InputManager::UpdateMouseWindowPosition()
	{
		const HWND WindowHandle = EngineHelper::GetWindowHandle();
		if (!WindowHandle)
		{
			LOG_CORE_FATAL("Window Handle 반환 실패");
			return;
		}

		POINT mousePoint;
		GetCursorPos(&mousePoint);                 // 커서 좌표 받아오기
		ScreenToClient(WindowHandle, &mousePoint); // 커서의 좌표를 클라이언트 윈도우 기준으로 잡아준다.

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
