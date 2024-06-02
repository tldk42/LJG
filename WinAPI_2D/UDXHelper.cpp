#include "UDXHelper.h"
#include <d3dcompiler.h>

#include "Context.h"

namespace LJG
{
	ID3D11VertexShader* UDXHelper::LoadVertexFile(ID3D11Device* Device, const wchar_t* VertexFileName,
	                                              ID3DBlob**    OutBlob, LPCSTR        FunctionName, bool bBinary)
	{
		HRESULT result = S_OK;

		ID3D11VertexShader* vertexShader;
		ID3DBlob*           blob;
		DWORD               size;
		LPCVOID             data;

		if (!bBinary)
		{
			result = CompileShaderFromFile(VertexFileName, FunctionName ? FunctionName : "vs", "vs_5_0", &blob);
			if (FAILED(result))
			{
				return nullptr;
			}

			size = blob->GetBufferSize();
			data = blob->GetBufferPointer();
		}
		else
		{
			blob = *OutBlob;
			if (!blob)
			{
				return nullptr;
			}
			size = blob->GetBufferSize();
			data = blob->GetBufferPointer();
		}

		if (FAILED(result = Device->CreateVertexShader(data, size, nullptr, &vertexShader)))
		{
			blob->Release();
			return nullptr;
		}

		if (!OutBlob)
		{
			blob->Release();
		}
		else
		{
			*OutBlob = blob;
		}
		return vertexShader;
	}

	ID3D11PixelShader* UDXHelper::LoadPixelShaderFile(ID3D11Device* Device, const wchar_t* PixelFileName,
	                                                  const wchar_t* FunctionName, bool bBinary, ID3DBlob** OutBlob)
	{
		HRESULT result = S_OK;

		ID3D11PixelShader* pixelShader;
		ID3DBlob*          blob;
		DWORD              size;
		LPCVOID            data;

		if (!bBinary)
		{
			result = CompileShaderFromFile(PixelFileName, "ps", "ps_5_0",
			                               &blob);
			if (FAILED(result))
			{
				return nullptr;
			}

			size = blob->GetBufferSize();
			data = blob->GetBufferPointer();
		}
		else
		{
			blob = *OutBlob;
			if (!blob)
			{
				return nullptr;
			}
			size = blob->GetBufferSize();
			data = blob->GetBufferPointer();
		}

		if (FAILED(result = Device->CreatePixelShader(data, size, nullptr, &pixelShader)))
		{
			blob->Release();
			return nullptr;
		}

		if (!OutBlob)
		{
			blob->Release();
		}
		else
		{
			*OutBlob = blob;
		}
		return pixelShader;
	}

	HRESULT UDXHelper::CompileShaderFromFile(const WCHAR* FileName, LPCSTR EntryPoint, LPCSTR ShaderModel,
	                                         ID3DBlob**   OutBlob)
	{
		HRESULT result;

		DWORD ShaderFlag = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
		ShaderFlag |= D3DCOMPILE_DEBUG;
#endif
		ID3DBlob* errorBlob;

		result = D3DCompileFromFile(
			FileName,
			nullptr,
			nullptr,
			EntryPoint,
			ShaderModel,
			ShaderFlag,
			0,
			OutBlob,
			&errorBlob);

		if (FAILED(result))
		{
			if (errorBlob)
			{
				OutputDebugStringA(static_cast<char*>(errorBlob->GetBufferPointer()));
			}
		}

		if (errorBlob)
		{
			errorBlob->Release();
		}

		return result;
	}
}
