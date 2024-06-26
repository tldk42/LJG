#include "DXWrite.h"

#include "Context.h"
#include "Helper/EngineHelper.h"
#include "Helper/UDXHelper.h"
#include "Component/UTextBlock.h"
#include "Window.h"

namespace LJG
{
	DXWriteUPtr DXWrite::s_Writer = nullptr;

	DXWrite::DXWrite()
		: mD2DFactory(nullptr),
		  mRenderTarget(nullptr),
		  mBrush(nullptr),
		  mWriteFactory(nullptr),
		  mTextFormat(nullptr),
		  mTextLayout(nullptr),
		  mDPI(0.f),
		  mDPI_Scale(0.f),
		  bEnableFontUnderline(false),
		  mFontSize(72.f),
		  mTextLength(0),
		  mFontWeight(DWRITE_FONT_WEIGHT_NORMAL),
		  mFontStyle(DWRITE_FONT_STYLE_NORMAL)
	{
		DXWrite::Initialize();
	}

	DXWrite::~DXWrite()
	{
		DXWrite::Release();
	}

	void DXWrite::Create()
	{
		s_Writer.reset(new DXWrite());
	}

	void DXWrite::Initialize()
	{
		constexpr wchar_t defaultText[] = L"Times New Roman";
		mFontFamily                     = defaultText;

		CreateDeviceIndependentResources();
		CreateDeviceResources();

		Window::GetWindow()->OnResize.Bind([this](UINT Width, UINT Height){
			OnResizeCallback(Width, Height);
		});

	}

	void DXWrite::Update(float DeltaTime) {}

	void DXWrite::Render()
	{
#pragma region Font Test
	
#pragma endregion
	}

	void DXWrite::Release()
	{
		DiscardDeviceIndependentResources();
		DiscardDeviceResources();
	}

	bool DXWrite::Initialized()
	{
		if (s_Writer)
			return s_Writer->bInitialized;

		return false;
	}

	HRESULT DXWrite::Begin() const
	{
		assert(mRenderTarget);

		mRenderTarget->BeginDraw();
		mRenderTarget->SetTransform(D2D1::IdentityMatrix());

		return S_OK;
	}

	HRESULT DXWrite::End() const
	{
		assert(mRenderTarget.Get());

		return mRenderTarget->EndDraw();
	}

	HRESULT DXWrite::Draw(const FVector2f& InPosition, WTextView InText, D2D1::ColorF InColor) const
	{
		CHECK_RESULT(Begin());

		CHECK_RESULT(DrawText_A(InPosition, InText, InColor));

		return End();
	}

	HRESULT DXWrite::DrawText_A(const FVector2f& InPosition, WTextView InText, D2D1::ColorF InColor) const
	{
		if (mRenderTarget.Get() && mBrush.Get())
		{
			const D2D1_RECT_F layoutRect = D2D1::RectF(
				InPosition.X / mDPI_Scale,
				InPosition.Y / mDPI_Scale,
				mRenderTarget->GetSize().width / mDPI_Scale,
				mRenderTarget->GetSize().height / mDPI_Scale);

			mBrush->SetColor(InColor);
			mRenderTarget->DrawText(WText(InText).c_str(), InText.size(), mTextFormat.Get(), &layoutRect, mBrush.Get());
		}

		return S_OK;
	}

	HRESULT DXWrite::DrawText_Immediately(const std::wstring& InText, D2D1_RECT_F Rect, D2D1::ColorF InColor)
	{
		Begin();

		mBrush->SetColor(InColor);
		mRenderTarget->DrawText(InText.c_str(), InText.size(), mTextFormat.Get(), &Rect, mBrush.Get());

		End();
		return S_OK;
	}
	
	HRESULT DXWrite::CreateDeviceIndependentResources()
	{
		// Set DPI
		mDPI       = static_cast<float_t>(GetDpiForWindow(GetHWND()));
		mDPI_Scale = mDPI / 96.f;


		// Create D2 Factory
		HRESULT result = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, mD2DFactory.GetAddressOf());
		if (FAILED(result)) {}

