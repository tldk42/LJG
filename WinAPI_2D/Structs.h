#pragma once
#include <cstdint>
#include "Enums.h"


namespace LJG
{
	struct FWindowData
	{
		int32_t Width;
		int32_t Height;
		bool    bFullScreen;
		bool    bVsync;
	};

	using namespace std::chrono;

	struct FKeyData
	{
		EKeyCode  KeyCode;// ���� Key
		EKeyState State; // Ű ����
		bool      bPressed;

		steady_clock::time_point PressTime;
		steady_clock::time_point ReleaseTime;
		milliseconds             PressDuration;
	};

	struct FWriteData
	{
		RECT         RectSize;
		std::wstring Text;
		int32_t      ID;

		FWriteData()
			: RectSize(),
			  Text(),
			  ID(_GenerateUniqueID()) {}

		FWriteData(const RECT& InRectSize, std::wstring InText)
			: RectSize(InRectSize),
			  Text(std::move(InText)),
			  ID(_GenerateUniqueID()) {}


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
