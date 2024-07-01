#include "XVertex2D.h"
#include "XWorldBuffer.h"
#include "Context.h"
#include "Window.h"
#include "XShaderData.h"
#include "Component/Manager/ShaderManager.h"
#include "Helper/UDXHelper.h"


namespace LJG
{
	extern float_t g_GlobalScaleX;
	extern float_t g_GlobalScaleY;

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

		// Window::GetWindow()->OnResize.Bind([this](UINT Width, UINT Height){
		// 	const auto originalScale    = GetScale();
		// 	const auto originalLocation = GetLocation();
		//
		// 	SetScale({originalScale.X * g_GlobalScaleX, originalScale.Y * g_GlobalScaleY});
		// 	SetWorldLocation({
		// 		originalLocation.X * g_GlobalScaleX,
		// 		originalLocation.Y * g_GlobalScaleY
		// 	});
		// });

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

		mShaderData = Manager_Shader.CreateOrLoad(L"AlphaBlend", L"Shader/alphablend.vsh", L"Shader/alphablend.psh");
		
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
		const XMMATRIX newScaleMatrix = XMMatrixScaling(InScale.X, InScale.Y, 1.0f);

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
		const float currentZ = XMVectorGetZ(mTransform.r[3]);

		mTransform.r[3] = XMVectorSet(InLocation.X, InLocation.Y, currentZ, 1.f);
	}

	void XVertex2D::AddWorldLocation(const FVector2f& InAddLocation)
	{
		const float currentZ = XMVectorGetZ(mTransform.r[3]);

		mTransform.r[3] = XMVectorSet(GetLocation().X + InAddLocation.X, GetLocation().Y + InAddLocation.Y, currentZ, 1.f);
	}

	void XVertex2D::SetWorldTransform(const Matrix& InMatrix)
	{
		mTransform = ScaleMatrix(mTextureScale.X, mTextureScale.Y) * InMatrix;
	}

	void XVertex2D::SetWorldTransform(const FVector2f& InLocation, const float InAngle, const FVector2f& InScale)
	{
		const float currentZ = XMVectorGetZ(mTransform.r[3]);

		const XMMATRIX translation = TranslationMatrix(InLocation.X, InLocation.Y, currentZ);
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

	void XVertex2D::SetZOrder(const float InZOrder)
	{
		mZOrder = InZOrder;

		for (auto& vertex : mVertexBufferArray)
		{
			vertex.Pos.Z = mZOrder;
		}

		SetShaderParams();
	}

#pragma endregion
}
