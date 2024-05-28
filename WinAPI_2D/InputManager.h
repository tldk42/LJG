#pragma once
#include "CommonInclude.h"
#include "Math/Vector2D.h"

namespace LJG
{
	class InputManager : public ICoreAPI
	{
	public:
		InputManager();

		static void Create();
		static InputManager* Get() { return s_InputManager; }

#pragma region Core Interface
		void Initialize() override;
		void Update() override;
		void Render() override;
		void Release() override;
#pragma endregion

	public:
		inline bool IsKeyDown(EKeyCode& Key) const { return mKeys[static_cast<UINT>(Key)].State == EKeyState::Down; }
		inline bool IsKeyUp(EKeyCode& Key) const { return mKeys[static_cast<UINT>(Key)].State == EKeyState::Up; }

		inline bool IsKeyPressed(EKeyCode& Key) const
		{
			return mKeys[static_cast<UINT>(Key)].State == EKeyState::Pressed;
		}

		inline const FVector2D& GetMousePosition() { return mMousePosition; }
		inline void             SetMousePosition(const FVector2D& Position);

	private:
		void CreateKeys();

		void UpdateKeys();
		void UpdateKey(Key& InKey);
		void UpdateKeyDown(Key& InKey);
		void UpdateKeyUp(Key& InKey);

		void UpdateMouseWindowPosition();

		void ClearKeys();
		void ClearMouse();

		bool IsKeyDown_Implements(const EKeyCode InKey);

	private:
		std::vector<Key> mKeys;
		FVector2D        mMousePosition;

		static InputManager* s_InputManager;
	};
}
