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

				// Ŭ���̾�Ʈ ��ǥ�踦 ����Ͽ� RECT�� �����Ѵ�.
				mFont->Begin();
				mFont->mTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
				// �ܶ�(�䷯�׷���)����
				mFont->mTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
				RECT rc1 = {0, 0, width, height / 2};
				mFont->DrawText_A(rc1,
				                  (TCHAR*)L"X�� ���� ����, Y�� ��� ����",
				                  D2D1::ColorF(1, 1, 1, 0.5));

				mFont->mTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
				mFont->mTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
				RECT rc2 = {0, 0, width, height / 2};
				mFont->DrawText_A(rc2, (TCHAR*)L"X�� ���� ����, Y�� �ϴ� ����", D2D1::ColorF(1, 1, 1, 0.5));

				mFont->mTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
				mFont->mTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
				RECT rc3 = {0, 0, width, height / 2};
				mFont->DrawText_A(rc3, (TCHAR*)L"X�� �߾� ����, Y�� �߾� ����", D2D1::ColorF(1, 1, 1, 0.5));

				mFont->mTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
				mFont->mTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
				RECT rc4 = {0, height / 2, width, height};
				mFont->DrawText_A(rc4, (TCHAR*)L"X�� ���� ����, Y�� �ϴ� ����");

				mFont->mTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
				mFont->mTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
				RECT rc5 = {0, height / 2, width, height};
				mFont->DrawText_A(rc5, (TCHAR*)L"X�� ���� ����, Y�� ��� ����");

				mFont->mTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
				mFont->mTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
				RECT rc6 = {0, height / 2, width, height};
				mFont->DrawText_A(rc6, (TCHAR*)L"X�� �߾� ����, Y�� ��� ����");


				RECT rc;
				GetClientRect(EngineHelper::GetWindowHandle(), &rc);
				mFont->mTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
				mFont->mTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

				rc.bottom = rc.bottom / 2;
				// bottom �� right�� ���̾ƿ��� ����/���� ũ���̸� �缳�� �ϸ� Layout�� �ٽ� �����Ͽ��� �Ѵ�.
				// top, left�� ��ġ �̱� ������ �ٽ� �������� �ʾƵ� �ȴ�.
				// ���̾ƿ� �ִ� X = left + right
				// ���̾ƿ� �ִ� Y = top + bottom
				mFont->SetText(D2D1::Point2F(rc.right, rc.bottom), L"KGCA Game Academy", D2D1::ColorF(1, 1, 0, 1));
				mFont->SetBold(true);
				mFont->SetFontSize(40);
				mFont->SetItalic(true);
				mFont->SetUnderline(true);
				// ���̾ƿ��� rc.left, rc.top�� �̵��Ͽ� ��ο� �ȴ�.
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
		LOG_DX_INFO("DX �ʱ�ȭ ����...");

		// Step 1. SwapChain ���� ����ü ä���ֱ� (����ü���� �����ϱ� ���� �ʿ�)
		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
		{
			swapChainDesc.BufferCount = 1;
			swapChainDesc.BufferDesc.Width = 1600; // Buffer Width
			swapChainDesc.BufferDesc.Height = 900; // Buffer Height
			swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // ���� ��� ����
			swapChainDesc.BufferDesc.RefreshRate.Numerator = 60; // FPS ����
			swapChainDesc.BufferDesc.RefreshRate.Denominator = 1; // FPS �и�
			swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // ���� (������ ����)
			swapChainDesc.OutputWindow = Hwnd; // ��µ� ������ �ڵ�
			swapChainDesc.SampleDesc.Count = 1; // ��Ƽ ���ø� ����
			swapChainDesc.SampleDesc.Quality = 0; // ��Ƽ ���ø� ǰ��
			swapChainDesc.Windowed = !(mWindowData.bFullScreen); // â ��ü ȭ�� ���
			swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; // Swap�� �Ͼ ���� ���۸� Discard
			swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; // ������ ���÷��̷� �ڵ���ȯ
		}

		// Step 2. Direct3D Device, Context, SwapChain�� �ѹ��� ����(�õ�)
		if (FAILED(D3D11CreateDeviceAndSwapChain(
			NULL,                                                                  // pAdapter (�����) : null�̸� �� ����� ���
			D3D_DRIVER_TYPE_HARDWARE,                                              // �ϵ���� ���� ���
			NULL,                                                                  // ����Ʈ����� ����? (�ϵ���� ���� NULL)
			D3D11_CREATE_DEVICE_SINGLETHREADED | D3D11_CREATE_DEVICE_BGRA_SUPPORT, // ����� ���� Ȱ��ȭ
			&mFeatureLevel,                                                        // DX ��� ����
			1,                                                                     // �迭 ����
			D3D11_SDK_VERSION,                                                     // DX SDK Version
			&swapChainDesc,                                                        // SwapChain ����ü ����
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

		Resize(); // ���� Ÿ�� �� ����

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
		LOG_DX_INFO("RTV �����Ϸ�");

		backBufferPtr->Release();

		return false;
	}
}
