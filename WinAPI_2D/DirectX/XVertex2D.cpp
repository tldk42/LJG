#include "XVertex2D.h"
#include "XWorldBuffer.h"
#include "Context.h"
#include "Helper/UDXHelper.h"

namespace LJG
{
	XVertex2D::XVertex2D(const float InZOrder)
		: mZOrder(InZOrder)
	{
		mWorldBuffer = std::make_unique<XWorldBuffer>();
	}

	XVertex2D::~XVertex2D()
	{
		XVertex2D::Release();
	}

	void XVertex2D::Initialize()
	{
		mVertexBufferArray.reserve(4);

		mWorldBuffer->Initialize();
		CHECK_RESULT(CreateShape());
	}

	void XVertex2D::Update(float DeltaTime)
	{
		mWorldBuffer->Update(DeltaTime);
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

		mWorldBuffer->Render();
		Context::GetDeviceContext()->IASetVertexBuffers(0, 1, mVertexBuffer.GetAddressOf(), &stride, &offset);
		Context::GetDeviceContext()->IASetIndexBuffer(mIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);

		Context::GetDeviceContext()->IASetPrimitiveTopology(mPrimType);

		// TODO: 실제 Draw는 Child Vertex에서 진행
		// Context::GetDeviceContext()->DrawIndexed(8, 0, 0);
	}

	void XVertex2D::Release()
	{
		mWorldBuffer->Release();
		mVertexLayout = nullptr;
		mVertexBuffer = nullptr;
		mIndexBuffer  = nullptr;
		mVertexShader = nullptr;
		mPixelShader  = nullptr;
	}

#pragma region Transform
	void XVertex2D::SetScale(const FVector2f& InScale)
	{
		mScale = InScale;

		SetTransform(FVector2f::ZeroVector, 0.f, mScale);
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
		SetTransform(InAddLocation, 0, FVector2f::UnitVector);

		mWorldLocation += InAddLocation;
	}

	void XVertex2D::SetWorldTransform(const FVector2f& InLocation, const float InAngle, const FVector2f& InScale)
	{
		const FVector2f delta = InLocation - mWorldLocation;

		SetTransform(delta, InAngle, InScale);

		mWorldLocation = InLocation;
		mAngle         = InAngle;
		mScale         = InScale;
	}

	void XVertex2D::SetFlipX(const bool bEnable)
	{
		if (bEnable != bFlipX)
		{
			for (FVertexBase& vertex : mVertexBufferArray)
			{
				vertex.Pos.X *= -1;
			}

			bFlipX = bEnable;
		}
	}

	void XVertex2D::SetTransform(const FVector2f& InLocation, const float InAngle, const FVector2f& InScale)
	{
		const XMMATRIX translation = TranslationMatrix(InLocation.X, InLocation.Y);
		const XMMATRIX rotation    = RotationMatrix(InAngle);
		const XMMATRIX scale       = ScaleMatrix(InScale.X, InScale.Y);

		const XMMATRIX transform = scale * rotation * translation;

		mWorldBuffer->SetWorldMatrix(transform);

		for (FVertexBase& vertex : mVertexBufferArray)
		{
			XMVECTOR pos = {vertex.Pos.X, vertex.Pos.Y, vertex.Pos.Z, 1.f};

			// 1 : 1 정규화
			// pos = XMVector2Transform(pos, aspectScale);

			// 변환 행렬 적용
			pos = XMVector2Transform(pos, transform);

			// 4 : 3변환 
			// pos = XMVector2Transform(pos, aspectInverse);

			XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&vertex.Pos), pos);
		}
	}
#pragma endregion

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

		result = UDXHelper::LoadVertexShaderFile(Context::GetDevice(), L"Shader/sample2_vert.vsh",
												 vertexShaderBuf.GetAddressOf(), mVertexShader.GetAddressOf());
		result = UDXHelper::LoadPixelShaderFile(Context::GetDevice(), L"Shader/sample2_frag.psh",
												mPixelShader.GetAddressOf());

		if (!mVertexShader.Get() || !mPixelShader.Get())
		{
			LOG_DX_ERROR("Failed to load, compile ShaderFile or 릴리즈모??경로??정??시???");
			return E_FAIL;
		}

		constexpr D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{
				"POSITION",                  // 셰이더 입력 서명에서 이 요소와 연결된 의미체계 
				0,                           // 의미상 인덱스
				DXGI_FORMAT_R32G32B32_FLOAT,    // 데이터 형식 (float2)
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
		/*
		 * (0) ^ * * * ^ (1)
		 *     *       *
		 *	   *       *
		 * (3) ^ * * * ^ (2)
		 */
		mVertexBufferArray =
		{
			{FVector3f(-.5f, .5f, mZOrder) * mScale, {0, 0}, mDrawColor},
			{FVector3f(.5f, .5f, mZOrder) * mScale, {1, 0}, mDrawColor},
			{FVector3f(.5f, -.5f, mZOrder) * mScale, {1, 1}, mDrawColor},
			{FVector3f(-.5f, -.5f, mZOrder) * mScale, {0, 1}, mDrawColor},
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

	void XVertex2D::OnResizeCallback()
	{}
}
