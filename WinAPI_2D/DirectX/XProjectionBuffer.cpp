#include "XProjectionBuffer.h"

#include "Context.h"

namespace LJG
{

	XProjectionBuffer::XProjectionBuffer()
	{
		XConstantBuffer::Initialize();
	}

	void XProjectionBuffer::Initialize()
	{
		XConstantBuffer::Initialize();
	}

	void XProjectionBuffer::Update(float DeltaTime)
	{
		XConstantBuffer::Update(DeltaTime);

		Context::GetDeviceContext()->UpdateSubresource(mConstantBuffer.Get(), 0, nullptr, &mProjectionMatrix, 0, 0);
	}

	void XProjectionBuffer::Render()
	{
		XConstantBuffer::Render();

		Context::GetDeviceContext()->VSSetConstantBuffers(2, 1, mConstantBuffer.GetAddressOf());
	}

	void XProjectionBuffer::Release()
	{
		XConstantBuffer::Release();
	}

	HRESULT XProjectionBuffer::CreateConstantBuffer()
	{
		D3D11_BUFFER_DESC constantBufferDesc{};
		{
			constantBufferDesc.ByteWidth      = sizeof(XMMATRIX);
			constantBufferDesc.Usage          = D3D11_USAGE_DEFAULT;
			constantBufferDesc.BindFlags      = D3D11_BIND_CONSTANT_BUFFER;
			constantBufferDesc.CPUAccessFlags = 0;
		}

		return Context::GetDevice()->CreateBuffer(&constantBufferDesc, nullptr, mConstantBuffer.GetAddressOf());
	}
}
