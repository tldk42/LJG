#pragma once

// Window
#include <Windows.h>

// Basic
#include <cmath>
#include <cstdint>
#include <tchar.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <atlconv.h>

// STL
#include <algorithm>
#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>

#include <d3d11.h>
#include <wrl.h>

// Custom Classes
#include "Helper/Logger.h"
#include "Structs.h"

#include "Math/MathFwd.h"
#include "Math/Vector2D.h"
#include "Math/Vector.h"
#include "Math/Color.h"
#include "Math/Box2D.h"
#include <DirectXMath.h>

#include "TManagedEntity.h"

using namespace Microsoft::WRL;
using namespace std::chrono;
using namespace DirectX;


using ResizeDelegate = std::function<void(UINT, UINT)>;

using Text = std::string;
using TextView = std::string_view;
using WText = std::wstring;
using WTextView = std::wstring_view; // 읽기 전용 문자열의 경우 view를 쓰자
using Matrix = XMMATRIX;

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
		VK_SPACE
	};

	constexpr const char* ASCIIString[static_cast<UINT>(EKeyCode::End)] =
	{
		"Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P",
		"A", "S", "D", "F", "G", "H", "J", "K", "L",
		"Z", "X", "C", "V", "B", "N", "M",
		"LEFT", "RIGHT", "DOWN", "UP",
		"LBUTTON", "MBUTTON", "RBUTTON",
		"Space"
	};
#pragma endregion

	// =========================== 인라인 함수 =============================
#pragma region 인라인 함수

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

	/** UObject 유효성 검사 */
	template <typename T>
	inline bool IsValid(T ValuePtr)
	{
		return ValuePtr != nullptr;
	}

	inline WText Text2WText(const Text& InString)
	{
		USES_CONVERSION;
		return WText(A2W(InString.c_str()));
	}

	inline Text WText2Text(const WText& InWString)
	{
		USES_CONVERSION;
		return Text(W2A(InWString.c_str()));
	}

	/** 이동 변환 행렬 생성 */
	inline XMMATRIX TranslationMatrix(float InX, float InY, float InZ = 0.f)
	{
		return XMMatrixTranslation(InX, InY, InZ);
	}

	/** 회전 변환 행렬 생성 */
	inline XMMATRIX RotationMatrix(float InDegree)
	{
		float radians = XMConvertToRadians(InDegree);
		return XMMatrixRotationZ(radians);
	}

	/** 스케일 변환 행렬 생성 */
	inline XMMATRIX ScaleMatrix(float InX, float InY)
	{
		return XMMatrixScaling(InX, InY, 1.0f);
	}

	/** 4x4 행렬 -> 위치벡터 반환 */
	inline FVector2f Mat2LocVector2(const Matrix& InMatrix)
	{
		XMFLOAT4X4 locationVec;
		XMStoreFloat4x4(&locationVec, InMatrix);
		return {locationVec._41, locationVec._42};
	}

	/** 4x4 행렬 -> 회전 각 반환 */
	inline float Mat2RotDegree(const Matrix& InMatrix)
	{
		XMFLOAT4X4 matrixValues;
		XMStoreFloat4x4(&matrixValues, InMatrix);

		return XMConvertToDegrees(atan2f(matrixValues._21, matrixValues._11));
	}

	/** 4x4 행렬 -> 크기벡터 반환 */
	inline FVector2f Mat2ScaleVector2(const Matrix& InMatrix)
	{
		XMFLOAT4X4 matrixValues;
		XMStoreFloat4x4(&matrixValues, InMatrix);

		const float scaleX = sqrtf(matrixValues._11 * matrixValues._11 + matrixValues._12 * matrixValues._12);
		const float scaleY = sqrtf(matrixValues._21 * matrixValues._21 + matrixValues._22 * matrixValues._22);

		return FVector2f{scaleX, scaleY};
	}
#pragma endregion

	// ======================== 인터페이스 ==================================

	class ICoreAPI
	{
	public:
		virtual ~ICoreAPI() = default;

		virtual void Initialize() = 0;
		virtual void Update(float DeltaTime) = 0;
		virtual void Render() = 0;
		virtual void Release() = 0;
	};

	class IManagedAPI
	{
	public:
		virtual ~IManagedAPI() = default;

		virtual void SetID(WTextView InKey) = 0;
	};

	// ======================== 매크로 ================================
#pragma region 매크로

#define CONCATENATE(x, y) x##y // 토큰 결합
#define STRINGIFY(x) #x // 문자열화
#define CHECK_PREFIX(name, prefix) static_assert(std::string_view(STRINGIFY(name)).substr(0, 1) == #prefix, "DelegateName must start with '#prefix'");

#define DECLARE_DYNAMIC_DELEGATE(delegateName, ...)\
CHECK_PREFIX(delegateName, F);\
class delegateName {\
	public:\
	using FunctionType = std::function<void(__VA_ARGS__)>;\
	void Bind(FunctionType func) { functions.push_back(func); }\
	template<typename... Args>\
	void Execute(Args&&... args) { for (auto& func : functions) { func(std::forward<Args>(args)...); } }\
	private:\
	std::vector<FunctionType> functions;\
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
	CLASS_PTR(GUI_Inspector)

	CLASS_PTR(Window)

	// -------- Graphics ------------
	CLASS_PTR(DXWrite)
	CLASS_PTR(XSamplerState)
	CLASS_PTR(XBlendState)
	CLASS_PTR(XVertex2D)
	CLASS_PTR(XTexture)
	CLASS_PTR(XSprite2D)
	CLASS_PTR(XDebugShape2D)
	CLASS_PTR(XWorldBuffer)
	CLASS_PTR(XViewBuffer)
	CLASS_PTR(XProjectionBuffer)

	//--------- Objects ---------------
	CLASS_PTR(UObject)
	CLASS_PTR(UTextBlock)
	CLASS_PTR(UAnimation)
	CLASS_PTR(UAnimator)

	//--------- Actors ---------------
	CLASS_PTR(AActor)
	CLASS_PTR(APawn)
#pragma endregion

}
