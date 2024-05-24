#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

namespace LJG
{
	using namespace DirectX;

	class D3D11
	{
	public:
		D3D11();
		~D3D11();

	private:
		ID3D11Device*            mD3D;
		ID3D11DeviceContext*     mD3DDevice;
		IDXGISwapChain*          mSwapChain;
		ID3D11RenderTargetView*  mRenderTargetView;
		ID3D11Texture2D*         mDepthStencilBuffer;
		ID3D11DepthStencilState* mDepthStencilState;
		ID3D11DepthStencilView*  mDepthStencilView;
		ID3D11RasterizerState*   mRasterState;

		DXGI_SWAP_CHAIN_DESC          mSwapChainDesc;
		D3D11_TEXTURE2D_DESC          mDepthBufferDesc;
		D3D11_DEPTH_STENCIL_DESC      mDepthStencilDesc;
		D3D11_DEPTH_STENCIL_VIEW_DESC mDepthStencilViewDesc;

		XMMATRIX          mProjectionMatrix;
		XMMATRIX          mWorldMatrix;
		XMMATRIX          mOrthoMatrix;
		D3D_FEATURE_LEVEL mFeatureLevel;

		D3D11_VIEWPORT mViewport;

		float mFOV;
		float mScreenAspect;
	};
}
