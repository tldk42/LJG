#include "Context.h"

#include "Helper/UDXHelper.h"
#include "Helper/EngineHelper.h"
#include "DXWrite.h"
#include "Window.h"

namespace LJG
{
	ContextUPtr Context::s_Context = nullptr;

	Context::Context(const FWindowData& InWinData, void* InDeviceContext)
		: mDevice(nullptr),
		  mDeviceContext(nullptr),
		  mSwapChain(nullptr),
		  mRenderTargetView(nullptr),
		  mDepthStencilView(nullptr),
		  mDepthStencilBuffer(nullptr),
		  mViewport(),
		  mFeatureLevel(D3D_FEATURE_LEVEL_11_0),
		  mVideoCardDescription{},
		  mWindowData(InWinData)

	{
		if (!InitD3D(static_cast<HWND>(InDeviceContext)))
		{
			LOG_DX_ERROR("FAILED");
		}
	}

	Context::~Context()
	{
		Context::Release();
	}

	void Context::Create(const FWindowData& InWinData, void* InDeviceContext)
	{
		s_Context.reset(new Context(InWinData, InDeviceContext));

		s_Context->Initialize();
	}

	void Context::Initialize()
	{
		Window::GetWindow()->OnResize.emplace_back([this](UINT Width, UINT Height){
			OnResizeCallback(Width, Height);
		});
	}

	void Context::Update(float InDeltaTime) {}

	void Context::Render()
	{
		Present();
	}

	void Context::Release()
	{
		mDepthStencilBuffer = nullptr;
		mDepthStencilView   = nullptr;
		mRenderTargetView   = nullptr;
		mSwapChain          = nullptr;
		mGIFactory          = nullptr;
		mDeviceContext      = nullptr;

		ComPtr<ID3D11Debug> debug;
		if (mDevice.Get() && SUCCEEDED(mDevice->QueryInterface(IID_PPV_ARGS(&debug))))
		{
			debug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
		}
		mDevice = nullptr;
	}

	bool Context::InitD3D(HWND InHwnd)
	{
		LOG_DX_TRACE("DirectX Initialization Start...");

		// Step 1. DirectX Graphic Infrastructure ����
		CHECK_RESULT(CreateGIFactory());
		LOG_DX_TRACE("1. DirectX Graphic Infrastructure...");

		// Step 2. D3D Device, DeviceContext ��ȯ
		CHECK_RESULT(CreateDevice());
		LOG_DX_TRACE("2. Device, DeviceContext...");

		// Step 3. SwapChain ���� ���� �� SwapChain ��ȯ
		CHECK_RESULT(CreateSwapChain(InHwnd));
		LOG_DX_TRACE("3. SwapChain...");

		// Step 4. RenderTargetView, Viewport ����
		OnResizeCallback(mWindowData.Width, mWindowData.Height);
		LOG_DX_TRACE("4. RTV..., Viewport...");

		// Step 5. Alt + Enter�� �ڵ� â��ȯ�� ����
		CHECK_RESULT(mGIFactory->MakeWindowAssociation(InHwnd, DXGI_MWA_NO_WINDOW_CHANGES | DXGI_MWA_NO_ALT_ENTER));
		return true;
	}

	HRESULT Context::CreateGIFactory()
	{
		ComPtr<IDXGIAdapter> DXGIAdapter;

		CHECK_RESULT(CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(mGIFactory.GetAddressOf())));

		// ù��° �׷���ī�� ��ġ ��ȯ
		CHECK_RESULT(mGIFactory->EnumAdapters(0, DXGIAdapter.GetAddressOf()));
		{
			DXGI_ADAPTER_DESC desc;
			CHECK_RESULT(DXGIAdapter->GetDesc(&desc));

			size_t stringLength;
			wcstombs_s(&stringLength, mVideoCardDescription, 128, desc.Description, 128);

			LOG_DX_TRACE("�׷���ī��: {}, �޸�: {:d}", mVideoCardDescription, desc.DedicatedVideoMemory / (1 << 20));
		}

		DXGIAdapter = nullptr;