		// Create  DWrite Factory
		result = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory),
									 reinterpret_cast<IUnknown**>(mWriteFactory.GetAddressOf()));
		if (FAILED(result)) {}

		// Create TextFormat
		result = mWriteFactory->CreateTextFormat(
			mFontFamily.c_str(),
			nullptr,
			mFontWeight,
			mFontStyle,
			DWRITE_FONT_STRETCH_NORMAL,
			20,
			L"en-us",
			mTextFormat.GetAddressOf());
		if (SUCCEEDED(result))
		{
			bInitialized = true;
		}

		return result;
	}

	HRESULT DXWrite::CreateDeviceResources()
	{
		ComPtr<IDXGISurface1> backBuffer;
		CHECK_RESULT(Context::GetSwapChain()->GetBuffer(0, __uuidof(IDXGISurface1),
														reinterpret_cast<void**>(backBuffer.GetAddressOf())));


		D2D1_RENDER_TARGET_PROPERTIES props;

		props.type        = D2D1_RENDER_TARGET_TYPE_DEFAULT;
		props.pixelFormat = D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED);
		props.dpiX        = mDPI;
		props.dpiY        = mDPI;
		props.usage       = D2D1_RENDER_TARGET_USAGE_NONE;
		props.minLevel    = D2D1_FEATURE_LEVEL_DEFAULT;

		CHECK_RESULT(mD2DFactory->CreateDxgiSurfaceRenderTarget(backBuffer.Get(), &props, mRenderTarget.GetAddressOf()));
		CHECK_RESULT(mRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Yellow), mBrush.GetAddressOf()));


		backBuffer = nullptr;

		return S_OK;
	}

	void DXWrite::DiscardDeviceIndependentResources()
	{
		mD2DFactory   = nullptr;
		mWriteFactory = nullptr;
		mTextFormat   = nullptr;
		mTextLayout   = nullptr;
	}

	void DXWrite::DiscardDeviceResources()
	{
		mRenderTarget = nullptr;
		mBrush        = nullptr;
	}

	void DXWrite::AddText(UTextBlockSPtr InWriteData)
	{
	}

#pragma region Set Brush
	/*HRESULT DXWrite::SetText(D2D1_POINT_2F InPos, const wchar_t* InText, D2D1::ColorF InColor)
	{
		HRESULT result = S_OK;

		mTextLength = static_cast<uint32_t>(wcslen(InText));

		mText.clear();
		mText = InText;

		ReleaseCOM(mTextLayout);

		if (SUCCEEDED(result))
		{
			result = mWriteFactory->CreateTextLayout(
				mText.c_str(), // The string to be laid out and formatted.
				mTextLength,   // The length of the string.
				mTextFormat,   // The text format to apply to the string (contains font information, etc).
				InPos.x,       // The width of the layout box.
				InPos.y,       // The height of the layout box.
				&mTextLayout   // The IDWriteTextLayout interface pointer.
			);
		}

		// Declare a typography pointer.
		IDWriteTypography* pTypography = NULL;
		// Create a typography interface object.
		if (SUCCEEDED(result))
		{
			result = mWriteFactory->CreateTypography(&pTypography);
		}

		// Set the stylistic set.
		DWRITE_FONT_FEATURE fontFeature = {DWRITE_FONT_FEATURE_TAG_STYLISTIC_SET_7, 1};
		if (SUCCEEDED(result))
		{
			result = pTypography->AddFontFeature(fontFeature);
		}

		// Set the typography for the entire string.
		DWRITE_TEXT_RANGE textRange = {0, mTextLength};

		if (SUCCEEDED(result))
		{
			result = mTextLayout->SetTypography(pTypography, textRange);
		}

		// Set the underline for the entire string.
		if (SUCCEEDED(result))
		{
			result = mTextLayout->SetUnderline(bEnableFontUnderline, textRange);
		}
		ReleaseCOM(pTypography);
		return result;
	}*/

	HRESULT DXWrite::SetFont(const wchar_t* InFontFamily)
	{
		const DWRITE_TEXT_RANGE textRange = {0, mTextLength};
		const HRESULT           result    = mTextLayout->SetFontFamilyName(InFontFamily, textRange);
		if (SUCCEEDED(result))
		{
			mFontFamily.clear();
			mFontFamily = InFontFamily;
		}

		return result;
	}

	HRESULT DXWrite::SetFontSize(const float InSize)
	{
		const DWRITE_TEXT_RANGE textRange = {0, mTextLength};

		const HRESULT result = mTextLayout->SetFontSize(InSize, textRange);

		if (SUCCEEDED(result))
		{
			mFontSize = InSize;
		}

		return result;
	}

	HRESULT DXWrite::SetBold(const bool bEnable)
	{
		DWRITE_TEXT_RANGE textRange = {0, mTextLength};

		mFontWeight = bEnable ? DWRITE_FONT_WEIGHT_BOLD : DWRITE_FONT_WEIGHT_NORMAL;

		const HRESULT result = mTextLayout->SetFontWeight(mFontWeight, textRange);

		return result;
	}

	HRESULT DXWrite::SetItalic(const bool bEnable)
	{
		DWRITE_TEXT_RANGE textRange = {0, mTextLength};

		mFontStyle = bEnable ? DWRITE_FONT_STYLE_ITALIC : DWRITE_FONT_STYLE_NORMAL;

		const HRESULT result = mTextLayout->SetFontStyle(mFontStyle, textRange);

		return result;
	}

	HRESULT DXWrite::SetUnderline(const bool bEnable)
	{
		DWRITE_TEXT_RANGE textRange = {0, mTextLength};

		bEnableFontUnderline = bEnable;

		const HRESULT result = mTextLayout->SetUnderline(bEnableFontUnderline, textRange);

		return result;
	}
#pragma endregion

	void DXWrite::OnResizeCallback(UINT InWidth, UINT InHeight)
	{
		// RenderTarget, Brush 秦力 
		DiscardDeviceResources();
		// 货肺款 BackBuffer肺 犁积己
		CreateDeviceResources();
	}
}
