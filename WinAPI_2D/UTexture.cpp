#include "UTexture.h"

#include <d3dcompiler.h>
#include "Context.h"
#include "UDXHelper.h"
#include "directxtk/WICTextureLoader.h"


namespace LJG
{
	UTexture::UTexture(const std::wstring& TextureFile)
	{
		CHECK_RESULT(LoadTextureFromFile(TextureFile));
		UTexture::Initialize();
	}

	UTexture::~UTexture()
	{
		UTexture::Release();
	}

	void UTexture::Initialize()
	{
		CHECK_RESULT(CreateTriangle());
		CHECK_RESULT(CreateConstantBuffer());
	}

	void UTexture::Update(float DeltaTime)
	{
		SetShaderParams();
	}

	void UTexture::Render()
	{
		// Input Layout
		Context::GetDeviceContext()->IASetInputLayout(mVertexLayout.Get());

		// Shader
		Context::GetDeviceContext()->VSSetShader(mVertexShader.Get(), nullptr, 0);
		Context::GetDeviceContext()->PSSetShader(mPixelShader.Get(), nullptr, 0);
		// TODO: Set other shader...

		//아니
		// 렌더링 리소스가 변경될 때 다시 호출 (각기 다른 텍스처로 설정 -> 렌더링)
		Context::GetDeviceContext()->PSSetShaderResources(0, 1, mSRV.GetAddressOf());
		Context::GetDeviceContext()->PSSetSamplers(0, 1, mSamplerState.GetAddressOf());

		// hardcoded
		constexpr UINT stride = sizeof(FTexVertex);
		constexpr UINT offset = 0;

		Context::GetDeviceContext()->IASetVertexBuffers(0, 1, mVertexBuffer.GetAddressOf(), &stride, &offset);
		Context::GetDeviceContext()->IASetIndexBuffer(mIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
		// Context::GetDeviceContext()->VSSetConstantBuffers(0, 1, &mConstantBuffer);
		Context::GetDeviceContext()->IASetPrimitiveTopology(mPrimType);

		Context::GetDeviceContext()->DrawIndexed(6, 0, 0);
	}

	void UTexture::Release()
	{
		mVertexLayout    = nullptr;
		mVertexBuffer    = nullptr;
		mIndexBuffer     = nullptr;
		mConstantBuffer  = nullptr;
		mVertexShader    = nullptr;
		mPixelShader     = nullptr;
		mTextureResource = nullptr;
		mSRV             = nullptr;
		mTexture         = nullptr;
		mSamplerState    = nullptr;
	}

	HRESULT UTexture::LoadTextureFromFile(const std::wstring& TextureFile)
	{
		if (!TextureFile.empty())
		{
			CHECK_RESULT(DirectX::CreateWICTextureFromFile(Context::GetDevice(), TextureFile.c_str(),
														   mTextureResource.GetAddressOf(),
														   mSRV.GetAddressOf()));
			CHECK_RESULT(mTextureResource->QueryInterface(__uuidof(ID3D11Texture2D),
														  reinterpret_cast<void**>(mTexture.GetAddressOf())));

			// 텍스처 정보 가져오기
			mSRV->GetDesc(&mSRVDesc);
			mTexture->GetDesc(&mTextureDesc);

			LOG_DX_INFO("-------- Texure Loaded ----------");
			std::string texName;
			texName.assign(TextureFile.begin(), TextureFile.end());
			LOG_DX_INFO("File: {}", texName);
			LOG_DX_INFO("Width: {}", mTextureDesc.Width);
			LOG_DX_INFO("Height: {}", mTextureDesc.Height);

			AdjustTextureSize();
		}

		return S_OK;
	}

	void UTexture::AdjustTextureSize()
	{
		const FWindowData winData = Context::GetWindowData();

		mVertexOffset.X = static_cast<float_t>(mTextureDesc.Width) / static_cast<float_t>(winData.Width);
		mVertexOffset.Y = static_cast<float_t>(mTextureDesc.Height) / static_cast<float_t>(winData.Height);

		if (const float overflowArea = mVertexOffset.GetMax(); overflowArea > 1)
		{
			mVertexOffset /= overflowArea;
		}
	}

	HRESULT UTexture::CreateTriangle()
	{
		CHECK_RESULT(CreateVertexBuffer());
		CHECK_RESULT(CreateIndexBuffer());
		CHECK_RESULT(LoadShaderAndInputLayout());
		CHECK_RESULT(CreateSamplerState());

		Context::GetDeviceContext()->IASetPrimitiveTopology(mPrimType);

		return S_OK;
	}

	HRESULT UTexture::CreateVertexBuffer()
	{
		// 정점 정보 (사각형을 그리기위해 기본적인 삼각형 2개를 인덱싱하여 형성
		mVertexBufferArray = {
			{{mScale.X * (-mVertexOffset.X), mScale.Y * (mVertexOffset.Y)}, {0, 0}},
			{{mScale.X * (mVertexOffset.X), mScale.Y * (mVertexOffset.Y)}, {1, 0}},
			{{mScale.X * (mVertexOffset.X), mScale.Y * (-mVertexOffset.Y)}, {1, 1}},
			{{mScale.X * (-mVertexOffset.X), mScale.Y * (-mVertexOffset.Y)}, {0, 1}}
		};

		D3D11_BUFFER_DESC bufferDesc;
		{
			bufferDesc.ByteWidth      = std::size(mVertexBufferArray) * sizeof(FTexVertex); // 버퍼크기
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

	HRESULT UTexture::CreateIndexBuffer()
	{
		const WORD indices[] =
		{
			0, 1, 2,
			0, 2, 3
		};

		constexpr UINT numIndex = std::size(indices);

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
		ibInitData.pSysMem = indices;

		return Context::GetDevice()->CreateBuffer(&initData, &ibInitData, mIndexBuffer.GetAddressOf());
	}

	HRESULT UTexture::LoadShaderAndInputLayout()
	{
		HRESULT result = S_OK;

		DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
		shaderFlags |= D3DCOMPILE_DEBUG;
#endif
		/**
		 * ID3DBlob
		 *  임의 길이의 데이터를 반환하는 곳에 사용됨
		 *	메시 최적화 및 로드 작업 때 정점 인접, 자료 등의 정보를 저장하는 데이터 버퍼로 사용
		 *	셰이더 컴파일 API인자로써 개체코드, 오류메시지 반환
		 *	GetBufferPointer	: 데이터 포인터
		 *	GetBufferSize		: 데이터 크기
		 */
		ComPtr<ID3DBlob> vertexShaderBuf = nullptr;

		result = UDXHelper::LoadVertexShaderFile(Context::GetDevice(), L"sample_vert.vsh",
												 vertexShaderBuf.GetAddressOf(), mVertexShader.GetAddressOf());
		result = UDXHelper::LoadPixelShaderFile(Context::GetDevice(), L"sample_frag.psh", mPixelShader.GetAddressOf());

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
			}
		};

		result = Context::GetDevice()->CreateInputLayout(
			layout,
			2,
			vertexShaderBuf->GetBufferPointer(),
			vertexShaderBuf->GetBufferSize(),
			mVertexLayout.GetAddressOf());

		vertexShaderBuf = nullptr;

		return result;
	}

	HRESULT UTexture::CreateSamplerState()
	{
		/**
		 * 텍스처 매핑
		 *	1. 텍스처 필터링
		 *		Point(가까운 텍셀값) Linear(보간) Anisotropic(경사도)
		 *	2. 좌표 Warping (U, V, W값은 채워야한다)
		 *		Wrap (반복) Clamp(0-1) Mirror(반복, 뒤집기) Border(범위 벗어날 시에 경계 색)
		 */
		D3D11_SAMPLER_DESC samplerDesc{};
		{
			samplerDesc.Filter         = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
			samplerDesc.AddressU       = D3D11_TEXTURE_ADDRESS_WRAP;
			samplerDesc.AddressV       = D3D11_TEXTURE_ADDRESS_WRAP;
			samplerDesc.AddressW       = D3D11_TEXTURE_ADDRESS_WRAP;
			samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
			samplerDesc.MinLOD         = 0;
			samplerDesc.MaxLOD         = D3D11_FLOAT32_MAX;
		}

		return Context::GetDevice()->CreateSamplerState(&samplerDesc, mSamplerState.GetAddressOf());
	}

	HRESULT UTexture::CreateConstantBuffer()
	{
		D3D11_BUFFER_DESC bufferDesc;
		{
			bufferDesc.ByteWidth      = 32;
			bufferDesc.Usage          = D3D11_USAGE_DYNAMIC;
			bufferDesc.BindFlags      = D3D11_BIND_CONSTANT_BUFFER;
			bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			bufferDesc.MiscFlags      = 0;
		}

		return Context::GetDevice()->CreateBuffer(&bufferDesc, nullptr, mConstantBuffer.GetAddressOf());
	}

	void UTexture::SetWorldLocation(const FVector2f& InPos)
	{
		mWorldLocation      = InPos;
		mNormalizedLocation = GetWorldPositionToNormalized(InPos);

		assert(!mVertexBufferArray.empty());

		mVertexBufferArray[0].Pos = (FVector2f(-mVertexOffset.X, mVertexOffset.Y) + mNormalizedLocation) *
		mScale; // Left Top
		mVertexBufferArray[1].Pos = (FVector2f(mVertexOffset.X, mVertexOffset.Y) + mNormalizedLocation) *
		mScale; // Right Top
		mVertexBufferArray[2].Pos = (FVector2f(mVertexOffset.X, -mVertexOffset.Y) + mNormalizedLocation) *
		mScale; // Right Bottom
		mVertexBufferArray[3].Pos = (FVector2f(-mVertexOffset.X, -mVertexOffset.Y) + mNormalizedLocation) *
		mScale; // Left Top
	}

	void UTexture::AddWorldLocation(const FVector2f& InPos)
	{
		const FVector2f normPos = GetWorldPositionToNormalized(InPos);

		for (FTexVertex& vertex : mVertexBufferArray)
		{
			vertex.Pos += normPos;
		}

		mWorldLocation += InPos;
		mNormalizedLocation += normPos;
	}

	void UTexture::OnResizeCallback()
	{
		AdjustTextureSize();
		SetWorldLocation(mWorldLocation);
	}

	void UTexture::SetShaderParams() const
	{
		Context::GetDeviceContext()->UpdateSubresource(
			mVertexBuffer.Get(),
			0,
			nullptr,
			mVertexBufferArray.data(),
			0,
			0);
	}

	FVector2f UTexture::GetWorldPositionToNormalized(const FVector2f& InPos)
	{
		FVector2f         worldPos;
		const FWindowData winData = Context::GetWindowData();

		worldPos.X = InPos.X / static_cast<float_t>(winData.Width);
		worldPos.Y = InPos.Y / static_cast<float_t>(winData.Height);
		return worldPos;
	}
}