		return S_OK;
	}

	HRESULT Context::CreateDevice()
	{
		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
		};

		CHECK_RESULT(D3D11CreateDevice(
			nullptr,                  // �� ����� ���
			D3D_DRIVER_TYPE_HARDWARE, // �ϵ���� ���� ���
			nullptr,                  // �ϵ���� ���
#ifdef _DEBUG
			D3D11_CREATE_DEVICE_DEBUG | // ����� Ȱ��ȭ
#endif
			D3D11_CREATE_DEVICE_BGRA_SUPPORT, // flags
			featureLevels,                                                         // ��� ����
			ARRAYSIZE(featureLevels),                                              // ��� �迭 ����
			D3D11_SDK_VERSION,                                                     // DX Version
			mDevice.GetAddressOf(),                                                              // (Out) Device
			&mFeatureLevel,                                                        // (Out) Features
			mDeviceContext.GetAddressOf()));                                                      // (Out) DeviceContext

		if (mFeatureLevel < D3D_FEATURE_LEVEL_11_0)
		{
			mDeviceContext = nullptr;
			mDevice        = nullptr;
			LOG_DX_ERROR("Failed to Create Device");
			EngineHelper::ShowErrorMessageBox(nullptr, true);
		}

		return S_OK;
	}

	HRESULT Context::CreateSwapChain(HWND InHwnd)
	{
		ZeroMemory(&mSwapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
		{
			mSwapChainDesc.BufferCount                        = 1;
			mSwapChainDesc.BufferDesc.Width                   = mWindowData.Width; // Buffer Width
			mSwapChainDesc.BufferDesc.Height                  = mWindowData.Height; // Buffer Height
			mSwapChainDesc.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM; // ���� ��� ����
			mSwapChainDesc.BufferDesc.RefreshRate.Numerator   = 60; // FPS ���� TODO: ���� �ֻ��� ����
			mSwapChainDesc.BufferDesc.RefreshRate.Denominator = 1; // FPS �и�
			mSwapChainDesc.BufferUsage                        = DXGI_USAGE_RENDER_TARGET_OUTPUT; // ���� (������ ����)
			mSwapChainDesc.OutputWindow                       = InHwnd; // ��µ� ������ �ڵ�
			mSwapChainDesc.SampleDesc.Count                   = 1; // ��Ƽ ���ø� ����
			mSwapChainDesc.SampleDesc.Quality                 = 0; // ��Ƽ ���ø� ǰ��
			mSwapChainDesc.Windowed                           = !(mWindowData.bFullScreen); // â ��ü ȭ�� ���
			mSwapChainDesc.SwapEffect                         = DXGI_SWAP_EFFECT_DISCARD; // Swap�� �Ͼ ���� ���۸� Discard
			mSwapChainDesc.Flags                              = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; // ������ ���÷��̷� �ڵ���ȯ
		}

		CHECK_RESULT(mGIFactory->CreateSwapChain(mDevice.Get(), &mSwapChainDesc, mSwapChain.GetAddressOf()));
		return S_OK;
	}

	void Context::OnResizeCallback(UINT InWidth, UINT InHeight)
	{
		if (mDevice.Get())
		{
			if (DXWrite::Initialized())
			{
				DXWrite::Get()->DiscardDeviceResources();
			}
			mDeviceContext->OMSetRenderTargets(0, nullptr, nullptr);

			mRenderTargetView = nullptr;

			CHECK_RESULT(mSwapChain->ResizeBuffers(mSwapChainDesc.BufferCount,
												   InWidth, InHeight,
												   mSwapChainDesc.BufferDesc.Format,
												   mSwapChainDesc.Flags));
			mSwapChain->GetDesc(&mSwapChainDesc);

			SetRenderTarget();
			SetViewport();

			mWindowData.Width  = InWidth;
			mWindowData.Height = InHeight;
		}
	}

	void Context::SetRenderTarget()
	{
		ComPtr<ID3D11Texture2D> backBuffer;
		CHECK_RESULT(mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
										   reinterpret_cast<LPVOID*>(backBuffer.GetAddressOf())));
		CHECK_RESULT(mDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, mRenderTargetView.GetAddressOf()));

		mDeviceContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), nullptr);

		backBuffer = nullptr;
	}

	void Context::SetViewport()
	{
		mViewport.Width    = static_cast<float_t>(mSwapChainDesc.BufferDesc.Width);
		mViewport.Height   = static_cast<float_t>(mSwapChainDesc.BufferDesc.Height);
		mViewport.MinDepth = 0.f;
		mViewport.MaxDepth = 1.f;
		mViewport.TopLeftX = 0;
		mViewport.TopLeftY = 0;
		mDeviceContext->RSSetViewports(1, &mViewport);
	}

	void Context::Present() const
	{
		assert(mSwapChain.Get());

		CHECK_RESULT(mSwapChain->Present(mWindowData.bVsync, 0));
	}
}
