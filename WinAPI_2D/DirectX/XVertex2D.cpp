#include "XVertex2D.h"
#include "XWorldBuffer.h"
#include "Context.h"
#include "XShaderData.h"
#include "Component/Manager/ShaderManager.h"
#include "Helper/UDXHelper.h"

namespace LJG
{
	XVertex2D::XVertex2D(const float InZOrder)
		: mTextureScale(FVector2f::UnitVector),
		  mZOrder(InZOrder)
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
		mWorldBuffer->SetWorldMatrix(mTransform);
		mWorldBuffer->Update(DeltaTime);
	}

	void XVertex2D::Render()
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

		Context::GetDeviceContext()->IASetPrimitiveTopology(mPrimType);

		// TODO: ���� Draw�� Child Vertex���� ����
		// Context::GetDeviceContext()->DrawIndexed(8, 0, 0);
	}

	void XVertex2D::Release()
	{
		mWorldBuffer->Release();
		mVertexLayout = nullptr;
		mVertexBuffer = nullptr;
		mIndexBuffer  = nullptr;
		mShaderData   = nullptr;
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
			bufferDesc.ByteWidth      = std::size(mVertexBufferArray) * sizeof(FVertexBase); // ����ũ��
			bufferDesc.Usage          = D3D11_USAGE_DEFAULT; // ������ �б�/���� ��� ����
			bufferDesc.BindFlags      = D3D11_BIND_VERTEX_BUFFER; // ���������ο� ���ε��� ���
			bufferDesc.CPUAccessFlags = 0; // ������ ���ۿ� CPU�� �����ϴ� ���� (DX ���ɿ� �ſ� �߿�)
			bufferDesc.MiscFlags      = 0; // �߰����� �ɼ� �÷���
		}

		D3D11_SUBRESOURCE_DATA InitData;
		{
			InitData.pSysMem = mVertexBufferArray.data(); // �ʱ�ȭ ������ ������ (���� �迭�� �ּҸ� �Ѱ��ش�)
			// InitData.SysMemPitch (�ؽ�ó ���ҽ��� ������ ũ��)
			// InitData.SysMemSlicePitch (3���� �ؽ�ó�� ���� ����)
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

		mShaderData = Manager_Shader.Load(L"SimpleShader", L"Shader/sample2_vert.vsh", L"Shader/sample2_frag.psh");

		constexpr D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{
				"POSITION",                  // ���̴� �Է� ������ �� ��ҿ� ����� �ǹ�ü�� 
				0,                           // �ǹ̻� �ε���
				DXGI_FORMAT_R32G32B32_FLOAT, // ������ ���� (float2)
				0,                           // �Է� ����� �ĺ�����
				0,                           // ��� ���� ������ 
				D3D11_INPUT_PER_VERTEX_DATA, // ���� �Է� ���� �Է� ������ Ŭ����
				0                            // ���� ���ۿ��� ������ �Ǵ� �ν��Ͻ��� �� (D3D11_INPUT_PER_VERTEX_DATA -> 0)
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
			{FVector3f(-.5f, .5f, mZOrder), {0, 0}, mDrawColor},
			{FVector3f(.5f, .5f, mZOrder), {1, 0}, mDrawColor},
			{FVector3f(.5f, -.5f, mZOrder), {1, 1}, mDrawColor},
			{FVector3f(-.5f, -.5f, mZOrder), {0, 1}, mDrawColor},
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

	#pragma region Transform
	void XVertex2D::SetScale(const FVector2f& InScale)
	{
		// ���� ����� �̵�, ȸ�� ������ ����
		XMVECTOR scale, rotation, translation;
		XMMatrixDecompose(&scale, &rotation, &translation, mTransform);

		// ���ο� ������ ����� ����
		const XMMATRIX newScaleMatrix = XMMatrixScaling(InScale.X * mTextureScale.X, InScale.Y * mTextureScale.Y, 1.0f);

		// ���ο� ������ ��İ� ������ ȸ�� ����� ����
		const XMMATRIX rotationMatrix = XMMatrixRotationQuaternion(rotation);
		mTransform                    = newScaleMatrix * rotationMatrix;

		// ������ ��ġ ������ �ٽ� ����
		mTransform.r[3] = translation;
	}

	void XVertex2D::SetWorldRotation(const float InDegree)
	{
		// ���ο� �� (Degree)
		const XMMATRIX newRotationMatrix = RotationMatrix(InDegree);

		// ���� ������ ����
		const XMVECTOR cachedScale = XMVectorSet(XMVectorGetX(mTransform.r[0]),
												 XMVectorGetY(mTransform.r[1]),
												 XMVectorGetZ(mTransform.r[2]), 0.0f);
		// ���� ��ġ ����
		const XMVECTOR cachedTranslation = mTransform.r[3];

		// ���ο� ��ȯ ����� ������, ���ο� ȸ��, ���� ��ġ�� �����Ͽ� �籸��
		mTransform      = XMMatrixScalingFromVector(cachedScale) * newRotationMatrix; // ȸ��, �������� �� 3x3����
		mTransform.r[3] = cachedTranslation;                                          // �̵� ������ ������ �຤��
	}

	void XVertex2D::SetColor(const FLinearColor& InColor)
	{
		mDrawColor = InColor;

		for (auto& vertex : mVertexBufferArray)
		{
			vertex.Color = mDrawColor;
		}

		SetShaderParams();
	}

	void XVertex2D::SetWorldLocation(const FVector2f& InLocation)
	{
		mTransform.r[3] = XMVectorSet(InLocation.X, InLocation.Y, 0.f, 1.f);
	}

	void XVertex2D::AddWorldLocation(const FVector2f& InAddLocation)
	{
		mTransform.r[3] = XMVectorSet(GetLocation().X + InAddLocation.X, GetLocation().Y + InAddLocation.Y, 0.f, 1.f);
	}

	void XVertex2D::SetWorldTransform(const Matrix& InMatrix)
	{
		mTransform = ScaleMatrix(mTextureScale.X, mTextureScale.Y) * InMatrix;
	}

	void XVertex2D::SetWorldTransform(const FVector2f& InLocation, const float InAngle, const FVector2f& InScale)
	{
		const XMMATRIX translation = TranslationMatrix(InLocation.X, InLocation.Y);
		const XMMATRIX rotation    = RotationMatrix(InAngle);
		const XMMATRIX scale       = ScaleMatrix(InScale.X * mTextureScale.X, InScale.Y * mTextureScale.Y);

		const XMMATRIX transform = scale * rotation * translation;

		mTransform = transform;
	}

	void XVertex2D::SetFlipX(const bool bEnable)
	{
		if (bEnable != bFlipX)
		{
			for (FVertexBase& vertex : mVertexBufferArray)
			{
				vertex.Tex.X = 1.f - vertex.Tex.X;
			}

			bFlipX = bEnable;
		}

		SetShaderParams();
	}

#pragma endregion

	void XVertex2D::OnResizeCallback()
	{}
}
