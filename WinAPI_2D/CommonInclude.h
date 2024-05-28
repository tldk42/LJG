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

	class ICoreAPI
	{
	public:
		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;
		virtual void Release() = 0;
	};
}
