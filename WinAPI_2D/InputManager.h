#pragma once
#include "CommonInclude.h"
#include "Math/Vector2D.h"

namespace LJG
{
	CLASS_PTR(InputManager)

	class InputManager : public ICoreAPI
	{
	public:
		InputManager();
		~InputManager() = default;

		static void          Create();
		static InputManager* Get() { return s_InputManager.get(); }

#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

	public:
		FORCEINLINE static bool IsKeyDown(const EKeyCode Key) { return Get()->IsKeyDown_Internal(Key); }
		FORCEINLINE static bool IsKeyUp(const EKeyCode Key) { return Get()->IsKeyUp_Internal(Key); }
		FORCEINLINE static bool IsKeyPressed(const EKeyCode Key) { return Get()->IsKeyPressed_Internal(Key); }

	private:
		inline bool IsKeyDown_Internal(EKeyCode Key) const
		{
			return mKeys[static_cast<UINT>(Key)].State == EKeyState::Down;
		}

		inline bool IsKeyUp_Internal(EKeyCode Key) const
		{
			return mKeys[static_cast<UINT>(Key)].State == EKeyState::Up;
		}

		inline bool IsKeyPressed_Internal(EKeyCode Key) const
		{
			return mKeys[static_cast<UINT>(Key)].State == EKeyState::Pressed;
		}

		inline const FVector2D& GetMousePosition() { return mMousePosition; }
		inline void             SetMousePosition(const FVector2D& Position);

	private:
		void CreateKeys();

		void UpdateKeys();
		void UpdateKey(FKeyData& InKey);
		void UpdateKeyDown(FKeyData& InKey);
		void UpdateKeyUp(FKeyData& InKey);

		void UpdateMouseWindowPosition();

		void ClearKeys();
		void ClearMouse();

		bool IsKeyDown_Implements(const EKeyCode InKey);

	private:
		std::vector<FKeyData> mKeys;
		FVector2D             mMousePosition;

		static InputManagerUPtr s_InputManager;
	};
}
