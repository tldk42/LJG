#include "DXWrite.h"

#include "Context.h"
#include "EngineHelper.h"

namespace LJG
{
	DXWrite* DXWrite::s_Writer;

	DXWrite::DXWrite(int32_t InWidth, int32_t InHeight, IDXGISurface1* InSurface)
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
		Set(InWidth, InHeight, InSurface);
	}

	DXWrite::~DXWrite() {}

	void DXWrite::Create(int32_t InWidth, int32_t InHeight, IDXGISurface1* InSurface)
	{
		s_Writer = new DXWrite(InWidth, InHeight, InSurface);
	}

	void DXWrite::Initialize()
	{
		const wchar_t defaultText[] = L"Times New Roman";
		mFontFamily                 = defaultText;

		CreateDeviceIndependentResources();
	}

	void DXWrite::Update() {}

	void DXWrite::Render()
	{
#pragma region Font Test
		if (mTextFormat)
		{
			D2D1_SIZE_F rtSize = mRenderTarget->GetSize();
			//Draw a grid background.
			int width  = static_cast<int>(rtSize.width);
			int height = static_cast<int>(rtSize.height);

			for (FWriteData& text : TextArray)
			{
				Draw(text.RectSize, text.Text);
			}

			// // 클라이언트 좌표계를 사용하여 RECT를 구성한다.
			// RECT rc1 = {0, 0, width, height};
			// Draw(rc1, (TCHAR*)L"FPS: ");

			// DrawText_Immediately({900, 600});
		}
#pragma endregion
	}

	void DXWrite::Release()
	{
		mText.clear();
		mFontFamily.clear();
		DiscardDeviceIndependentResources();
		DiscardDeviceResources();
	}

	bool DXWrite::Set(int32_t InWidth, int32_t InHeight, IDXGISurface1* InSurface)
	{
		Initialize();

		CreateDeviceResources(InSurface);


		// static_assert(Window::GetWindow(), L"윈도우 초기화 안됨");

		Window::GetWindow()->AddResizeCallback([this](UINT Width, UINT Height){
			IDXGISurface1* backBuffer = nullptr;
			Context::GetSwapChain()->GetBuffer(0, __uuidof(IDXGISurface1), reinterpret_cast<void**>(&backBuffer));

			OnResizeCallback(Width, Height, backBuffer);
			backBuffer->Release();
		});

		TextArray.clear();
		TextArray.reserve(10);

		return true;
	}

	bool DXWrite::Begin()
	{
		if (mRenderTarget)
		{
			mRenderTarget->BeginDraw();
			mRenderTarget->SetTransform(D2D1::IdentityMatrix());
		}

		return true;
	}

	bool DXWrite::End()
	{
		if (mRenderTarget && FAILED(mRenderTarget->EndDraw()))
		{
			return false;
		}

		return true;
	}

	HRESULT DXWrite::Draw(RECT InRect, const std::wstring& InText, D2D1::ColorF InColor)
	{
		if (Begin())
		{
			if (SUCCEEDED(DrawText_A(InRect, InText, InColor)))
			{
				return End();
			}
		}
		return 0;
	}

	HRESULT DXWrite::DrawText_A(RECT InRect, const std::wstring& InText, D2D1::ColorF InColor)
	{
		if (mRenderTarget && mBrush)
		{
			D2D1_RECT_F layoutRect = D2D1::RectF(
				static_cast<FLOAT>(InRect.left) / mDPI_Scale,
				static_cast<FLOAT>(InRect.top) / mDPI_Scale,
				static_cast<FLOAT>(InRect.right) / mDPI_Scale,
				static_cast<FLOAT>(InRect.bottom) / mDPI_Scale);

			mBrush->SetColor(InColor);
			mRenderTarget->DrawText(InText.c_str(), InText.size(), mTextFormat, &layoutRect, mBrush);
		}

		return S_OK;
	}

	HRESULT DXWrite::DrawText_Immediately(const std::wstring& InText, D2D1_RECT_F Rect, D2D1::ColorF InColor)
	{
		Begin();

		mBrush->SetColor(InColor);
		mRenderTarget->DrawText(InText.c_str(), InText.size(), mTextFormat, &Rect, mBrush);

		End();
		return S_OK;
	}


	HRESULT DXWrite::CreateDeviceIndependentResources()
	{
		// Set DPI
		mDPI       = GetDpiForWindow(EngineHelper::GetWindowHandle());
		mDPI_Scale = mDPI / 96.f;


		// Create D2 Factory
		HRESULT result = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &mD2DFactory);
		if (FAILED(result)) {}

		// Create  DWrite Factory
		result = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory),
		                             reinterpret_cast<IUnknown**>(&mWriteFactory));
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
			&mTextFormat);
		if (FAILED(result)) {}

		return result;
	}

	HRESULT DXWrite::CreateDeviceResources(IDXGISurface1* InSurface)
	{
		HRESULT result = S_OK;

		D2D1_RENDER_TARGET_PROPERTIES props;

		props.type        = D2D1_RENDER_TARGET_TYPE_DEFAULT;
		props.pixelFormat = D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED);
		props.dpiX        = mDPI;
		props.dpiY        = mDPI;
		props.usage       = D2D1_RENDER_TARGET_USAGE_NONE;
		props.minLevel    = D2D1_FEATURE_LEVEL_DEFAULT;

		result = mD2DFactory->CreateDxgiSurfaceRenderTarget(InSurface, &props, &mRenderTarget);
		if (SUCCEEDED(result))
		{
			result = mRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Yellow), &mBrush);
		}

		return result;
	}

	void DXWrite::DiscardDeviceIndependentResources()
	{
		ReleaseCOM(mD2DFactory);
		ReleaseCOM(mWriteFactory);
		ReleaseCOM(mTextFormat);
		ReleaseCOM(mTextLayout);
	}

	void DXWrite::DiscardDeviceResources()
	{
		ReleaseCOM(mRenderTarget);
		ReleaseCOM(mBrush);
	}

	void DXWrite::AddText(const FWriteData& InWriteData)
	{
		Get()->TextArray.emplace_back(InWriteData);
	}

	void DXWrite::UpdateText(const FWriteData& WriteToUpdate, const std::wstring& NewText)
	{
		FWriteData& DataToUpdate = FindText(WriteToUpdate);

		DataToUpdate.Text = NewText;
	}

	FWriteData& DXWrite::FindText(const FWriteData& WriteToFind)
	{
		FWriteData returnValue{};

		for (FWriteData& textData : Get()->TextArray)
		{
			if (textData == WriteToFind)
			{
				return textData;
			}
		}
		return returnValue;
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

	void DXWrite::OnResizeCallback(UINT InWidth, UINT InHeight, IDXGISurface1* InSurface)
	{
		// RenderTarget, Brush 해제 
		DiscardDeviceResources();
		// 새로운 BackBuffer로 재생성
		CreateDeviceResources(InSurface);
	}
}
