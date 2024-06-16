#include "XWorldBuffer.h"

#include "Context.h"

namespace LJG
{

	void XWorldBuffer::Initialize()
	{
		XConstantBuffer::Initialize();
	}

	void XWorldBuffer::Update(float DeltaTime)
	{
		XConstantBuffer::Update(DeltaTime);

		Context::GetDeviceContext()->UpdateSubresource(mConstantBuffer.Get(), 0, nullptr, &mWorldMatrix, 0, 0);
	}

	void XWorldBuffer::Render()
	{
		XConstantBuffer::Render();

		Context::GetDeviceContext()->VSSetConstantBuffers(0, 1, mConstantBuffer.GetAddressOf());
	}

	void XWorldBuffer::Release()
	{
		XConstantBuffer::Release();
	}

	HRESULT XWorldBuffer::CreateConstantBuffer()
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
