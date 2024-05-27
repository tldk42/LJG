#include "Context.h"

#include "EngineHelper.h"
#include "Write.h"

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
			// TODO: Clear below code
			constexpr float clearColor[] = {.1f, .2f, .3f, 1.f};
			mDeviceContext->ClearRenderTargetView(mRenderTargetView, clearColor);

#pragma region Font Test
			if (mFont->mTextFormat)
			{
				D2D1_SIZE_F rtSize = mFont->mRenderTarget->GetSize();
				//Draw a grid background.
				int width  = static_cast<int>(rtSize.width);
				int height = static_cast<int>(rtSize.height);

				// 클라이언트 좌표계를 사용하여 RECT를 구성한다.
				mFont->Begin();
				mFont->mTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
				// 단락(페러그래프)설정
				mFont->mTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
				RECT rc1 = {0, 0, width, height / 2};
				mFont->DrawText_A(rc1,
				                  (TCHAR*)L"X축 좌측 정렬, Y축 상단 정렬",
				                  D2D1::ColorF(1, 1, 1, 0.5));

				mFont->mTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
				mFont->mTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
				RECT rc2 = {0, 0, width, height / 2};
				mFont->DrawText_A(rc2, (TCHAR*)L"X축 우측 정렬, Y축 하단 정렬", D2D1::ColorF(1, 1, 1, 0.5));

				mFont->mTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
				mFont->mTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
				RECT rc3 = {0, 0, width, height / 2};
				mFont->DrawText_A(rc3, (TCHAR*)L"X축 중앙 정렬, Y축 중앙 정렬", D2D1::ColorF(1, 1, 1, 0.5));

				mFont->mTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
				mFont->mTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
				RECT rc4 = {0, height / 2, width, height};
				mFont->DrawText_A(rc4, (TCHAR*)L"X축 좌측 정렬, Y축 하단 정렬");

				mFont->mTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
				mFont->mTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
				RECT rc5 = {0, height / 2, width, height};
				mFont->DrawText_A(rc5, (TCHAR*)L"X축 우측 정렬, Y축 상단 정렬");

				mFont->mTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
				mFont->mTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
				RECT rc6 = {0, height / 2, width, height};
				mFont->DrawText_A(rc6, (TCHAR*)L"X축 중앙 정렬, Y축 상단 정렬");


				RECT rc;
				GetClientRect(EngineHelper::GetWindowHandle(), &rc);
				mFont->mTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
				mFont->mTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

				rc.bottom = rc.bottom / 2;
				// bottom 와 right은 레이아웃의 가로/세로 크기이며 재설정 하면 Layout를 다시 생성하여야 한다.
				// top, left는 위치 이기 때문에 다시 생성하지 않아도 된다.
				// 레이아웃 최대 X = left + right
				// 레이아웃 최대 Y = top + bottom
				mFont->SetText(D2D1::Point2F(rc.right, rc.bottom), L"KGCA Game Academy", D2D1::ColorF(1, 1, 0, 1));
				mFont->SetBold(true);
				mFont->SetFontSize(40);
				mFont->SetItalic(true);
				mFont->SetUnderline(true);
				// 레이아웃이 rc.left, rc.top로 이동하여 드로우 된다.
				mFont->DrawText_A(D2D1::Point2F(rc.left, rc.top), D2D1::ColorF(1, 1, 0, 1));

				rc.top = mWindowData.Height / 2;
				mFont->SetText(D2D1::Point2F(rc.right, rc.bottom), L"TBasis Sample", D2D1::ColorF(1, 1, 0, 1));
				mFont->SetBold(false);
				mFont->SetFontSize(70);
				mFont->SetItalic(false);
				mFont->SetUnderline(false);
				mFont->DrawText_A(D2D1::Point2F(rc.left, rc.top), D2D1::ColorF(1, 1, 0, 1));
				mFont->End();
			}
#pragma endregion

			if (FAILED(mSwapChain->Present(mWindowData.bVsync, 0)))
			{
				LOG_DX_ERROR("SwapChain Present Failed");
			}
		}
	}

	void Context::InitD3D(HWND Hwnd)
	{
		LOG_DX_INFO("DX 초기화 시작...");

		// Step 1. SwapChain 정보 구조체 채워넣기 (스왑체인을 생성하기 위해 필요)
		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
		{
			swapChainDesc.BufferCount = 1;
			swapChainDesc.BufferDesc.Width = 1600; // Buffer Width
			swapChainDesc.BufferDesc.Height = 900; // Buffer Height
			swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // 색상 출력 형식
			swapChainDesc.BufferDesc.RefreshRate.Numerator = 60; // FPS 분자
			swapChainDesc.BufferDesc.RefreshRate.Denominator = 1; // FPS 분모
			swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // 버퍼 (렌더링 버퍼)
			swapChainDesc.OutputWindow = Hwnd; // 출력될 윈도우 핸들
			swapChainDesc.SampleDesc.Count = 1; // 멀티 샘플링 개수
			swapChainDesc.SampleDesc.Quality = 0; // 멀티 샘플링 품질
			swapChainDesc.Windowed = !(mWindowData.bFullScreen); // 창 전체 화면 모드
			swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; // Swap이 일어난 이후 버퍼를 Discard
			swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; // 적합한 디스플레이로 자동전환
		}

		// Step 2. Direct3D Device, Context, SwapChain을 한번에 생성(시도)
		if (FAILED(D3D11CreateDeviceAndSwapChain(
			NULL,                                                                  // pAdapter (모니터) : null이면 주 모니터 사용
			D3D_DRIVER_TYPE_HARDWARE,                                              // 하드웨어 가속 사용
			NULL,                                                                  // 소프트웨어로 구동? (하드웨어 사용시 NULL)
			D3D11_CREATE_DEVICE_SINGLETHREADED | D3D11_CREATE_DEVICE_BGRA_SUPPORT, // 디버그 계층 활성화
			&mFeatureLevel,                                                        // DX 기능 수준
			1,                                                                     // 배열 원소
			D3D11_SDK_VERSION,                                                     // DX SDK Version
			&swapChainDesc,                                                        // SwapChain 구조체 정보
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

		// IDXGIFactory* factory;
		// IDXGIAdapter* adapter;
		//
		// if (FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&factory)))) {}
		// if (FAILED(factory->EnumAdapters(0, &adapter))) {}

		// DXGI_ADAPTER_DESC desc;
		// adapter->GetDesc(&desc);
		// // mVideoCardDescription = desc.Description;
		// factory->Release();
		// adapter->Release();

		Resize(); // 렌더 타겟 뷰 생성

		InitFont();
	}

	void Context::InitFont()
	{
		mFont = new Write();
		mSwapChain->GetBuffer(0, __uuidof(IDXGISurface), reinterpret_cast<LPVOID*>(&mSurfaceBackBuffer));
		mFont->Set(EngineHelper::GetWindowHandle(), mWindowData.Width, mWindowData.Height, mSurfaceBackBuffer);
		if (mSurfaceBackBuffer)
		{
			mSurfaceBackBuffer->Release();
		}
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
