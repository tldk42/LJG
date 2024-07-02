#pragma once

namespace LJG
{

	/** Ű�� ���� ���� */
	enum class EKeyState : uint8_t
	{
		None,    // �⺻
		Up,      // ������
		Down,    // ���� (�Է� �Ҹ�)
		Pressed, // ���� ����
	};

	/** Ű����� �Էµ� �� �ִ� Ű ��� */
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
