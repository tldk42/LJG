#pragma once

// Window
#include <Windows.h>

// Basic
#include <cmath>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <sstream>

// STL
#include <vector>
#include <map>
#include <string>
#include <list>
#include <algorithm>

// Custom Classes
#include "Structs.h"
#include "Logger.h"

#include "Math/MathFwd.h"
#include "Math/Vector.h"


namespace LJG
{
	//=========================== ��� ==============================

	constexpr int ASCII[static_cast<UINT>(EKeyCode::End)] =
	{
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',
		VK_LEFT, VK_RIGHT, VK_DOWN, VK_UP,
		VK_LBUTTON, VK_MBUTTON, VK_RBUTTON
	};

	constexpr const char* ASCIIString[static_cast<UINT>(EKeyCode::End)] =
	{
		"Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P",
		"A", "S", "D", "F", "G", "H", "J", "K", "L",
		"Z", "X", "C", "V", "B", "N", "M",
		"LEFT", "RIGHT", "DOWN", "UP",
		"LBUTTON", "MBUTTON", "RBUTTON"
	};


	// =========================== �ζ��� �Լ� =============================

	template <typename T>
	inline void ReleaseCOM(T* ComPtr)
	{
		if (ComPtr)
		{
			ComPtr->Release();
			ComPtr = nullptr;
		}
	}

	// ======================== �������̽� ==================================

	class ICoreAPI
	{
	public:
		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;
		virtual void Release() = 0;
	};


	using ResizeDelegate = std::function<void(UINT, UINT)>;
}
