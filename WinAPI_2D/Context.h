#pragma once
#include "CommonInclude.h"
#include <d3d11.h>

namespace LJG
{
	CLASS_PTR(Context)

	class Context : ICoreAPI
	{
	private:
		Context(const FWindowData& WinData, void* DeviceContext);

	public:
		~Context();

	public:
		static void Create(const FWindowData& WinData, void* DeviceContext);

#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

		void Present();
		void Resize(UINT InWidth, UINT InHeight);

	private:
		bool    InitD3D(HWND Hwnd);
		HRESULT CreateDevice();
		HRESULT CreateGIFactory();
		HRESULT CreateSwapChain(HWND Hwnd);
		HRESULT SetViewport();
		HRESULT SetRenderTarget();

	public:
#pragma region Get
		inline static Context* Get() { return s_Context.get(); }

		inline static ID3D11Device*           GetDevice() { return Get()->mDevice.Get(); }
		inline static ID3D11DeviceContext*    GetDeviceContext() { return Get()->mDeviceContext.Get(); }
		inline static IDXGISwapChain*         GetSwapChain() { return Get()->mSwapChain.Get(); }
		inline static ID3D11RenderTargetView* GetRTV() { return Get()->mRenderTargetView.Get(); }
		inline static ID3D11DepthStencilView* GetDepthStencilView() { return Get()->mDepthStencilView.Get(); }

		inline static CHAR*              GetVideoCardDesc() { return Get()->mVideoCardDescription; }
		inline static const FWindowData& GetWindowData() { return Get()->mWindowData; }
#pragma endregion

	private:
		static ContextUPtr             s_Context;                  /** DX Context 스태틱 개체 */
		ComPtr<ID3D11Device>           mDevice;					   /** 디바이스 포인터 (리소스 생성) */
		ComPtr<ID3D11DeviceContext>    mDeviceContext;             /** 디바이스 컨텍스트 포인터 (파이프라인 설정) */
		ComPtr<IDXGISwapChain>         mSwapChain;                 /** 스왑체인 포인터 (디스플레이 제어) */
		DXGI_SWAP_CHAIN_DESC           mSwapChainDesc;             /** 스왑체인 구조체 */
		ComPtr<ID3D11RenderTargetView> mRenderTargetView;          /** 화면에 보여지는 버퍼 개체 (RTV) */
		ComPtr<ID3D11DepthStencilView> mDepthStencilView;          /** 깊이/스텐실 정보 기반 뷰 관리 개체 */
		ComPtr<ID3D11Texture2D>        mDepthStencilBuffer;        /** 2D 이미지 관리 개체 인터페이스 */
		D3D11_VIEWPORT                 mViewport;                  /** 렌더링 뷰포트 */
		D3D_FEATURE_LEVEL              mFeatureLevel;              /** DX기능 수준 레벨 */
		int32_t                        mVideoCardMemory;           /** 비디오카드 메모리 용량 */
		CHAR                           mVideoCardDescription[128]; /** 비디오카드 상세 정보 */
		FWindowData                    mWindowData;                /** 윈도우 프로퍼티 */

		ComPtr<IDXGIFactory> mGIFactory;
	};

	/**
	 * DirectX11부터는 Device와 Context가 분리됨 (멀티 스레딩 가능)
	 *			Device  	 < - >    Context (Immediate, Deferred)
	 *		Free Thread				Rendering Thread
	 *		리소스 생성				리소스 제어 및 렌더링
	 *
	 *
	 * SwapChain
	 *	전면 및 후면 버퍼(들)을 생성하고 제어
	 *	SwapChain을 생성하기 위해선 SWAP_CHAIN_DESC구조체를 이용해 버퍼 정보를 채워주어야 한다
	 *
	 * RenderTargetView
	 *	렌더링 될 버퍼의 메모리
	 *	이전에 생성된 SwapChain Buffer에서 GetBuffer를 통해 생성한다.
	 *	swapChain->GetBuffer(// BufferIndex, // ID3D11Texture2D고유ID, // 백버퍼 포인터 주소)
	 *
	 */
}
