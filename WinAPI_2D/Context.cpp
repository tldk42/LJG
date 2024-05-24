#include "Context.h"

#include "EngineHelper.h"

namespace LJG
{
	Context* Context::s_Context = nullptr;

	Context::Context(const FWindowData& WinData, void* DeviceContext)
		: mDevice(nullptr),
		  mDeviceContext(nullptr),
		  mSwapChain(nullptr),
		  mRenderTargetView(nullptr),
		  mDepthStencilView(nullptr),
		  mDepthStencilBuffer(nullptr),
		  mViewport(),
		  mFeatureLevel(D3D_FEATURE_LEVEL_11_0),
		  mVideoCardMemory(0),
		  mVideoCardDescription{},
		  mWindowData(WinData)

	{
		InitD3D(static_cast<HWND>(DeviceContext));
	}

	Context::~Context()
	{
		DX::ReleaseCOM(mDevice);
		DX::ReleaseCOM(mDeviceContext);
		DX::ReleaseCOM(mSwapChain);
		DX::ReleaseCOM(mRenderTargetView);
		DX::ReleaseCOM(mDepthStencilBuffer);
		DX::ReleaseCOM(mDepthStencilBuffer);
		DX::ReleaseCOM(mDepthStencilView);
	}

	void Context::Create(const FWindowData& WinData, void* DeviceContext)
	{
		s_Context = new Context(WinData, DeviceContext);
	}

	void Context::Present()
	{
		if (mSwapChain)
		{
			float clearColor[] = {.1f, .2f, .3f, 1.f};
			mDeviceContext->ClearRenderTargetView(mRenderTargetView, clearColor);

			if (FAILED(mSwapChain->Present(mWindowData.bVsync, 0)))
			{
				LOG_DX_ERROR("SwapChain Present Failed");
			}
		}
	}

	void Context::InitD3D(HWND Hwnd)
	{
		LOG_DX_INFO("DX �ʱ�ȭ ����...");

		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

		swapChainDesc.BufferCount                        = 1;
		swapChainDesc.BufferDesc.Width                   = 1600;                            // Buffer Width
		swapChainDesc.BufferDesc.Height                  = 900;                             // Buffer Height
		swapChainDesc.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;      // ���� ��� ����
		swapChainDesc.BufferDesc.RefreshRate.Numerator   = 60;                              // FPS ����
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;                               // FPS �и�
		swapChainDesc.BufferUsage                        = DXGI_USAGE_RENDER_TARGET_OUTPUT; // ���� (������ ����)
		swapChainDesc.OutputWindow                       = Hwnd;                            // ��µ� ������ �ڵ�
		swapChainDesc.SampleDesc.Count                   = 1;                               // ��Ƽ ���ø� ����
		swapChainDesc.SampleDesc.Quality                 = 0;                               // ��Ƽ ���ø� ǰ��
		swapChainDesc.Windowed                           = !(mWindowData.bFullScreen);      // â ��ü ȭ�� ���
		swapChainDesc.SwapEffect                         = DXGI_SWAP_EFFECT_DISCARD;
		swapChainDesc.Flags                              = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		if (FAILED(D3D11CreateDeviceAndSwapChain(
			NULL,                               // pAdapter (�����) : null�̸� �� ����� ���
			D3D_DRIVER_TYPE_HARDWARE,           // �ϵ���� ���� ���
			NULL,                               // ����Ʈ����� ����? (�ϵ���� ���� NULL)
			D3D11_CREATE_DEVICE_SINGLETHREADED, // ����� ���� Ȱ��ȭ
			&mFeatureLevel,                     // DX ��� ����
			1,                                  // �迭 ����
			D3D11_SDK_VERSION,                  // DX SDK Version
			&swapChainDesc,                     // SwapChain ����ü ����
			&mSwapChain,
			&mDevice, // ������ ��ġ
			NULL,
			&mDeviceContext // ������ ��ġ ���ؽ�Ʈ
		)))
		{
			LOG_DX_ERROR("Failed to Create DX Device & SwapChain");
			EngineHelper::ShowErrorMessageBox(Hwnd, true);
		}
		LOG_DX_INFO("Device & SwapChain �����Ϸ�");

		Resize(); // ���� Ÿ�� �� ����
	}

	bool Context::Resize()
	{
		DX::ReleaseCOM(mRenderTargetView);
		DX::ReleaseCOM(mDepthStencilBuffer);
		DX::ReleaseCOM(mDepthStencilBuffer);

		if (FAILED(mSwapChain->ResizeBuffers(1, mWindowData.Width, mWindowData.Height, DXGI_FORMAT_R8G8B8A8_UNORM, 0)))
		{
			return false;
		}

		ID3D11Texture2D* backBufferPtr;

		if (FAILED(mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&backBufferPtr))))
		{
			return false;
		}

		if (FAILED(mDevice->CreateRenderTargetView(backBufferPtr, NULL, &mRenderTargetView)))
		{
			return false;
		}
		LOG_DX_INFO("RTV �����Ϸ�");

		backBufferPtr->Release();

		return false;
	}
}
