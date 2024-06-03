#include "Vertex.h"

#include <d3dcompiler.h>

#include "Context.h"
#include "EngineHelper.h"
#include "UDXHelper.h"


namespace LJG
{
	Vertex::Vertex()
		: mVertexLayout(nullptr),
		  mVertexBuffer(nullptr),
		  mIndexBuffer(nullptr),
		  mConstantBuffer(nullptr),
		  mVertexShader(nullptr),
		  mPixelShader(nullptr),
		  mPrimType(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
	{
	}

	Vertex::~Vertex()
	{
	}

	void Vertex::Initialize()
	{
		if (FAILED(CreateTriangle()))
		{
			EngineHelper::ShowErrorMessageBox(Window::GetWindow()->GetHandle(), true);
		}
		if (FAILED(CreateConstantBuffer()))
		{
			EngineHelper::ShowErrorMessageBox(Window::GetWindow()->GetHandle(), true);
		}
	}

	void Vertex::Update()
	{
	}

	void Vertex::Render()
	{
		Context::GetDeviceContext()->VSSetShader(mVertexShader, nullptr, 0);
		Context::GetDeviceContext()->PSSetShader(mPixelShader, nullptr, 0);
		// TODO: Set other shader...

		Context::GetDeviceContext()->IASetInputLayout(mVertexLayout);

		// hardcoded
		constexpr UINT stride = 8;
		constexpr UINT offset = 0;

		Context::GetDeviceContext()->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
		Context::GetDeviceContext()->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
		Context::GetDeviceContext()->VSSetConstantBuffers(0, 1, &mConstantBuffer);
		Context::GetDeviceContext()->IASetPrimitiveTopology(mPrimType);
		Context::GetDeviceContext()->DrawIndexed(6, 0, 0);
	}

	void Vertex::Release()
	{
		ReleaseCOM(mVertexLayout);
		ReleaseCOM(mVertexBuffer);
		ReleaseCOM(mIndexBuffer);
		ReleaseCOM(mConstantBuffer);
		ReleaseCOM(mVertexShader);
		ReleaseCOM(mPixelShader);
	}

	HRESULT Vertex::CreateTriangle()
	{
		HRESULT result = S_OK;

		result = CreateVertexBuffer();
		result = CreateIndexBuffer();
		result = LoadShaderAndInputLayout();

		Context::GetDeviceContext()->IASetPrimitiveTopology(mPrimType);

		return result;
	}

	HRESULT Vertex::CreateVertexBuffer()
	{
		// 정점 정보
		const FVector2f vertices[] =
		{
			{-0.5f, 0.5f},
			{0.5f, 0.5f},
			{0.5f, -0.5f},
			{-0.5f, -0.5f}
		};

		D3D11_BUFFER_DESC bufferDesc;
		{
			bufferDesc.ByteWidth      = std::size(vertices) * sizeof(FVector2f); // 버퍼크기
			bufferDesc.Usage          = D3D11_USAGE_DEFAULT;                     // 버퍼의 읽기/쓰기 방법 지정
			bufferDesc.BindFlags      = D3D11_BIND_VERTEX_BUFFER;                // 파이프라인에 바인딩될 방법
			bufferDesc.CPUAccessFlags = 0;                                       // 생성될 버퍼에 CPU가 접근하는 유형 (DX 성능에 매우 중요)
			bufferDesc.MiscFlags      = 0;                                       // 추가적인 옵션 플래그
		}

		D3D11_SUBRESOURCE_DATA InitData;
		{
			InitData.pSysMem = vertices; // 초기화 데이터 포인터 (정점 배열의 주소를 넘겨준다)
			// InitData.SysMemPitch (텍스처 리소스의 한줄의 크기)
			// InitData.SysMemSlicePitch (3차원 텍스처의 깊이 간격)
		}

		return Context::GetDevice()->CreateBuffer(&bufferDesc, &InitData, &mVertexBuffer);
	}

	HRESULT Vertex::CreateIndexBuffer()
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

		return Context::GetDevice()->CreateBuffer(&initData, &ibInitData, &mIndexBuffer);
	}

	HRESULT Vertex::LoadShaderAndInputLayout()
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
		ID3DBlob* vertexShaderBuf;
		ID3DBlob* pixelShaderBuf = nullptr;

		mVertexShader = UDXHelper::LoadVertexShaderFile(Context::GetDevice(), L"sample_vert.vsh", &vertexShaderBuf);
		mPixelShader  = UDXHelper::LoadPixelShaderFile(Context::GetDevice(), L"sample_frag.psh");

		if (!mVertexShader || !mPixelShader)
		{
			LOG_DX_ERROR("Failed to load, compile ShaderFile");
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
		};

		result = Context::GetDevice()->CreateInputLayout(
			layout,
			1,
			vertexShaderBuf->GetBufferPointer(),
			vertexShaderBuf->GetBufferSize(),
			&mVertexLayout);

		ReleaseCOM(vertexShaderBuf);
		ReleaseCOM(pixelShaderBuf);

		return result;
	}

	HRESULT Vertex::CreateConstantBuffer()
	{
		D3D11_BUFFER_DESC bufferDesc;
		{
			bufferDesc.ByteWidth      = 32;
			bufferDesc.Usage          = D3D11_USAGE_DYNAMIC;
			bufferDesc.BindFlags      = D3D11_BIND_CONSTANT_BUFFER;
			bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			bufferDesc.MiscFlags      = 0;
		}

		return Context::GetDevice()->CreateBuffer(&bufferDesc, nullptr, &mConstantBuffer);
	}
}
