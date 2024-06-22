#include "XShaderData.h"

#include "Context.h"
#include "Helper/UDXHelper.h"

namespace LJG
{
	XShaderData::XShaderData(const WText& InKey, WTextView InVertexShader, WTextView InPixelShader)
		: mKey(InKey),
		  mVertexShaderFile(InVertexShader),
		  mPixelShaderFile(InPixelShader)
	{
		XShaderData::Initialize();
	}

	XShaderData::~XShaderData()
	{
		mVertexShader    = nullptr;
		mPixelShader     = nullptr;
		mVertexShaderBuf = nullptr;
	}

	void XShaderData::Initialize()
	{
		// Shader/sample2_vert.vsh , Shader/sample2_frag.psh
		CHECK_RESULT(UDXHelper::LoadVertexShaderFile(Context::GetDevice(), mVertexShaderFile,
													 mVertexShaderBuf.GetAddressOf(), mVertexShader.GetAddressOf()));
		CHECK_RESULT(UDXHelper::LoadPixelShaderFile(Context::GetDevice(), mPixelShaderFile,
													mPixelShader.GetAddressOf()));

		if (!mVertexShader.Get() || !mPixelShader.Get())
		{
			LOG_DX_ERROR("Failed to load, compile ShaderFile or 릴리즈모??경로??정??시???");
		}
	}

	void XShaderData::Update(float DeltaTime) {}

	void XShaderData::Render()
	{
		Context::GetDeviceContext()->VSSetShader(mVertexShader.Get(), nullptr, 0);
		Context::GetDeviceContext()->PSSetShader(mPixelShader.Get(), nullptr, 0);
	}

	void XShaderData::Release() {}
}
