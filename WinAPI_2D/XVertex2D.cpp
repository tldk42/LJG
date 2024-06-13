#include "XVertex2D.h"

#include "Context.h"
#include "UDXHelper.h"

namespace LJG
{
	XVertex2D::XVertex2D()
		: mNDCLocation(FVector2f::ZeroVector),
		  mNDCOffset(FVector2f::ZeroVector)
	{
		SetWindowResolution();
	}

	XVertex2D::~XVertex2D()
	{
		XVertex2D::Release();
	}

	void XVertex2D::Initialize()
	{
		mVertexBufferArray.reserve(4);

		CHECK_RESULT(CreateShape());
	}

	void XVertex2D::Update(float DeltaTime)
	{
		SetShaderParams();
	}

	void XVertex2D::Render()
	{
		// Input Layout
		Context::GetDeviceContext()->IASetInputLayout(mVertexLayout.Get());

		// Shader
		Context::GetDeviceContext()->VSSetShader(mVertexShader.Get(), nullptr, 0);
		Context::GetDeviceContext()->PSSetShader(mPixelShader.Get(), nullptr, 0);
		// TODO: Set other shader...

		// hardcoded
		constexpr UINT stride = sizeof(FVertexBase);
		constexpr UINT offset = 0;

		Context::GetDeviceContext()->IASetVertexBuffers(0, 1, mVertexBuffer.GetAddressOf(), &stride, &offset);
		Context::GetDeviceContext()->IASetIndexBuffer(mIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
		Context::GetDeviceContext()->IASetPrimitiveTopology(mPrimType);


		// TODO: Child??서
		// Context::GetDeviceContext()->DrawIndexed(8, 0, 0);
	}

	void XVertex2D::Release()
	{
		mVertexLayout = nullptr;
		mVertexBuffer = nullptr;
		mIndexBuffer  = nullptr;
		mVertexShader = nullptr;
		mPixelShader  = nullptr;
	}

	void XVertex2D::SetWindowResolution()
	{
		mScreenResolution =
		{
			static_cast<float_t>(Context::GetWindowData().Width),
			static_cast<float_t>(Context::GetWindowData().Height)
		};
	}

	void XVertex2D::SetScale(const FVector2f& InScale)
	{
		const FVector2f cachedScale = mScale;

		mScale.X = (InScale.X) / mScreenResolution.X;
		mScale.Y = (InScale.Y) / mScreenResolution.Y;

		for (FVertexBase& vertex : mVertexBufferArray)
		{
			vertex.Pos *= (mScale / cachedScale);
		}
	}

	void XVertex2D::SetWorldRotation(const float InAngle)
	{
		mAngle = InAngle;

		SetTransform(FVector2f::ZeroVector, InAngle, FVector2f::UnitVector);
	}

	void XVertex2D::SetColor(const FLinearColor& InColor)
	{
		mDrawColor = InColor;

		for (auto& vertex : mVertexBufferArray)
		{
			vertex.Color = mDrawColor;
		}
	}

	void XVertex2D::SetWorldLocation(const FVector2f& InLocation)
	{
		AddWorldLocation(InLocation - mWorldLocation);
	}

	void XVertex2D::AddWorldLocation(const FVector2f& InAddLocation)
	{
		const FVector2f addiPos = UDXHelper::Screen2NDC(mScreenResolution, InAddLocation);

		SetTransform(addiPos, 0, FVector2f::UnitVector);

		mWorldLocation += InAddLocation;

		Screen2NDC();
	}

	void XVertex2D::SetWorldTransform(const FVector2f& InLocation, const float InAngle, const FVector2f& InScale)
	{
		const FVector2f addiPos = UDXHelper::Screen2NDC(mScreenResolution, InLocation - mWorldLocation);

		SetTransform(addiPos, InAngle, InScale);

		mWorldLocation = InLocation;
		mAngle         = InAngle;
		mScale         = InScale;
	}

	void XVertex2D::SetTransform(const FVector2f& InLocation, const float InAngle, const FVector2f& InScale)
	{
		const float aspectRatio = mScreenResolution.X / mScreenResolution.Y;

		const XMMATRIX aspectScale   = ScaleMatrix(aspectRatio, 1.0f);
		const XMMATRIX aspectInverse = ScaleMatrix(1.f / aspectRatio, 1.f);

		const XMMATRIX translation = TranslationMatrix(InLocation.X, InLocation.Y);
		const XMMATRIX rotation    = RotationMatrix(InAngle);
		const XMMATRIX scale       = ScaleMatrix(InScale.X, InScale.Y);

		const XMMATRIX transform = scale * rotation * translation;

		for (FVertexBase& vertex : mVertexBufferArray)
		{
			XMVECTOR pos = {vertex.Pos.X, vertex.Pos.Y, 1.f, 1.f};

			// 1 : 1 정규화
			pos = XMVector2Transform(pos, aspectScale);

			// 변환 행렬 적용
			pos = XMVector2Transform(pos, transform);

			// 4 : 3변환 
			pos = XMVector2Transform(pos, aspectInverse);

			XMStoreFloat2(reinterpret_cast<XMFLOAT2*>(&vertex.Pos), pos);
		}
	}

	HRESULT XVertex2D::CreateShape()
	{
		CHECK_RESULT(CreateVertexBuffer());
		CHECK_RESULT(CreateIndexBuffer());
		CHECK_RESULT(LoadShaderAndInputLayout());

		return S_OK;
	}

	HRESULT XVertex2D::CreateVertexBuffer()
	{
		CreateVertexArray();

		D3D11_BUFFER_DESC bufferDesc;
		{
			bufferDesc.ByteWidth      = std::size(mVertexBufferArray) * sizeof(FVertexBase); // 버퍼??기
			bufferDesc.Usage          = D3D11_USAGE_DEFAULT;                                 // 버퍼????기/??기 방법 지??
			bufferDesc.BindFlags      = D3D11_BIND_VERTEX_BUFFER;                            // ??이??라??에 바인??될 방법
			bufferDesc.CPUAccessFlags =
			0;                    // ??성??버퍼??CPU가 ??근??는 ??형 (DX ??능??매우 중요)
			bufferDesc.MiscFlags = 0; // 추????인 ??션 ??래??
		}

		D3D11_SUBRESOURCE_DATA InitData;
		{
			InitData.pSysMem = mVertexBufferArray.data(); // 초기????이????인??(??점 배열??주소????겨준??
			// InitData.SysMemPitch (??스??리소??의 ??줄????기)
			// InitData.SysMemSlicePitch (3차원 ??스처의 깊이 간격)
		}

		return Context::GetDevice()->CreateBuffer(&bufferDesc, &InitData, mVertexBuffer.GetAddressOf());
	}

	HRESULT XVertex2D::CreateIndexBuffer()
	{
		CreateIndexArray();

		const UINT numIndex = mIndices.size();

		D3D11_BUFFER_DESC initData;
		{
			initData.ByteWidth      = numIndex * sizeof(WORD);
			initData.Usage          = D3D11_USAGE_DEFAULT;
			initData.BindFlags      = D3D11_BIND_INDEX_BUFFER;
			initData.CPUAccessFlags = 0;
			initData.MiscFlags      = 0;
		}

		D3D11_SUBRESOURCE_DATA ibInitData;
		ZeroMemory(&ibInitData, sizeof(D3D11_SUBRESOURCE_DATA));
		ibInitData.pSysMem = mIndices.data();

		return Context::GetDevice()->CreateBuffer(&initData, &ibInitData, mIndexBuffer.GetAddressOf());
	}

	HRESULT XVertex2D::LoadShaderAndInputLayout()
	{
		HRESULT result = S_OK;

		ComPtr<ID3DBlob> vertexShaderBuf = nullptr;

		result = UDXHelper::LoadVertexShaderFile(Context::GetDevice(), L"sample2_vert.vsh",
												 vertexShaderBuf.GetAddressOf(), mVertexShader.GetAddressOf());
		result = UDXHelper::LoadPixelShaderFile(Context::GetDevice(), L"sample2_frag.psh", mPixelShader.GetAddressOf());

		if (!mVertexShader.Get() || !mPixelShader.Get())
		{
			LOG_DX_ERROR("Failed to load, compile ShaderFile or 릴리즈모??경로??정??시???");
			return E_FAIL;
		}

		constexpr D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{
				"POSITION",                  // ??이????력 ??명??서 ????소?? ??결??????체계 
				0,                           // ????????덱??
				DXGI_FORMAT_R32G32_FLOAT,    // ??이????식 (float2)
				0,                           // ??력 ??셈블러 ??별??수
				0,                           // ??소 ??이 ??프??
				D3D11_INPUT_PER_VERTEX_DATA, // ??일 ??력 ??롯 ??력 ??이????래??
				0                            // ??점 버퍼??서 ??더????는 ??스??스????(D3D11_INPUT_PER_VERTEX_DATA -> 0)
			},
			{
				"TEX",
				0,
				DXGI_FORMAT_R32G32_FLOAT,
				0,
				D3D11_APPEND_ALIGNED_ELEMENT,
				D3D11_INPUT_PER_VERTEX_DATA,
				0
			},
			{
				"COLOR",
				0,
				DXGI_FORMAT_R32G32B32A32_FLOAT,
				0,
				D3D11_APPEND_ALIGNED_ELEMENT,
				D3D11_INPUT_PER_VERTEX_DATA,
				0
			}
		};

		result = Context::GetDevice()->CreateInputLayout(
			layout,
			3,
			vertexShaderBuf->GetBufferPointer(),
			vertexShaderBuf->GetBufferSize(),
			mVertexLayout.GetAddressOf());

		vertexShaderBuf = nullptr;

		return result;
	}

