#pragma once

/** 키의 세부 상태 */
enum class EKeyState
{
	None,    // 기본
	Down,    // 눌림
	Pressed, // 눌린 상태
	Up       // 떼어짐
};

/** 키보드로 입력될 수 있는 키 목록 */
enum class EKeyCode
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
	End
};