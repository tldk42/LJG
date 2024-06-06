#pragma once
#include <d3d11.h>
#include <wrl.h>

namespace LJG
{
	using namespace Microsoft::WRL;

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
