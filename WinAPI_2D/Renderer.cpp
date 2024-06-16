#include "Renderer.h"

#include "DirectX/Context.h"
#include "DirectX/DXWrite.h"

namespace LJG
{
	Renderer::Renderer() {}

	Renderer::~Renderer()
	{
		Renderer::Release();
	}

	void Renderer::Initialize()
	{
		Context::Create();
		DXWrite::Create();
	}

	void Renderer::Update(float DeltaTime)
	{}

	void Renderer::Release()
	{
		DXWrite::Get()->Release();
		Context::Get()->Release();
	}

	void Renderer::Render()
	{
		DXWrite::Get()->Render();
		Context::Get()->Render();
	}

	void Renderer::Clear(const FLinearColor& InClearColor)
	{
		Context::GetDeviceContext()->ClearRenderTargetView(Context::GetRTV(), InClearColor.RGBA);
	}
}
