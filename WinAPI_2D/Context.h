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
		static Context*         s_Context;                  /** DX Context 스태틱 개체 */
		ID3D11Device*           mDevice;                    /** 디바이스 포인터 (리소스 생성) */
		ID3D11DeviceContext*    mDeviceContext;             /** 디바이스 컨텍스트 포인터 (파이프라인 설정) */
		IDXGISwapChain*         mSwapChain;                 /** 스왑체인 포인터 (디스플레이 제어) */
		ID3D11RenderTargetView* mRenderTargetView;          /** 화면에 보여지는 버퍼 개체 (RTV) */
		ID3D11DepthStencilView* mDepthStencilView;          /** 깊이/스텐실 정보 기반 뷰 관리 개체 */
		ID3D11Texture2D*        mDepthStencilBuffer;        /** 2D 이미지 관리 개체 인터페이스 */
		D3D11_VIEWPORT          mViewport;                  /** 렌더링 뷰포트 */
		D3D_FEATURE_LEVEL       mFeatureLevel;              /** DX기능 수준 레벨 */
		int32_t                 mVideoCardMemory;           /** 비디오카드 메모리 용량 */
		WCHAR                   mVideoCardDescription[128]; /** 비디오카드 상세 정보 */
		FWindowData             mWindowData;                /** 윈도우 프로퍼티 */
	};
}
