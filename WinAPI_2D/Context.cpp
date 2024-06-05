#include "Context.h"

#include "EngineHelper.h"
#include "DXWrite.h"

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
		if (!InitD3D(static_cast<HWND>(DeviceContext)))
		{
			LOG_DX_ERROR("FAILED");
		}
	}

	Context::~Context()
	{
		ReleaseContext();
	}

	void Context::Create(const FWindowData& WinData, void* DeviceContext)
	{
		s_Context = new Context(WinData, DeviceContext);

		s_Context->Initialize();
	}

	void Context::Initialize()
	{
		// static_assert(Window::GetWindow(), L"윈도우 초기화 안됨");

		Window::GetWindow()->OnResize.emplace_back([this](UINT Width, UINT Height){
			Resize(Width, Height);
		});
	}

	void Context::Update(float DeltaTime) {}

	void Context::Render()
	{
		Present();
	}

	void Context::Release() {}

	bool Context::InitD3D(HWND Hwnd)
	{
		LOG_DX_TRACE("DirectX Initialization Start...");

		// Step 1. D3D Device, DeviceContext 반환
		if (FAILED(CreateDevice()))
		{
			LOG_DX_ERROR("Failed to Create DX Device & Device Context");
			EngineHelper::ShowErrorMessageBox(Hwnd, true);
			return false;
		}
		LOG_DX_TRACE("1. Device, DeviceContext...");

		// Step 2. DirectX Graphic Infrastructure 생성
		if (FAILED(CreateGIFactory()))
		{
			LOG_DX_ERROR("Failed to Create DXGI");
			EngineHelper::ShowErrorMessageBox(Hwnd, true);
			return false;
		}
		LOG_DX_TRACE("2. DirectX Graphic Infrastructure...");

		// Step 3. SwapChain 정보 생성 및 SwapChain 반환
		if (FAILED(CreateSwapChain(Hwnd)))
		{
			LOG_DX_ERROR("Failed to Create SwapChain");
			EngineHelper::ShowErrorMessageBox(Hwnd, true);
			return false;
		}
		LOG_DX_TRACE("3. SwapChain...");

		Resize(mWindowData.Width, mWindowData.Height); // 렌더 타겟 뷰 생성


		// Step 6. Alt + Enter로 자동 창변환을 제어
		if (FAILED(mGIFactory->MakeWindowAssociation(Hwnd, DXGI_MWA_NO_WINDOW_CHANGES | DXGI_MWA_NO_ALT_ENTER)))
		{
			LOG_DX_ERROR("Failed to Make Association");
			EngineHelper::ShowErrorMessageBox(Hwnd, true);
			return false;
		}

		return true;
	}

	HRESULT Context::CreateDevice()
	{
		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
		};

		HRESULT result = D3D11CreateDevice(
			nullptr,                  // 주 모니터 사용
			D3D_DRIVER_TYPE_HARDWARE, // 하드웨어 가속 사용
			nullptr,                  // 하드웨어 사용
#ifdef _DEBUG
			D3D11_CREATE_DEVICE_DEBUG | // 디버그 활성화
#endif
			D3D11_CREATE_DEVICE_SINGLETHREADED | D3D11_CREATE_DEVICE_BGRA_SUPPORT, // flags
			featureLevels,                                                         // 기능 수준
			ARRAYSIZE(featureLevels),                                              // 기능 배열 개수
			D3D11_SDK_VERSION,                                                     // DX Version
			mDevice.GetAddressOf(),                                                              // (Out) Device
			&mFeatureLevel,                                                        // (Out) Features
			mDeviceContext.GetAddressOf());                                                      // (Out) DeviceContext

		if (FAILED(result) || mFeatureLevel < D3D_FEATURE_LEVEL_11_0)
		{
			mDeviceContext.Reset();
			mDevice.Reset();
			LOG_DX_ERROR("Failed to Create Device");
			EngineHelper::ShowErrorMessageBox(nullptr, true);
		}

		return result;
	}

	HRESULT Context::CreateGIFactory()
	{
		if (!mDevice)
			return E_FAIL;

		ComPtr<IDXGIDevice>  DXGIDevice;
		ComPtr<IDXGIAdapter> DXGIAdapter;

		HRESULT result = mDevice->QueryInterface(__uuidof(IDXGIDevice),
		                                         reinterpret_cast<void**>(DXGIDevice.GetAddressOf()));

		result = DXGIDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(DXGIAdapter.GetAddressOf()));

		result = DXGIAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(mGIFactory.GetAddressOf()));

		if (SUCCEEDED(mGIFactory->EnumAdapters(0, &DXGIAdapter))) // 첫번째 그래픽카드 장치 반환
		{
			DXGI_ADAPTER_DESC desc;
			DXGIAdapter->GetDesc(&desc);
			size_t stringLength;

			wcstombs_s(&stringLength, mVideoCardDescription, 128, desc.Description, 128);
			LOG_DX_TRACE("그래픽카드: {}, 메모리: {:d}", mVideoCardDescription, desc.DedicatedVideoMemory / (1 << 20));
		}

		DXGIDevice.Reset();
		DXGIAdapter.Reset();

		return result;
	}

	HRESULT Context::CreateSwapChain(HWND Hwnd)
	{
		ZeroMemory(&mSwapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
		{
			mSwapChainDesc.BufferCount = 1;
			mSwapChainDesc.BufferDesc.Width = mWindowData.Width; // Buffer Width
			mSwapChainDesc.BufferDesc.Height = mWindowData.Height; // Buffer Height
			mSwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // 색상 출력 형식
			mSwapChainDesc.BufferDesc.RefreshRate.Numerator = 60; // FPS 분자 TODO: 고정 주사율 설정
			mSwapChainDesc.BufferDesc.RefreshRate.Denominator = 1; // FPS 분모
			mSwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // 버퍼 (렌더링 버퍼)
			mSwapChainDesc.OutputWindow = Hwnd; // 출력될 윈도우 핸들
			mSwapChainDesc.SampleDesc.Count = 1; // 멀티 샘플링 개수
			mSwapChainDesc.SampleDesc.Quality = 0; // 멀티 샘플링 품질
			mSwapChainDesc.Windowed = !(mWindowData.bFullScreen); // 창 전체 화면 모드
			mSwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; // Swap이 일어난 이후 버퍼를 Discard
			mSwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; // 적합한 디스플레이로 자동전환
		}

		return mGIFactory->CreateSwapChain(mDevice.Get(), &mSwapChainDesc, mSwapChain.GetAddressOf());
	}

	void Context::Resize(UINT InWidth, UINT InHeight)
	{
		if (mDevice.Get())
		{
			if (DXWrite::Initialized())
			{
				DXWrite::Get()->DiscardDeviceResources();
			}
			mDeviceContext->OMSetRenderTargets(0, nullptr, nullptr);

			mRenderTargetView.Reset();

			HRESULT result = mSwapChain->ResizeBuffers(mSwapChainDesc.BufferCount,
			                                           InWidth, InHeight,
			                                           mSwapChainDesc.BufferDesc.Format,
			                                           mSwapChainDesc.Flags);
			mSwapChain->GetDesc(&mSwapChainDesc);

			if (result != S_OK)
			{
				LOG_DX_FATAL("DS");
			}

			SetRenderTarget();
			SetViewport();

			mWindowData.Width  = InWidth;
			mWindowData.Height = InHeight;
		}
	}

	HRESULT Context::SetRenderTarget()
	{
		ComPtr<ID3D11Texture2D> backBuffer;
		HRESULT                 result = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
		                                       reinterpret_cast<LPVOID*>(backBuffer.GetAddressOf()));
		if (FAILED(result))
		{
			EngineHelper::ShowErrorMessageBox(nullptr, false);
		}

		result = mDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, mRenderTargetView.GetAddressOf());
		if (FAILED(result))
		{
			EngineHelper::ShowErrorMessageBox(nullptr, false);
		}

		backBuffer.Reset();

		mDeviceContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), nullptr);
		return result;
	}

	HRESULT Context::SetViewport()
	{
		mViewport.Width    = mSwapChainDesc.BufferDesc.Width;
		mViewport.Height   = mSwapChainDesc.BufferDesc.Height;
		mViewport.MinDepth = 0.f;
		mViewport.MaxDepth = 1.f;
		mViewport.TopLeftX = 0;
		mViewport.TopLeftY = 0;
		mDeviceContext->RSSetViewports(1, &mViewport);

		return S_OK;
	}

	void Context::Present()
	{
		if (mSwapChain.Get())
		{
			if (FAILED(mSwapChain->Present(mWindowData.bVsync, 0)))
			{
				LOG_DX_ERROR("SwapChain Present Failed");
			}
		}
	}

	void Context::ReleaseContext()
	{
		// ReleaseCOM(mDevice.);
		// ReleaseCOM(mDeviceContext);
		// ReleaseCOM(mSwapChain);
		// ReleaseCOM(mRenderTargetView);
		// ReleaseCOM(mDepthStencilView);
		// ReleaseCOM(mDepthStencilBuffer);
		// ReleaseCOM(mDepthStencilView);
	}
}
