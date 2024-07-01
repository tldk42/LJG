#pragma once

namespace LJG
{
	//=========================== 상수 ==============================
#pragma region 상수
	constexpr int ASCII[static_cast<UINT>(EKeyCode::End)] =
	{
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',
		VK_LEFT, VK_RIGHT, VK_DOWN, VK_UP,
		VK_LBUTTON, VK_MBUTTON, VK_RBUTTON,
		VK_SPACE, VK_F1, VK_F2, VK_F3, VK_F4,
		VK_LSHIFT
	};

	constexpr const char* ASCIIString[static_cast<UINT>(EKeyCode::End)] =
	{
		"Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P",
		"A", "S", "D", "F", "G", "H", "J", "K", "L",
		"Z", "X", "C", "V", "B", "N", "M",
		"LEFT", "RIGHT", "DOWN", "UP",
		"LBUTTON", "MBUTTON", "RBUTTON",
		"Space", "F1", "F2", "F3", "F4",
		"LSHIFT"
	};

	constexpr const char* SceneList[6] =
	{
		"Intro",
		"Menu",
		"Tutorial",
		"Game_1",
		"Game_2",
		"Game_3"
	};

#pragma endregion

}
