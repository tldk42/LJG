#include "XShape2D_Line.h"

#include "Component/Manager/ShaderManager.h"
#include "DirectX/Context.h"
#include "DirectX/XShaderData.h"
#include "DirectX/XWorldBuffer.h"

namespace LJG
{

	XShape2D_Line::XShape2D_Line()
	{
		mDrawColor   = FLinearColor::Red;
		mWorldBuffer = std::make_unique<XWorldBuffer>();
	}

	XShape2D_Line::~XShape2D_Line()
	{
		Release();
	}

	void XShape2D_Line::Initialize()
	{
		mVertexBufferArray.reserve(2); // 직선은 정점 2개
		mWorldBuffer->Initialize();
		CHECK_RESULT(CreateShape());
	}

	void XShape2D_Line::Update(float DeltaTime)
	{
		mWorldBuffer->SetWorldMatrix(mTransform);
		mWorldBuffer->Update(DeltaTime);
	}

	void XShape2D_Line::Render()
	{
		// Input Layout
		Context::GetDeviceContext()->IASetInputLayout(mVertexLayout.Get());

		// Shader
		mShaderData->Render();

		// TODO: Set other shader...

		// hardcoded
		constexpr UINT stride = sizeof(FVertexBase);
		constexpr UINT offset = 0;

		mWorldBuffer->Render();
		Context::GetDeviceContext()->IASetVertexBuffers(0, 1, mVertexBuffer.GetAddressOf(), &stride, &offset);
		Context::GetDeviceContext()->IASetIndexBuffer(mIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);

		Context::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);


