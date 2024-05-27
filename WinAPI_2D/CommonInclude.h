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
#include <algorithm>

// Custom Classes
#include "Structs.h"
#include "Logger.h"


namespace LJG
{
	template <typename T>
	void ReleaseCOM(T* ComPtr)
	{
		if (ComPtr)
		{
			ComPtr->Release();
			ComPtr = nullptr;
		}
	}
}
