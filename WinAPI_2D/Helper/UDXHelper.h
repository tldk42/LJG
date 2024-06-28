#pragma once
#include "CommonInclude.h"

namespace LJG
{

	inline void CHECK_RESULT(const HRESULT Result, ...)
	{
		if (FAILED(Result))
		{
			PWSTR output;
			FormatMessage(
				FORMAT_MESSAGE_FROM_SYSTEM |
				FORMAT_MESSAGE_IGNORE_INSERTS |
				FORMAT_MESSAGE_ALLOCATE_BUFFER,
				nullptr,
				Result,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				reinterpret_cast<LPTSTR>(&output),
				0,
				nullptr);

			MessageBox(nullptr, output, L"ㅋㅋㅋ 에러 ㅋㅋㅋ", MB_OK);
		}

		assert(SUCCEEDED(Result));
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

	class UDXHelper
	{
	public:
		static HRESULT LoadVertexShaderFile(ID3D11Device* Device, const WText&          VertexFileName,
											ID3DBlob**    OutBlob, ID3D11VertexShader** VertexShader,
											LPCSTR        FunctionName = nullptr,
											bool          bBinary      = false);
		static HRESULT LoadPixelShaderFile(ID3D11Device*       d3dDevice,
										   const WText&        PixelFileName,
										   ID3D11PixelShader** pixelShader,
										   const wchar_t*      FunctionName = nullptr,
										   bool                bBinary      = false,
										   ID3DBlob**          OutBlob      = nullptr);

		static HRESULT CompileShaderFromFile(const WCHAR* FileName, LPCSTR EntryPoint, LPCSTR ShaderModel,
											 ID3DBlob**   OutBlob);

		static FVector2f NDC2Screen(const FVector2f& InWindow, const FVector2f& InNDC);
		static FVector2f Screen2NDC(const FVector2f& InWindow, const FVector2f& InScreen);
	};
}
