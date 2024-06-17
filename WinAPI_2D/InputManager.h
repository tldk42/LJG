#pragma once
#include "CommonInclude.h"

namespace LJG
{

	class InputManager
	{

		using InputCallback = Delegate_OneParam<float_t>;

	public:
		InputManager();
		~InputManager() = default;

		[[nodiscard]] inline static InputManager& Get()
		{
			static InputManager instance;
			return instance;
		}

		static void Initialize();
		static void Update(float DeltaTime);

	public:
		FORCEINLINE static bool             IsKeyDown(const EKeyCode Key) { return Get().IsKeyDown_Internal(Key); }
		FORCEINLINE static bool             IsKeyUp(const EKeyCode Key) { return Get().IsKeyUp_Internal(Key); }
		FORCEINLINE static bool             IsKeyPressed(const EKeyCode Key) { return Get().IsKeyPressed_Internal(Key); }
		FORCEINLINE static const FVector2f& GetMousePosition() { return Get().mMousePosition; }

		FORCEINLINE static void EnableDebug(const bool bEnable) { Get().bEnableDebug = bEnable; }

		void AddInputBinding(const EKeyCode InKeyCode, const EKeyState BindType, InputCallback Callback);

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

		void UpdateKeyBindings(const EKeyState InTriggerType,const float DeltaTime);

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

	public:
		std::unordered_map<EKeyCode, std::vector<InputCallback>> InputBindings_Up;
		std::unordered_map<EKeyCode, std::vector<InputCallback>> InputBindings_Down;
		std::unordered_map<EKeyCode, std::vector<InputCallback>> InputBindings_Pressed;

	private:
		std::vector<FKeyData> mKeys;
		FVector2f             mMousePosition;

		bool bEnableDebug;
	};
}
