#pragma once

namespace LJG
{

	/** 키의 세부 상태 */
	enum class EKeyState : uint8_t
	{
		None,    // 기본
		Up,      // 떼어짐
		Down,    // 눌림 (입력 소모)
		Pressed, // 눌린 상태
	};

	/** 키보드로 입력될 수 있는 키 목록 */
	enum class EKeyCode : uint8_t
	{
		Q,
		W,
		E,
		R,
		T,
		Y,
		U,
		I,
		O,
		P,
		A,
		S,
		D,
		F,
		G,
		H,
		J,
		K,
		L,
		Z,
		X,
		C,
		V,
		B,
		N,
		M,
		Left,
		Right,
		Down,
		Up,
		LButton,
		MButton,
		RButton,
		Space,
		F1,
		F2,
		F3,
		F4,
		LShift,
		End
	};

	enum class EFileBrowserOption : uint8_t
	{
		Directory,
		File
	};

	enum class ETraceType : uint8_t
	{
		Pawn,
		Ground,
		Projectile,
		UI
	};

	enum class ENodeState : uint8_t
	{
		Running,
		Success,
		Failure
	};

	

}
