#include "InputManager.h"

#include "DirectX/Context.h"
#include "Helper/EngineHelper.h"


namespace LJG
{

	InputManager::InputManager()
		: mMousePosition(), bEnableDebug(false)
	{
// #ifdef _DEBUG
// 		bEnableDebug = true;
// #endif

		InputBindings_Up.reserve(30);
		InputBindings_Down.reserve(30);
		InputBindings_Pressed.reserve(30);
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

		Get().UpdateKeyBindings(DeltaTime);
	}


	void InputManager::AddInputBinding(const EKeyCode                     InKeyCode, const EKeyState BindType,
									   const FOnInputEvent::FunctionType& Callback)
	{
		switch (BindType)
		{
		case EKeyState::Up:
			InputBindings_Up[InKeyCode].Bind(Callback);
			break;
		case EKeyState::Down:
			InputBindings_Down[InKeyCode].Bind(Callback);
			break;
		case EKeyState::Pressed:
			InputBindings_Pressed[InKeyCode].Bind(Callback);
			break;
		}

	}

	void InputManager::UpdateKeyBindings(const float DeltaTime)
	{
		for (auto& inputActions : InputBindings_Up)
		{
			if (mKeys[EnumAsByte(inputActions.first)].State == EKeyState::Up)
			{
				(inputActions.second).Execute(DeltaTime);
			}
		}

		for (auto& inputActions : InputBindings_Down)
		{
			if (mKeys[EnumAsByte(inputActions.first)].State == EKeyState::Down)
			{
				(inputActions.second).Execute(DeltaTime);
			}
		}

		for (auto& inputActions : InputBindings_Pressed)
		{
			if (mKeys[EnumAsByte(inputActions.first)].State == EKeyState::Pressed)
			{
				(inputActions.second).Execute(DeltaTime);
			}
		}
	}

	void InputManager::CreateKeys()
	{
		mKeys.clear();
		mKeys.reserve(EnumAsByte(EKeyCode::End));

		for (size_t i = 0; i < EnumAsByte(EKeyCode::End); ++i)
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

		// ���콺 ������ ���� (����Ʈ�� 0,0�� ������)
		mMousePosition.X = mousePoint.x - Context::GetViewportSize().X / 2;
		mMousePosition.Y = mousePoint.y - Context::GetViewportSize().Y / 2;
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
		return GetAsyncKeyState(ASCII[EnumAsByte(InKey)]) & 0x8000;
	}

	void InputManager::Debug_Input() const
	{
		if (bEnableDebug)
		{
			for (const FKeyData& key : mKeys)
			{
				if (key.PressDuration.count() > 0)
				{
					std::cout << "Key " << ASCIIString[EnumAsByte(key.KeyCode)] << " was pressed for " <<
					key.PressDuration.count() * (1.f / 1000.f) << " seconds\n";
				}
			}
		}
	}
}
