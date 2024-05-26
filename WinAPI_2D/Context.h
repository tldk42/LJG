#pragma once
#include "CommonInclude.h"
#include <d3d11.h>

namespace LJG
{
	namespace DX
	{
		template <typename T>
		void ReleaseCOM(T* ComPtr)
		{
			if (ComPtr)
			{
				ComPtr->Release();
				ComPtr = nullptr;
			}
		}
	}

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
		void InitD3D(HWND Hwnd);
		bool Resize();

	public:
#pragma region Get
		inline static Context* GetContext() { return s_Context; }
		inline static Context* Get() { return s_Context; }

		inline static ID3D11Device*           GetDevice() { return Get()->mDevice; }
		inline static ID3D11DeviceContext*    GetDeviceContext() { return Get()->mDeviceContext; }
		inline static IDXGISwapChain*         GetSwapChain() { return Get()->mSwapChain; }
		inline static ID3D11RenderTargetView* GetRTV() { return Get()->mRenderTargetView; }
		inline static ID3D11DepthStencilView* GetDepthStencilView() { return Get()->mDepthStencilView; }

		inline static const char*        GetVideoCardDesc() { return Get()->mVideoCardDescription; }
		inline static const FWindowData& GetWindowData() { return Get()->mWindowData; }
#pragma endregion

	private:
		static Context*         s_Context;                  /** DX Context ����ƽ ��ü */
		ID3D11Device*           mDevice;                    /** ����̽� ������ (���ҽ� ����) */
		ID3D11DeviceContext*    mDeviceContext;             /** ����̽� ���ؽ�Ʈ ������ (���������� ����) */
		IDXGISwapChain*         mSwapChain;                 /** ����ü�� ������ (���÷��� ����) */
		ID3D11RenderTargetView* mRenderTargetView;          /** ȭ�鿡 �������� ���� ��ü (RTV) */
		ID3D11DepthStencilView* mDepthStencilView;          /** ����/���ٽ� ���� ��� �� ���� ��ü */
		ID3D11Texture2D*        mDepthStencilBuffer;        /** 2D �̹��� ���� ��ü �������̽� */
		D3D11_VIEWPORT          mViewport;                  /** ������ ����Ʈ */
		D3D_FEATURE_LEVEL       mFeatureLevel;              /** DX��� ���� ���� */
		int32_t                 mVideoCardMemory;           /** ����ī�� �޸� �뷮 */
		WCHAR                   mVideoCardDescription[128]; /** ����ī�� �� ���� */
		FWindowData             mWindowData;                /** ������ ������Ƽ */
	};
}
