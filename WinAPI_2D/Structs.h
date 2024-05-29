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

	struct FKeyData
	{
		EKeyCode  KeyCode;
		EKeyState State;
		bool      bPressed;
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
