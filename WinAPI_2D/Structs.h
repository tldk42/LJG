#pragma once
#include <cstdint>
#include "Enums.h"

namespace LJG
{
	struct FWindowData
	{
		uint32_t Width;
		uint32_t Height;
		bool     bFullScreen;
		bool     bVsync;
	};

	using namespace std::chrono;

	struct FKeyData
	{
		EKeyCode  KeyCode;// 고유 Key
		EKeyState State; // 키 상태
		bool      bPressed;

		steady_clock::time_point PressTime;
		steady_clock::time_point ReleaseTime;
		milliseconds             PressDuration;
	};


	struct FWriteData
	{
		RECT         RectSize;
		std::wstring Text;

	private:
		int32_t ID = _GenerateUniqueID();

		static int32_t _GenerateUniqueID()
		{
			static int currentID = 0;
			return ++currentID;
		}

		bool operator==(const FWriteData& WriteData) const
		{
			return ID == WriteData.ID;
		}
	};


}