		Context::GetDeviceContext()->DrawIndexed(mIndices.size(), 0, 0);
	}

	void XShape2D_Line::Release()
	{
		mWorldBuffer->Release();
		mVertexLayout = nullptr;
		mVertexBuffer = nullptr;
		mIndexBuffer  = nullptr;
		mShaderData   = nullptr;
	}

	HRESULT XShape2D_Line::CreateShape()
	{
		CHECK_RESULT(CreateVertexBuffer());
		CHECK_RESULT(CreateIndexBuffer());
		CHECK_RESULT(LoadShaderAndInputLayout());

		return S_OK;
	}

	HRESULT XShape2D_Line::CreateVertexBuffer()
	{
		CreateVertexArray();

		D3D11_BUFFER_DESC bufferDesc;
		{
			bufferDesc.ByteWidth      = std::size(mVertexBufferArray) * sizeof(FVertexBase); // 버퍼크기
			bufferDesc.Usage          = D3D11_USAGE_DEFAULT; // 버퍼의 읽기/쓰기 방법 지정
			bufferDesc.BindFlags      = D3D11_BIND_VERTEX_BUFFER; // 파이프라인에 바인딩될 방법
			bufferDesc.CPUAccessFlags = 0; // 생성될 버퍼에 CPU가 접근하는 유형 (DX 성능에 매우 중요)
			bufferDesc.MiscFlags      = 0; // 추가적인 옵션 플래그
		}

		D3D11_SUBRESOURCE_DATA InitData;
		{
			InitData.pSysMem = mVertexBufferArray.data(); // 초기화 데이터 포인터 (정점 배열의 주소를 넘겨준다)
			// InitData.SysMemPitch (텍스처 리소스의 한줄의 크기)
			// InitData.SysMemSlicePitch (3차원 텍스처의 깊이 간격)
		}

		return Context::GetDevice()->CreateBuffer(&bufferDesc, &InitData, mVertexBuffer.GetAddressOf());
	}

	HRESULT XShape2D_Line::CreateIndexBuffer()
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

	HRESULT XShape2D_Line::LoadShaderAndInputLayout()
	{
		HRESULT result = S_OK;

		mShaderData = Manager_Shader.CreateOrLoad(L"SimpleShader", L"Shader/sample2_vert.vsh", L"Shader/sample2_frag.psh");

		constexpr D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{
				"POSITION",                  // 셰이더 입력 서명에서 이 요소와 연결된 의미체계 
				0,                           // 의미상 인덱스
				DXGI_FORMAT_R32G32B32_FLOAT, // 데이터 형식 (float2)
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
			mShaderData->GetVertexShaderBuffer()->GetBufferPointer(),
			mShaderData->GetVertexShaderBuffer()->GetBufferSize(),
			mVertexLayout.GetAddressOf());


		return result;
	}

	void XShape2D_Line::CreateVertexArray()
	{
		/*
		 * (0) | 
		 *     | 
		 *	   |
		 * (1) | 
		 */
		mVertexBufferArray =
		{
			{FVector3f(0.f, 0.f, 0.01f), mDrawColor, {0, 0}},
			{FVector3f(0.f, -1.f, 0.01f), mDrawColor, {1, 0}}
		};
	}

	void XShape2D_Line::CreateIndexArray()
	{
		mIndices =
		{
			0, 1
		};
	}

	void XShape2D_Line::SetShaderParams() const
	{
		Context::GetDeviceContext()->UpdateSubresource(
			mVertexBuffer.Get(),
			0,
			nullptr,
			mVertexBufferArray.data(),
			0,
			0);
	}

	void XShape2D_Line::SetColor(const FLinearColor& InColor)
	{
		mDrawColor = InColor;

		for (auto& vertex : mVertexBufferArray)
		{
			vertex.Color = mDrawColor;
		}

		SetShaderParams();
	}

	void XShape2D_Line::SetScale(const FVector2f& InScale)
	{
		// 기존 행렬의 이동, 회전 성분을 저장
		XMVECTOR scale, rotation, translation;
		XMMatrixDecompose(&scale, &rotation, &translation, mTransform);

		// 새로운 스케일 행렬을 생성
		const XMMATRIX newScaleMatrix = XMMatrixScaling(InScale.X, InScale.Y, 1.0f);

		// 새로운 스케일 행렬과 기존의 회전 행렬을 결합
		const XMMATRIX rotationMatrix = XMMatrixRotationQuaternion(rotation);
		mTransform                    = newScaleMatrix * rotationMatrix;

		// 기존의 위치 성분을 다시 설정
		mTransform.r[3] = translation;
	}

	void XShape2D_Line::SetWorldRotation(const float InDegree)
	{
		// 새로운 각 (Degree)
		const XMMATRIX newRotationMatrix = RotationMatrix(InDegree);

		// 기존 스케일 성분
		const XMVECTOR cachedScale = XMVectorSet(XMVectorGetX(mTransform.r[0]),
												 XMVectorGetY(mTransform.r[1]),
												 XMVectorGetZ(mTransform.r[2]), 0.0f);
		// 기존 위치 성분
		const XMVECTOR cachedTranslation = mTransform.r[3];

		// 새로운 변환 행렬을 스케일, 새로운 회전, 기존 위치를 결합하여 재구성
		mTransform      = XMMatrixScalingFromVector(cachedScale) * newRotationMatrix; // 회전, 스케일은 위 3x3성분
		mTransform.r[3] = cachedTranslation;
	}

	void XShape2D_Line::SetWorldLocation(const FVector2f& InLocation)
	{
		const float currentZ = XMVectorGetZ(mTransform.r[3]);

		mTransform.r[3] = XMVectorSet(InLocation.X, InLocation.Y, currentZ, 1.f);
	}

	void XShape2D_Line::AddWorldLocation(const FVector2f& InAddLocation)
	{
		const float currentZ = XMVectorGetZ(mTransform.r[3]);

		mTransform.r[3] = XMVectorSet(GetLocation().X + InAddLocation.X, GetLocation().Y + InAddLocation.Y, currentZ, 1.f);
	}

	void XShape2D_Line::SetWorldTransform(const Matrix& InMatrix)
	{
		mTransform = InMatrix;
	}

	void XShape2D_Line::SetWorldTransform(const FVector2f& InLocation, const float InAngle, const FVector2f& InScale)
	{
		const float currentZ = XMVectorGetZ(mTransform.r[3]);

		const XMMATRIX translation = TranslationMatrix(InLocation.X, InLocation.Y, currentZ);
		const XMMATRIX rotation    = RotationMatrix(InAngle);
		const XMMATRIX scale       = ScaleMatrix(InScale.X, InScale.Y);

		const XMMATRIX transform = scale * rotation * translation;

		mTransform = transform;
	}


}
