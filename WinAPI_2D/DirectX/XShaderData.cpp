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
		// Shader/alphablend.vsh , Shader/alphablend.psh
		CHECK_RESULT(UDXHelper::LoadVertexShaderFile(Context::GetDevice(), mVertexShaderFile,
													 mVertexShaderBuf.GetAddressOf(), mVertexShader.GetAddressOf()));
		CHECK_RESULT(UDXHelper::LoadPixelShaderFile(Context::GetDevice(), mPixelShaderFile,
													mPixelShader.GetAddressOf()));

		if (!mVertexShader.Get() || !mPixelShader.Get())
		{
			LOG_DX_ERROR("Failed to load, compile ShaderFile or �������??���??��??��???");
		}

		if (mKey == L"SimpleShader")
		{
			constexpr D3D11_INPUT_ELEMENT_DESC layout[] =
			{
				{
					"POSITION",                  // ���̴� �Է� ������ �� ��ҿ� ����� �ǹ�ü�� 
					0,                           // �ǹ̻� �ε���
					DXGI_FORMAT_R32G32B32_FLOAT, // ������ ���� (float2)
					0,                           // �Է� ����� �ĺ�����
					0,                           // ��� ���� ������ 
					D3D11_INPUT_PER_VERTEX_DATA, // ���� �Է� ���� �Է� ������ Ŭ����
					0                            // ���� ���ۿ��� ������ �Ǵ� �ν��Ͻ��� �� (D3D11_INPUT_PER_VERTEX_DATA -> 0)
				},
				{
					"COLOR",
					0,
					DXGI_FORMAT_R32G32B32A32_FLOAT,
					0,
					D3D11_APPEND_ALIGNED_ELEMENT,
					D3D11_INPUT_PER_VERTEX_DATA,
					0
				}
			};

			CHECK_RESULT(Context::GetDevice()->CreateInputLayout(
				layout,
				2,
				mVertexShaderBuf->GetBufferPointer(),
				mVertexShaderBuf->GetBufferSize(),
				mVertexLayout.GetAddressOf()));
		}
		else
		{
			constexpr D3D11_INPUT_ELEMENT_DESC layout[] =
			{
				{
					"POSITION",                  // ���̴� �Է� ������ �� ��ҿ� ����� �ǹ�ü�� 
					0,                           // �ǹ̻� �ε���
					DXGI_FORMAT_R32G32B32_FLOAT, // ������ ���� (float2)
					0,                           // �Է� ����� �ĺ�����
					0,                           // ��� ���� ������ 
					D3D11_INPUT_PER_VERTEX_DATA, // ���� �Է� ���� �Է� ������ Ŭ����
					0                            // ���� ���ۿ��� ������ �Ǵ� �ν��Ͻ��� �� (D3D11_INPUT_PER_VERTEX_DATA -> 0)
				},
				{
					"COLOR",
					0,
					DXGI_FORMAT_R32G32B32A32_FLOAT,
					0,
					D3D11_APPEND_ALIGNED_ELEMENT,
					D3D11_INPUT_PER_VERTEX_DATA,
					0
				},
				{
					"TEX",
					0,
					DXGI_FORMAT_R32G32_FLOAT,
					0,
					D3D11_APPEND_ALIGNED_ELEMENT,
					D3D11_INPUT_PER_VERTEX_DATA,
					0
				}
			};

			CHECK_RESULT(Context::GetDevice()->CreateInputLayout(
				layout,
				3,
				mVertexShaderBuf->GetBufferPointer(),
				mVertexShaderBuf->GetBufferSize(),
				mVertexLayout.GetAddressOf()));
		}

	}

	void XShaderData::Update(float DeltaTime) {}

	void XShaderData::Render()
	{
		// Input Layout
		Context::GetDeviceContext()->IASetInputLayout(mVertexLayout.Get());

		Context::GetDeviceContext()->VSSetShader(mVertexShader.Get(), nullptr, 0);
		Context::GetDeviceContext()->PSSetShader(mPixelShader.Get(), nullptr, 0);
	}

	void XShaderData::Release()
	{
		mVertexShader    = nullptr;
		mPixelShader     = nullptr;
		mVertexShaderBuf = nullptr;
		mVertexLayout    = nullptr;
	}
}
