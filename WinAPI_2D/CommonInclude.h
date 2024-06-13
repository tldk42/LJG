#pragma once

// Window
#include <Windows.h>

// Basic
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>

// STL
#include <algorithm>
#include <list>
#include <map>
#include <string>
#include <vector>

#include <d3d11.h>
#include <wrl.h>

// Custom Classes
#include "Logger.h"
#include "Structs.h"

#include "Math/MathFwd.h"
#include "Math/Vector2D.h"
#include "Math/Vector.h"
#include "Math/Color.h"
#include "Math/Box2D.h"

#include "TManagedEntity.h"

using namespace Microsoft::WRL;
using namespace std::chrono;

using ResizeDelegate = std::function<void(UINT, UINT)>;
using WText = std::wstring;
using WTextView = std::wstring_view; // 읽기 전용 문자열의 경우 view를 쓰자


namespace LJG
{
	//=========================== 상수 ==============================

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


	// =========================== 인라인 함수 =============================

	template <typename T>
	inline void ReleaseCOM(T*& ComPtr)
	{
		if (ComPtr)
		{
			ComPtr->Release();
			ComPtr = nullptr;
		}
	}

	template <typename EnumType>
	inline uint8_t EnumAsByte(EnumType value)
	{
		return static_cast<uint8_t>(value);
	}

	template <typename T>
	inline bool IsValid(T ValuePtr)
	{
		return ValuePtr != nullptr;
	}

	// ======================== 인터페이스 ==================================

	class ICoreAPI
	{
	public:
		virtual      ~ICoreAPI() = default;
		virtual void Initialize() = 0;
		virtual void Update(float DeltaTime) = 0;
		virtual void Render() = 0;
		virtual void Release() = 0;
	};


#define STRUCT_PTR(structName)\
	struct structName;\
	using structName##UPtr = std::unique_ptr<structName>;\
	using structName##SPtr = std::shared_ptr<structName>;\
	using structName##WPtr = std::weak_ptr<structName>;

	STRUCT_PTR(FWriteData)
	STRUCT_PTR(FTimer)


#define CLASS_PTR(klassName)\
	class klassName;\
	using klassName##UPtr = std::unique_ptr<klassName>;\
	using klassName##SPtr = std::shared_ptr<klassName>;\
	using klassName##WPtr = std::weak_ptr<klassName>;

	CLASS_PTR(TGUI_Base)
	
	CLASS_PTR(Window)

	// -------- Graphics ------------
	CLASS_PTR(DXWrite)
	CLASS_PTR(XSamplerState)
	CLASS_PTR(XBlendState)
	CLASS_PTR(XVertex2D)
	CLASS_PTR(XTexture)
	CLASS_PTR(XSprite2D)
	CLASS_PTR(XDebugShape2D)

	//--------- Objects ---------------
	CLASS_PTR(UObject)
	CLASS_PTR(UTextBlock)
	CLASS_PTR(UAnimation)
	CLASS_PTR(UAnimator)

	//--------- Actors ---------------
	CLASS_PTR(AActor)
	CLASS_PTR(APawn)
}
