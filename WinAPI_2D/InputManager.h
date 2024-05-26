#pragma once
#include "CommonInclude.h"
#include "Math/MathFwd.h"

namespace LJG
{
	class InputManager
	{
	public:
		static void Initialize();

	public:
		static void Update();

		inline static bool IsKeyDown(EKeyCode& Key) { return s_Keys[static_cast<UINT>(Key)].State == EKeyState::Down; }
		inline static bool IsKeyUp(EKeyCode& Key) { return s_Keys[static_cast<UINT>(Key)].State == EKeyState::Up; }

		inline static bool IsKeyPressed(EKeyCode& Key)
		{
			return s_Keys[static_cast<UINT>(Key)].State == EKeyState::Pressed;
		}

		inline static const FVector2D& GetMousePosition() { return s_MousePosition; }
		inline void                    SetMousePosition(const FVector2D& Position);

	private:
		static void CreateKeys();

		static void UpdateKeys();
		static void UpdateKey(Key& InKey);
		static void UpdateKeyDown(Key& InKey);
		static void UpdateKeyUp(Key& InKey);

		static void UpdateMouseWindowPosition();

		static void ClearKeys();
		static void ClearMouse();

		static bool IsKeyDown_Implements(const EKeyCode InKey);

	private:
		static std::vector<Key> s_Keys;
		static FVector2D        s_MousePosition;
	};
}
