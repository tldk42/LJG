#pragma once
#include "CommonInclude.h"

namespace LJG
{
	CLASS_PTR(InputManager)

	class InputManager : public ICoreAPI
	{
	public:
		InputManager();
		~InputManager() override = default;

		static void          Create();
		static InputManager* Get() { return s_InputManager.get(); }

#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

	public:
		FORCEINLINE static bool             IsKeyDown(const EKeyCode Key) { return Get()->IsKeyDown_Internal(Key); }
		FORCEINLINE static bool             IsKeyUp(const EKeyCode Key) { return Get()->IsKeyUp_Internal(Key); }
		FORCEINLINE static bool             IsKeyPressed(const EKeyCode Key) { return Get()->IsKeyPressed_Internal(Key); }
		FORCEINLINE static const FVector2f& GetMousePosition() { return Get()->mMousePosition; }

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

	private:
		void CreateKeys();

		void UpdateKeys();
		void UpdateKey(FKeyData& InKey);
		void UpdateKeyDown(FKeyData& InKey);
		void UpdateKeyUp(FKeyData& InKey);

		void UpdateMouseWindowPosition();

		void ClearKeys();
		void ClearMouse();

		static bool IsKeyDown_Implements(const EKeyCode InKey);

		void Debug_Input() const;

	private:
		std::vector<FKeyData> mKeys;
		FVector2f             mMousePosition;

		bool bEnableDebug;

		static InputManagerUPtr s_InputManager;
	};
}
