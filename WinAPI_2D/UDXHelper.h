#pragma once
#include <d3d11.h>

namespace LJG
{
	class UDXHelper
	{
	public:
		static ID3D11VertexShader* LoadVertexFile(ID3D11Device* Device, const wchar_t* VertexFileName,
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