	void XVertex2D::CreateVertexArray()
	{
		/*
		 * (0) ^ * * * ^ (1)
		 *     *       *
		 *	   *       *
		 * (3) ^ * * * ^ (2)
		 */
		mVertexBufferArray =
		{
			{FVector2f(-1.f, 1.f) * mScale, {0, 0}, mDrawColor},
			{FVector2f(1.f, 1.f) * mScale, {1, 0}, mDrawColor},
			{FVector2f(1.f, -1.f) * mScale, {1, 1}, mDrawColor},
			{FVector2f(-1.f, -1.f) * mScale, {0, 1}, mDrawColor},
		};
	}

	void XVertex2D::CreateIndexArray()
	{
		mIndices =
		{
			0, 1,
			1, 2,
			2, 3,
			3, 0
		};
	}

	void XVertex2D::SetShaderParams() const
	{
		Context::GetDeviceContext()->UpdateSubresource(
			mVertexBuffer.Get(),
			0,
			nullptr,
			mVertexBufferArray.data(),
			0,
			0);
	}

	void XVertex2D::NDC2Screen()
	{
		mWorldLocation.X = mScreenResolution.X * (mNDCLocation.X + 1.f) * .5f;
		mWorldLocation.Y = mScreenResolution.Y * .5f * (1.f - mNDCLocation.Y);
	}

	void XVertex2D::Screen2NDC()
	{
		mNDCLocation.X = mWorldLocation.X / (mScreenResolution.X * .5f);
		mNDCLocation.Y = mWorldLocation.Y / (mScreenResolution.Y * .5f);
	}

	void XVertex2D::OnResizeCallback()
	{
		const auto cachedWorldScale = mScale;

		SetWindowResolution();
		SetScale(cachedWorldScale * mScreenResolution);
	}
}
