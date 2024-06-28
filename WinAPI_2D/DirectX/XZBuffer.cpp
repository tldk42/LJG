#include "XZBuffer.h"

#include "Context.h"

namespace LJG
{

	XZBuffer::XZBuffer(const float_t InZOrder)
		: mZOrder(InZOrder) {}

	XZBuffer::~XZBuffer() {}

	void XZBuffer::Initialize()
	{
		XConstantBuffer::Initialize();
	}

	void XZBuffer::Update(float DeltaTime)
	{
		XConstantBuffer::Update(DeltaTime);

		// Context::GetDeviceContext()->VSSetConstantBuffers()
	}

	void XZBuffer::Render()
	{
		XConstantBuffer::Render();
	}

	void XZBuffer::Release()
	{
		XConstantBuffer::Release();
	}
}
