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
#include "data/constant.h"

#include "Math/MathFwd.h"
#include "Math/Vector2D.h"
#include "Math/Vector.h"
#include "Math/Color.h"
#include "Math/Box2D.h"
#include "Math/Line.h"
#include <DirectXMath.h>


using namespace Microsoft::WRL;
using namespace std::chrono;
using namespace DirectX;


using ResizeDelegate = std::function<void(UINT, UINT)>;

using Text      = std::string;
using TextView  = std::string_view;
using WText     = std::wstring;
using WTextView = std::wstring_view; // 읽기 전용 문자열의 경우 view를 쓰자
using Matrix    = XMMATRIX;

namespace LJG
{


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

	class IInteractableAPI
	{
	public:
		virtual ~IInteractableAPI() = default;

		virtual void OnBeginInteract() = 0;
		virtual void OnEndInteract() = 0;
	};

	class ICollisionAPI
	{
	public:
		virtual ~ICollisionAPI() = default;

		virtual ETraceType GetTraceType() = 0;

		virtual void OnCollisionEnter(struct FHitResult_Box2D& HitResult) = 0;
		virtual void OnCollision(struct FHitResult_Box2D& HitResult) = 0;
		virtual void OnCollisionExit(struct FHitResult_Box2D& HitResult) = 0;

		virtual uint32_t GetCollisionID() = 0;
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
	public:\
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
	CLASS_PTR(XShape2D_Box)
	CLASS_PTR(XShape2D_Line)
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
