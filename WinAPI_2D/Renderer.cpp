#include "Renderer.h"

#include "Context.h"
#include "DXWrite.h"

namespace LJG
{
	Renderer* Renderer::s_Renderer;


	Renderer::Renderer(const FWindowData& InWinData, HWND InWindowHandle)
		: mWindowData(InWinData),
		  mWindowHandle(InWindowHandle) {}

	void Renderer::Create(const FWindowData& WinData, void* DeviceContext)
	{
		if (!s_Renderer)
		{
			s_Renderer = new Renderer(WinData, static_cast<HWND>(DeviceContext));

			s_Renderer->Initialize();
		}
	}

	void Renderer::Initialize()
	{
		Context::Create(mWindowData, mWindowHandle);

		IDXGISurface1* surface = nullptr;
		Context::GetSwapChain()->GetBuffer(0, __uuidof(IDXGISurface1), reinterpret_cast<void**>(&surface));

		DXWrite::Create(mWindowData.Width, mWindowData.Height, surface);

		surface->Release();
	}

	void Renderer::Update() {}

	void Renderer::Release() {}

	Renderer* Renderer::GetRenderer()
	{
		return s_Renderer;
	}

	void Renderer::Render()
	{
		Clear();

		DXWrite::Get()->Render();
		Context::Get()->Render();
	}

	void Renderer::Clear()
	{
		constexpr float clearColor[] = {.1f, .2f, .3f, 1.f};

		Context::GetDeviceContext()->ClearRenderTargetView(Context::GetRTV(), clearColor);
	}
}
