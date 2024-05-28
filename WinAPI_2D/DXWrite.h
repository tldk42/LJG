#pragma once

#include "CommonInclude.h"
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>

namespace LJG
{
	class DXWrite : public ICoreAPI
	{
	public:
		DXWrite(int32_t InWidth, int32_t InHeight, IDXGISurface1* InSurface);
		~DXWrite();

	public:
		static void            Create( int32_t InWidth, int32_t InHeight, IDXGISurface1* InSurface);
		inline static DXWrite* Get() { return s_Writer; }

#pragma region Core Interface
		void Initialize() override;
		void Update() override;
		void Render() override;
		void Release() override;
#pragma endregion

		bool Set(int32_t InWidth, int32_t InHeight, IDXGISurface1* InSurface);

		bool    Begin();
		bool    End();
		HRESULT Draw(RECT InRect, TCHAR* InText, D2D1::ColorF = D2D1::ColorF::Green);
		HRESULT DrawText_A(RECT InRect, TCHAR* InText, D2D1::ColorF = D2D1::ColorF::DarkGreen);
		HRESULT DrawText_A(D2D1_POINT_2F InOrigin, D2D1::ColorF = D2D1::ColorF::DarkGreen);


		HRESULT CreateDeviceIndependentResources();
		/**
		 * SurfaceRenderTarget����
		 * @param InSurface �����(���� Ÿ��)
		 */
		HRESULT CreateDeviceResources(IDXGISurface1* InSurface);

		void DiscardDeviceIndependentResources();
		void DiscardDeviceResources();

	public:
#pragma region Set
		HRESULT SetText(D2D1_POINT_2F InPos, const wchar_t* InText, D2D1::ColorF InColor);
		HRESULT SetFont(const wchar_t* InFontFamily);
		HRESULT SetFontSize(const float InSize);
		HRESULT SetBold(const bool bEnable);
		HRESULT SetItalic(const bool bEnable);
		HRESULT SetUnderline(const bool bEnable);
#pragma endregion

	private:
		void OnResizeCallback(UINT InWidth, UINT InHeight, IDXGISurface1* InSurface);

	public:
		ID2D1Factory*         mD2DFactory;
		ID2D1RenderTarget*    mRenderTarget;
		ID2D1SolidColorBrush* mBrush;

		IDWriteFactory*    mWriteFactory;
		IDWriteTextFormat* mTextFormat;
		IDWriteTextLayout* mTextLayout;

		float_t mDPI;
		float_t mDPI_Scale;

		BOOL               bEnableFontUnderline;
		float              mFontSize;
		uint32_t           mTextLength;
		DWRITE_FONT_WEIGHT mFontWeight;
		DWRITE_FONT_STYLE  mFontStyle;

		std::wstring mFontFamily;
		std::wstring mText;

	private:
		static DXWrite* s_Writer;
	};
}