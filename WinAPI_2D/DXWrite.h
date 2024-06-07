#pragma once

#include "CommonInclude.h"
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>

namespace LJG
{
	CLASS_PTR(DXWrite);
	CLASS_PTR(FWriteData);

	class DXWrite : public ICoreAPI
	{
	public:
		DXWrite(int32_t InWidth, int32_t InHeight, IDXGISurface1* InSurface);
		~DXWrite() override;

	public:
		static void            Create(int32_t InWidth, int32_t InHeight, IDXGISurface1* InSurface);
		inline static DXWrite* Get() { return s_Writer.get(); }

#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

		static bool Initialized();

		bool Set(int32_t InWidth, int32_t InHeight, IDXGISurface1* InSurface);

		bool    Begin();
		bool    End();
		HRESULT Draw(RECT InRect, const std::wstring& InText, D2D1::ColorF = D2D1::ColorF::Green);
		HRESULT DrawText_A(RECT InRect, const std::wstring& InText, D2D1::ColorF = D2D1::ColorF::DarkGreen);
		HRESULT DrawText_Immediately(const std::wstring& InText, D2D1_RECT_F Rect,
									 D2D1::ColorF         = D2D1::ColorF::DarkGreen);


		HRESULT CreateDeviceIndependentResources();
		HRESULT CreateDeviceResources(IDXGISurface1* InSurface);

		void DiscardDeviceIndependentResources();
		void DiscardDeviceResources();

	public:
		static void AddText(UTextBlockSPtr InWriteData);
#pragma region Set
		// HRESULT SetText(D2D1_POINT_2F InPos, const wchar_t* InText, D2D1::ColorF InColor);
		HRESULT SetFont(const wchar_t* InFontFamily);
		HRESULT SetFontSize(const float InSize);
		HRESULT SetBold(const bool bEnable);
		HRESULT SetItalic(const bool bEnable);
		HRESULT SetUnderline(const bool bEnable);
#pragma endregion

	private:
		// Resize Callback
		void OnResizeCallback(UINT InWidth, UINT InHeight, IDXGISurface1* InSurface);

	private:
		ComPtr<ID2D1Factory>         mD2DFactory;
		ComPtr<ID2D1RenderTarget>    mRenderTarget;
		ComPtr<ID2D1SolidColorBrush> mBrush;

		ComPtr<IDWriteFactory>    mWriteFactory;
		ComPtr<IDWriteTextFormat> mTextFormat;
		ComPtr<IDWriteTextLayout> mTextLayout;

		float_t mDPI;
		float_t mDPI_Scale;

		BOOL               bEnableFontUnderline;
		float              mFontSize;
		uint32_t           mTextLength;
		DWRITE_FONT_WEIGHT mFontWeight;
		DWRITE_FONT_STYLE  mFontStyle;

		std::wstring mFontFamily;
		std::wstring mText;

		bool bInitialized;

		std::vector<UTextBlockSPtr> mTextArray;

	private:
		static DXWriteUPtr s_Writer;
	};
}
