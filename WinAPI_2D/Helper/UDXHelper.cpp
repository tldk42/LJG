#include "UDXHelper.h"
#include <d3dcompiler.h>

#include "DirectX/Context.h"

namespace LJG
{
	HRESULT UDXHelper::LoadVertexShaderFile(ID3D11Device* Device, const wchar_t*        VertexFileName,
											ID3DBlob**    OutBlob, ID3D11VertexShader** VertexShader, LPCSTR FunctionName,
											bool          bBinary)
	{
		HRESULT result = S_OK;

		ID3DBlob* blob;
		DWORD     size;
		LPCVOID   data;

		if (!bBinary)
		{
			result = CompileShaderFromFile(VertexFileName, FunctionName ? FunctionName : "vs", "vs_5_0",
										   &blob);
			if (FAILED(result))
			{
				return result;
			}

			size = blob->GetBufferSize();
			data = blob->GetBufferPointer();
		}
		else
		{
			blob = *OutBlob;
			if (!blob)
			{
				return E_FAIL;
			}
			size = blob->GetBufferSize();
			data = blob->GetBufferPointer();
		}

		if (FAILED(result = Device->CreateVertexShader(data, size, nullptr, VertexShader)))
		{
			blob = nullptr;
			return result;
		}

		if (!OutBlob)
		{
			blob = nullptr;
		}
		else
		{
			*OutBlob = blob;
		}
		return result;
	}

	HRESULT UDXHelper::LoadPixelShaderFile(ID3D11Device*       Device, const wchar_t* PixelFileName,
										   ID3D11PixelShader** pixelShader,
										   const wchar_t*      FunctionName, bool bBinary,
										   ID3DBlob**          OutBlob)
	{
		HRESULT result = S_OK;

		ID3DBlob* blob;
		DWORD     size;
		LPCVOID   data;

		if (!bBinary)
		{
			result = CompileShaderFromFile(PixelFileName, "ps", "ps_5_0",
										   &blob);
			if (FAILED(result))
			{
				return result;
			}

			size = blob->GetBufferSize();
			data = blob->GetBufferPointer();
		}
		else
		{
			blob = *OutBlob;
			if (!blob)
			{
				return E_FAIL;
			}
			size = blob->GetBufferSize();
			data = blob->GetBufferPointer();
		}

		if (FAILED(result = Device->CreatePixelShader(data, size, nullptr, pixelShader)))
		{
			blob = nullptr;
			return result;
		}

		if (!OutBlob)
		{
			blob = nullptr;
		}
		else
		{
			*OutBlob = blob;
		}
		return result;
	}

	HRESULT UDXHelper::CompileShaderFromFile(const WCHAR* FileName, LPCSTR EntryPoint, LPCSTR ShaderModel,
											 ID3DBlob**   OutBlob)
	{
		HRESULT result;

		DWORD ShaderFlag = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
		ShaderFlag |= D3DCOMPILE_DEBUG;
#endif
		ComPtr<ID3DBlob> errorBlob;

		result = D3DCompileFromFile(
			FileName,    // 셰이더 파일명
			nullptr,     // 코드 안 매크로 배열 주소
			nullptr,     // ID3DInclude 인터페이스
			EntryPoint,  // main 진입점
			ShaderModel, // 셰이더 프로필
			ShaderFlag,  // 셰이더 컴파일 플래그
			0,           // 이펙트 옵션 컴파일 플래그
			OutBlob,     // 반환 될 blob
			errorBlob.GetAddressOf()// 컴파일 오류 및 경고 목록 저장
		);

		if (FAILED(result))
		{
			if (errorBlob.Get())
			{
				OutputDebugStringA(static_cast<char*>(errorBlob->GetBufferPointer()));
			}
		}

		if (errorBlob.Get())
		{
			errorBlob = nullptr;
		}

		return result;
	}

	FVector2f UDXHelper::NDC2Screen(const FVector2f& InWindow, const FVector2f& InNDC)
	{
		FVector2f returnValue;

		returnValue.X = static_cast<float_t>(InWindow.X) * (InNDC.X + 1.f) * .5f;
		returnValue.Y = static_cast<float_t>(InWindow.Y) * .5f * (1.f - InNDC.Y);

		return returnValue;
	}

	FVector2f UDXHelper::Screen2NDC(const FVector2f& InWindow, const FVector2f& InScreen)
	{
		FVector2f returnValue;

		returnValue.X = InScreen.X / (static_cast<float_t>(InWindow.X) * .5f);
		returnValue.Y = InScreen.Y / (static_cast<float_t>(InWindow.Y) * .5f);

		return returnValue;
	}
}
