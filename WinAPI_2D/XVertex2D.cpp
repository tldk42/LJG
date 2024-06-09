#include "XVertex2D.h"

#include "Context.h"
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


		// TODO: Child에서
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

	void XVertex2D::SetWorldLocation(const FVector2f& InLocation)
	{
		// 스크린 좌표계 위치 업데이트
		mWorldLocation = InLocation;

		// NDC 좌표계 위치 업데이트
		const FVector2f cachedPos = mNDCLocation;
		Screen2NDC();
		const FVector2f deltaPos = (mNDCLocation - cachedPos);

		for (FVertexBase& vertex : mVertexBufferArray)
		{
			vertex.Pos += deltaPos;
		}
	}

	void XVertex2D::AddWorldLocation(const FVector2f& InAddLocation)
	{
		const FVector2f addiPos = UDXHelper::Screen2NDC(mScreenResolution, InAddLocation);

		// 스크린 좌표계 위치 업데이트
		mWorldLocation += InAddLocation;

		// NDC 좌표계 위치 업데이트
		Screen2NDC();

		for (FVertexBase& vertex : mVertexBufferArray)
		{
			vertex.Pos += addiPos;
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
			bufferDesc.ByteWidth      = std::size(mVertexBufferArray) * sizeof(FVertexBase); // 버퍼크기
			bufferDesc.Usage          = D3D11_USAGE_DEFAULT;                      // 버퍼의 읽기/쓰기 방법 지정
			bufferDesc.BindFlags      = D3D11_BIND_VERTEX_BUFFER;                 // 파이프라인에 바인딩될 방법
			bufferDesc.CPUAccessFlags = 0;                                        // 생성될 버퍼에 CPU가 접근하는 유형 (DX 성능에 매우 중요)
			bufferDesc.MiscFlags      = 0;                                        // 추가적인 옵션 플래그
		}

		D3D11_SUBRESOURCE_DATA InitData;
		{
			InitData.pSysMem = mVertexBufferArray.data(); // 초기화 데이터 포인터 (정점 배열의 주소를 넘겨준다)
			// InitData.SysMemPitch (텍스처 리소스의 한줄의 크기)
			// InitData.SysMemSlicePitch (3차원 텍스처의 깊이 간격)
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
			LOG_DX_ERROR("Failed to load, compile ShaderFile or 릴리즈모드(경로수정하시오)?");
			return E_FAIL;
		}

		constexpr D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{
				"POSITION",                  // 셰이더 입력 서명에서 이 요소와 연결된 의미체계 
				0,                           // 의미상 인덱스
				DXGI_FORMAT_R32G32_FLOAT,    // 데이터 형식 (float2)
				0,                           // 입력 어셈블러 식별정수
				0,                           // 요소 사이 오프셋 
				D3D11_INPUT_PER_VERTEX_DATA, // 단일 입력 슬롯 입력 데이터 클래스
				0                            // 정점 버퍼에서 렌더링 되는 인스턴스의 수 (D3D11_INPUT_PER_VERTEX_DATA -> 0)
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
		// 정점 정보 (사각형을 그리기위해 기본적인 삼각형 2개를 인덱싱하여 형성
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
