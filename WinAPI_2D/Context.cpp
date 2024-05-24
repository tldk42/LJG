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
		LOG_DX_INFO("DX 초기화 시작...");

		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

		swapChainDesc.BufferCount                        = 1;
		swapChainDesc.BufferDesc.Width                   = 1600;                            // Buffer Width
		swapChainDesc.BufferDesc.Height                  = 900;                             // Buffer Height
		swapChainDesc.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;      // 색상 출력 형식
		swapChainDesc.BufferDesc.RefreshRate.Numerator   = 60;                              // FPS 분자
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;                               // FPS 분모
		swapChainDesc.BufferUsage                        = DXGI_USAGE_RENDER_TARGET_OUTPUT; // 버퍼 (렌더링 버퍼)
		swapChainDesc.OutputWindow                       = Hwnd;                            // 출력될 윈도우 핸들
		swapChainDesc.SampleDesc.Count                   = 1;                               // 멀티 샘플링 개수
		swapChainDesc.SampleDesc.Quality                 = 0;                               // 멀티 샘플링 품질
		swapChainDesc.Windowed                           = !(mWindowData.bFullScreen);      // 창 전체 화면 모드
		swapChainDesc.SwapEffect                         = DXGI_SWAP_EFFECT_DISCARD;
		swapChainDesc.Flags                              = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		if (FAILED(D3D11CreateDeviceAndSwapChain(
			NULL,                               // pAdapter (모니터) : null이면 주 모니터 사용
			D3D_DRIVER_TYPE_HARDWARE,           // 하드웨어 가속 사용
			NULL,                               // 소프트웨어로 구동? (하드웨어 사용시 NULL)
			D3D11_CREATE_DEVICE_SINGLETHREADED, // 디버그 계층 활성화
			&mFeatureLevel,                     // DX 기능 수준
			1,                                  // 배열 원소
			D3D11_SDK_VERSION,                  // DX SDK Version
			&swapChainDesc,                     // SwapChain 구조체 정보
			&mSwapChain,
			&mDevice, // 생성한 장치
			NULL,
			&mDeviceContext // 생성된 장치 컨텍스트
		)))
		{
			LOG_DX_ERROR("Failed to Create DX Device & SwapChain");
			EngineHelper::ShowErrorMessageBox(Hwnd, true);
		}
		LOG_DX_INFO("Device & SwapChain 생성완료");

		Resize(); // 렌더 타겟 뷰 생성
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
		LOG_DX_INFO("RTV 생성완료");

		backBufferPtr->Release();

		return false;
	}
}
