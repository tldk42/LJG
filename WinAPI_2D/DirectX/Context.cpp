#include "Context.h"

#include "Helper/UDXHelper.h"
#include "Helper/EngineHelper.h"
#include "DXWrite.h"
#include "Window.h"

namespace LJG
{
	ContextUPtr Context::s_Context = nullptr;

	Context::Context()
		: mDevice(nullptr),
		  mDeviceContext(nullptr),
		  mSwapChain(nullptr),
		  mRenderTargetView(nullptr),
		  mDepthStencilView(nullptr),
		  mDepthStencilBuffer(nullptr),
		  mViewport(),
		  mFeatureLevel(D3D_FEATURE_LEVEL_11_0),
		  mVideoCardDescription{}
	{
		Context::Initialize();
	}

	Context::~Context()
	{
		Context::Release();
	}

	void Context::Create()
	{
		s_Context.reset(new Context());
	}

	void Context::Initialize()
	{
		LOG_DX_TRACE("DirectX Initialization Start...");

		// Step 1. DirectX Graphic Infrastructure 생성
		CHECK_RESULT(CreateGIFactory());
		LOG_DX_TRACE("1. DirectX Graphic Infrastructure...");

		// Step 2. D3D Device, DeviceContext 반환
		CHECK_RESULT(CreateDevice());
		LOG_DX_TRACE("2. Device, DeviceContext...");

		// Step 3. SwapChain 정보 생성 및 SwapChain 반환
		CHECK_RESULT(CreateSwapChain());
		LOG_DX_TRACE("3. SwapChain...");

		// Step 4. RenderTargetView, Viewport 생성
		OnResizeCallback(GetWindowWidth(), GetWindowHeight());
		LOG_DX_TRACE("4. RTV..., Viewport...");

		// Step 5. Alt + Enter로 자동 창변환을 제어
		CHECK_RESULT(mGIFactory->MakeWindowAssociation(GetHWND(), DXGI_MWA_NO_WINDOW_CHANGES | DXGI_MWA_NO_ALT_ENTER));

		Window::GetWindow()->OnResize.Bind([this](UINT Width, UINT Height){
			OnResizeCallback(Width, Height);
		});
	}

	void Context::Update(float InDeltaTime)
	{}

	void Context::Render()
	{
		// TODO: ImGui에서 렌더링 마다 초기화 해버리기 때문에 관리해 줘야함
		mDeviceContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), nullptr);
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

	HRESULT Context::CreateGIFactory()
	{
		ComPtr<IDXGIAdapter> DXGIAdapter;

		CHECK_RESULT(CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(mGIFactory.GetAddressOf())));

		// 첫번째 그래픽카드 장치 반환
		CHECK_RESULT(mGIFactory->EnumAdapters(0, DXGIAdapter.GetAddressOf()));
		{
			DXGI_ADAPTER_DESC desc;
			CHECK_RESULT(DXGIAdapter->GetDesc(&desc));

			size_t stringLength;
			wcstombs_s(&stringLength, mVideoCardDescription, 128, desc.Description, 128);

			LOG_DX_TRACE("그래픽카드: {}, 메모리: {:d}", mVideoCardDescription, desc.DedicatedVideoMemory / (1 << 20));
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
			nullptr,                  // 주 모니터 사용
			D3D_DRIVER_TYPE_HARDWARE, // 하드웨어 가속 사용
			nullptr,                  // 하드웨어 사용
#ifdef _DEBUG
			D3D11_CREATE_DEVICE_DEBUG | // 디버그 활성화
#endif
			D3D11_CREATE_DEVICE_BGRA_SUPPORT, // flags
			featureLevels,                    // 기능 수준
			ARRAYSIZE(featureLevels),         // 기능 배열 개수
			D3D11_SDK_VERSION,                // DX Version
			mDevice.GetAddressOf(),           // (Out) Device
			&mFeatureLevel,                   // (Out) Features
			mDeviceContext.GetAddressOf()));  // (Out) DeviceContext

		if (mFeatureLevel < D3D_FEATURE_LEVEL_11_0)
		{
			mDeviceContext = nullptr;
			mDevice        = nullptr;
			LOG_DX_ERROR("Failed to Create Device");
			EngineHelper::ShowErrorMessageBox(nullptr, true);
		}

		return S_OK;
	}

	HRESULT Context::CreateSwapChain()
	{
		ZeroMemory(&mSwapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
		{
			mSwapChainDesc.BufferCount                        = 1;
			mSwapChainDesc.BufferDesc.Width                   = GetWindowWidth(); // Buffer Width
			mSwapChainDesc.BufferDesc.Height                  = GetWindowHeight(); // Buffer Height
			mSwapChainDesc.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM; // 색상 출력 형식
			mSwapChainDesc.BufferDesc.RefreshRate.Numerator   = 60; // FPS 분자 TODO: 고정 주사율 설정
			mSwapChainDesc.BufferDesc.RefreshRate.Denominator = 1; // FPS 분모
			mSwapChainDesc.BufferUsage                        = DXGI_USAGE_RENDER_TARGET_OUTPUT; // 버퍼 (렌더링 버퍼)
			mSwapChainDesc.OutputWindow                       = GetHWND(); // 출력될 윈도우 핸들
			mSwapChainDesc.SampleDesc.Count                   = 1; // 멀티 샘플링 개수
			mSwapChainDesc.SampleDesc.Quality                 = 0; // 멀티 샘플링 품질
			mSwapChainDesc.Windowed                           = !IsFullScreen(); // 창 전체 화면 모드
			mSwapChainDesc.SwapEffect                         = DXGI_SWAP_EFFECT_DISCARD; // Swap이 일어난 이후 버퍼를 Discard
			mSwapChainDesc.Flags                              = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; // 적합한 디스플레이로 자동전환
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
			SetViewport(mSwapChainDesc.BufferDesc.Width, mSwapChainDesc.BufferDesc.Height);
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

	void Context::SetViewport(UINT InWidth, UINT InHeight)
	{
		mViewport.Width    = static_cast<float_t>(InWidth);
		mViewport.Height   = static_cast<float_t>(InHeight);
		mViewport.MinDepth = 0.f;
		mViewport.MaxDepth = 1.f;
		mViewport.TopLeftX = 0;
		mViewport.TopLeftY = 0;
		mDeviceContext->RSSetViewports(1, &mViewport);

		mViewportSize = {static_cast<float>(InWidth), static_cast<float>(InHeight)};
	}

	void Context::Present() const
	{
		assert(mSwapChain.Get());

		CHECK_RESULT(mSwapChain->Present(IsVsyncEnabled(), 0));
	}
}
