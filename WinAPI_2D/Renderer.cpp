#include "Renderer.h"

#include "Context.h"
#include "DXWrite.h"

namespace LJG
{
	RendererUPtr Renderer::s_Renderer = nullptr;


	Renderer::Renderer(const FWindowData& InWinData, HWND InWindowHandle)
		: mWindowData(InWinData),
		  mWindowHandle(InWindowHandle) {}

	Renderer::~Renderer()
	{
		Renderer::Release();
	}

	void Renderer::Create(const FWindowData& WinData, void* DeviceContext)
	{
		if (!s_Renderer)
		{
			s_Renderer.reset(new Renderer(WinData, static_cast<HWND>(DeviceContext)));

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

	void Renderer::Update(float DeltaTime) {}

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

	void Renderer::Clear()
	{
		constexpr float clearColor[] = {.1f, .2f, .3f, 1.f};

		Context* s = Context::Get();

		Context::GetDeviceContext()->ClearRenderTargetView(Context::GetRTV(), clearColor);
	}
}
