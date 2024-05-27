#pragma once
#include "CommonInclude.h"
#include <d3d11.h>

namespace LJG
{
	class Write;

	class Context
	{
	public:
		Context() = delete;
		Context(const FWindowData& WinData, void* DeviceContext);
		~Context();

	public:
		static void Create(const FWindowData& WinData, void* DeviceContext);

		void Present();

	private:
		void    InitD3D(HWND Hwnd);
		void    InitFont();
		HRESULT Resize(UINT InWidth, UINT InHeight);
		HRESULT CreateSwapChain(HWND Hwnd);
		void    CreateDeviceAndSwapChain(HWND Hwnd);
		HRESULT CreateGIFactory();
		HRESULT SetViewport();
		HRESULT SetRenderTarget();

	public:
#pragma region Get
		inline static Context* GetContext() { return s_Context; }
		inline static Context* Get() { return s_Context; }

		inline static ID3D11Device*           GetDevice() { return Get()->mDevice; }
		inline static ID3D11DeviceContext*    GetDeviceContext() { return Get()->mDeviceContext; }
		inline static IDXGISwapChain*         GetSwapChain() { return Get()->mSwapChain; }
		inline static ID3D11RenderTargetView* GetRTV() { return Get()->mRenderTargetView; }
		inline static ID3D11DepthStencilView* GetDepthStencilView() { return Get()->mDepthStencilView; }

		inline static CHAR*              GetVideoCardDesc() { return Get()->mVideoCardDescription; }
		inline static const FWindowData& GetWindowData() { return Get()->mWindowData; }
#pragma endregion

	private:
		static Context*         s_Context;                  /** DX Context ����ƽ ��ü */
		ID3D11Device*           mDevice;                    /** ����̽� ������ (���ҽ� ����) */
		ID3D11DeviceContext*    mDeviceContext;             /** ����̽� ���ؽ�Ʈ ������ (���������� ����) */
		IDXGISwapChain*         mSwapChain;                 /** ����ü�� ������ (���÷��� ����) */
		DXGI_SWAP_CHAIN_DESC    mSwapChainDesc; /** ����ü�� ����ü */
		ID3D11RenderTargetView* mRenderTargetView;          /** ȭ�鿡 �������� ���� ��ü (RTV) */
		ID3D11DepthStencilView* mDepthStencilView;          /** ����/���ٽ� ���� ��� �� ���� ��ü */
		ID3D11Texture2D*        mDepthStencilBuffer;        /** 2D �̹��� ���� ��ü �������̽� */
		D3D11_VIEWPORT          mViewport;                  /** ������ ����Ʈ */
		D3D_FEATURE_LEVEL       mFeatureLevel;              /** DX��� ���� ���� */
		int32_t                 mVideoCardMemory;           /** ����ī�� �޸� �뷮 */
		CHAR                    mVideoCardDescription[128]; /** ����ī�� �� ���� */
		FWindowData             mWindowData;                /** ������ ������Ƽ */

		IDXGIFactory* mGIFactory;

		Write*         mFont;
		IDXGISurface1* mSurfaceBackBuffer;

		friend class Window;
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
