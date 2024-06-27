#pragma once
#include "CommonInclude.h"
#include "Component/Manager/Manager.h"

namespace LJG
{

	DECLARE_DYNAMIC_DELEGATE(FOnInputEvent, float_t)

	#define Manager_Input InputManager::Get()
	
	class InputManager : public TSingleton<InputManager>
	{

	public:
		void Initialize();
		void Update(float DeltaTime);

	public:
		FORCEINLINE static bool             IsKeyDown(const EKeyCode Key) { return Get().IsKeyDown_Internal(Key); }
		FORCEINLINE static bool             IsKeyUp(const EKeyCode Key) { return Get().IsKeyUp_Internal(Key); }
		FORCEINLINE static bool             IsKeyPressed(const EKeyCode Key) { return Get().IsKeyPressed_Internal(Key); }
		FORCEINLINE static const FVector2f& GetMousePosition() { return Get().mMousePosition; }

		FORCEINLINE static void EnableDebug(const bool bEnable) { Get().bEnableDebug = bEnable; }

		void AddInputBinding(const EKeyCode                     InKeyCode, const EKeyState BindType,
							 const FOnInputEvent::FunctionType& Callback);

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

		void UpdateKeyBindings(const float DeltaTime);

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
		std::unordered_map<EKeyCode, FOnInputEvent> InputBindings_Up;
		std::unordered_map<EKeyCode, FOnInputEvent> InputBindings_Down;
		std::unordered_map<EKeyCode, FOnInputEvent> InputBindings_Pressed;

	private:
		std::vector<FKeyData> mKeys;
		FVector2f             mMousePosition;

		bool bEnableDebug;

	private:
		friend class TSingleton<InputManager>;
		InputManager();
		~InputManager() = default;

	};
}
