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
		static ContextUPtr             s_Context;                  /** DX Context ����ƽ ��ü */
		ComPtr<ID3D11Device>           mDevice;					   /** ����̽� ������ (���ҽ� ����) */
		ComPtr<ID3D11DeviceContext>    mDeviceContext;             /** ����̽� ���ؽ�Ʈ ������ (���������� ����) */
		ComPtr<IDXGISwapChain>         mSwapChain;                 /** ����ü�� ������ (���÷��� ����) */
		DXGI_SWAP_CHAIN_DESC           mSwapChainDesc;             /** ����ü�� ����ü */
		ComPtr<ID3D11RenderTargetView> mRenderTargetView;          /** ȭ�鿡 �������� ���� ��ü (RTV) */
		ComPtr<ID3D11DepthStencilView> mDepthStencilView;          /** ����/���ٽ� ���� ��� �� ���� ��ü */
		ComPtr<ID3D11Texture2D>        mDepthStencilBuffer;        /** 2D �̹��� ���� ��ü �������̽� */
		D3D11_VIEWPORT                 mViewport;                  /** ������ ����Ʈ */
		D3D_FEATURE_LEVEL              mFeatureLevel;              /** DX��� ���� ���� */
		int32_t                        mVideoCardMemory;           /** ����ī�� �޸� �뷮 */
		CHAR                           mVideoCardDescription[128]; /** ����ī�� �� ���� */
		FWindowData                    mWindowData;                /** ������ ������Ƽ */

		ComPtr<IDXGIFactory> mGIFactory;
	};

	/**
	 * DirectX11���ʹ� Device�� Context�� �и��� (��Ƽ ������ ����)
	 *			Device  	 < - >    Context (Immediate, Deferred)
	 *		Free Thread				Rendering Thread
	 *		���ҽ� ����				���ҽ� ���� �� ������
	 *
	 *
	 * SwapChain
	 *	���� �� �ĸ� ����(��)�� �����ϰ� ����
	 *	SwapChain�� �����ϱ� ���ؼ� SWAP_CHAIN_DESC����ü�� �̿��� ���� ������ ä���־�� �Ѵ�
	 *
	 * RenderTargetView
	 *	������ �� ������ �޸�
	 *	������ ������ SwapChain Buffer���� GetBuffer�� ���� �����Ѵ�.
	 *	swapChain->GetBuffer(// BufferIndex, // ID3D11Texture2D����ID, // ����� ������ �ּ�)
	 *
	 */
}
