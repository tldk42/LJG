#include "XConstantBuffer.h"

#include "Context.h"

namespace LJG
{

	XConstantBuffer::XConstantBuffer()
	{
		XConstantBuffer::Initialize();
	}

	void XConstantBuffer::Initialize()
	{
		CreateConstantBuffer();
	}

	void XConstantBuffer::Update(float DeltaTime)
	{
	
	}

	void XConstantBuffer::Render() {}

	void XConstantBuffer::Release()
	{
		mConstantBuffer = nullptr;
	}

	HRESULT XConstantBuffer::CreateConstantBuffer()
	{
		return S_OK;
	}
}
