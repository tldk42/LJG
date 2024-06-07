#pragma once
#include <assert.h>
#include <d3d11.h>
#include <wrl.h>

namespace LJG
{
	using namespace Microsoft::WRL;

	inline void CHECK_RESULT(const HRESULT Result, ...)
	{
		if (FAILED(Result))
		{
			PWSTR output;
			WCHAR buffer[256] = {0,};
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

			wsprintf(buffer, L"Error= %s ", L"__FILE__");
			MessageBox(nullptr, buffer, output, MB_OK);
		}

		assert(SUCCEEDED(Result));
	}

	class UDXHelper
	{
	public:
		static HRESULT LoadVertexShaderFile(ID3D11Device* Device, const wchar_t*        VertexFileName,
		                                    ID3DBlob**    OutBlob, ID3D11VertexShader** VertexShader,
		                                    LPCSTR        FunctionName = nullptr,
		                                    bool          bBinary      = false);
		static HRESULT LoadPixelShaderFile(ID3D11Device*       d3dDevice,
		                                   const wchar_t*      PixelFileName,
		                                   ID3D11PixelShader** pixelShader,
		                                   const wchar_t*      FunctionName = nullptr,
		                                   bool                bBinary      = false,
		                                   ID3DBlob**          OutBlob      = nullptr);

		static HRESULT CompileShaderFromFile(const WCHAR* FileName, LPCSTR EntryPoint, LPCSTR ShaderModel,
		                                     ID3DBlob**   OutBlob);
	};
}
