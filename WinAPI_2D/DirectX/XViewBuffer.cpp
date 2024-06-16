#include "XViewBuffer.h"

#include "Context.h"

namespace LJG
{
	XViewBuffer::XViewBuffer()
	{
		XViewBuffer::Initialize();
	}

	void XViewBuffer::Initialize()
	{
		XConstantBuffer::Initialize();
	}

	void XViewBuffer::Update(float DeltaTime)
	{
		XConstantBuffer::Update(DeltaTime);

		Context::GetDeviceContext()->UpdateSubresource(mConstantBuffer.Get(), 0, nullptr, &mViewMatrix, 0, 0);
	}

	void XViewBuffer::Render()
	{
		XConstantBuffer::Render();

		Context::GetDeviceContext()->VSSetConstantBuffers(1, 1, mConstantBuffer.GetAddressOf());
	}

	void XViewBuffer::Release()
	{
		XConstantBuffer::Release();
	}

	HRESULT XViewBuffer::CreateConstantBuffer()
	{
		D3D11_BUFFER_DESC constantBufferDesc{};
		{
			constantBufferDesc.ByteWidth      = sizeof(Matrix);
			constantBufferDesc.Usage          = D3D11_USAGE_DEFAULT;
			constantBufferDesc.BindFlags      = D3D11_BIND_CONSTANT_BUFFER;
			constantBufferDesc.CPUAccessFlags = 0;
		}


		return Context::GetDevice()->CreateBuffer(&constantBufferDesc, nullptr, mConstantBuffer.GetAddressOf());
	}
}
