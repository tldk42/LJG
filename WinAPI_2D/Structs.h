#pragma once
#include <cstdint>
#include "Enums.h"
#include "Math/MathFwd.h"
#include "Math/Vector2D.h"

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


	struct FCachedRenderState
	{
		Microsoft::WRL::ComPtr<ID3D11InputLayout>  CurrentInputLayout  = nullptr;
		Microsoft::WRL::ComPtr<ID3D11VertexShader> CurrentVertexShader = nullptr;
		Microsoft::WRL::ComPtr<ID3D11PixelShader>  CurrentPixelShader  = nullptr;
		Microsoft::WRL::ComPtr<ID3D11Buffer>       CurrentVertexBuffer = nullptr;
		Microsoft::WRL::ComPtr<ID3D11Buffer>       CurrentIndexBuffer  = nullptr;
		D3D_PRIMITIVE_TOPOLOGY                     CurrentTopology     = D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED;
	};


	struct FSceneData
	{
		std::string  Key;// 키 이름
		std::wstring TexPath  = LR"()"; // 텍스처 경로
		FVector2f    Position = FVector2f::ZeroVector;
		FVector2f    Scale    = FVector2f::UnitVector;
		float        ZOrder   = 0.5f;
		float        Rotation = 0.f;
	};
}
