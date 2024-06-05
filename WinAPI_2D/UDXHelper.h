#pragma once
#include <d3d11.h>
#include <wrl.h>

namespace LJG
{
	using namespace Microsoft::WRL;

	class UDXHelper
	{
	public:
		static ID3D11VertexShader* LoadVertexShaderFile(ID3D11Device* Device, const wchar_t* VertexFileName,
		                                                ID3DBlob**    OutBlob, LPCSTR        FunctionName = nullptr,
		                                                bool          bBinary                             = false);
		static ID3D11PixelShader* LoadPixelShaderFile(ID3D11Device*  d3dDevice,
		                                              const wchar_t* PixelFileName,
		                                              const wchar_t* FunctionName = nullptr,
		                                              bool           bBinary      = false,
		                                              ID3DBlob**     OutBlob      = nullptr);

		static HRESULT CompileShaderFromFile(const WCHAR* FileName, LPCSTR EntryPoint, LPCSTR ShaderModel,
		                                     ID3DBlob**   OutBlob);
	};
}
