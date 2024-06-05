#include "UTexture.h"

#include <d3dcompiler.h>
#include "Context.h"
#include "EngineHelper.h"
#include "UDXHelper.h"
#include "directxtk/WICTextureLoader.h"


namespace LJG
{
	UTexture::UTexture(const std::wstring& TextureFile)
	{
		if (FAILED(LoadTextureFromFile(TextureFile)))
		{
			LOG_DX_ERROR("Invalid file");
			return;
		}

		UTexture::Initialize();
	}

	UTexture::~UTexture()
	{
		UTexture::Release();
	}

	void UTexture::Initialize()
	{
		if (FAILED(CreateTriangle()))
		{
			EngineHelper::ShowErrorMessageBox(Window::GetWindow()->GetHandle(), false);
		}
		if (FAILED(CreateConstantBuffer()))
		{
			EngineHelper::ShowErrorMessageBox(Window::GetWindow()->GetHandle(), true);
		}
	}

	void UTexture::Update(float DeltaTime)
	{
		SetShaderParams();
	}

	void UTexture::Render()
	{
		Context::GetDeviceContext()->VSSetShader(mVertexShader.Get(), nullptr, 0);
		Context::GetDeviceContext()->PSSetShader(mPixelShader.Get(), nullptr, 0);
		// TODO: Set other shader...

		Context::GetDeviceContext()->IASetInputLayout(mVertexLayout.Get());


		// ������ ���ҽ��� ����� �� �ٽ� ȣ�� (���� �ٸ� �ؽ�ó�� ���� -> ������)
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
		// ComPtr ��ü
		// ReleaseCOM(mVertexLayout);
		// ReleaseCOM(mVertexBuffer);
		// ReleaseCOM(mIndexBuffer);
		// ReleaseCOM(mConstantBuffer);
		// ReleaseCOM(mVertexShader);
		// ReleaseCOM(mPixelShader);
		// ReleaseCOM(mTextureResource);
		// ReleaseCOM(mSRV);
		// ReleaseCOM(mTexture);
		// ReleaseCOM(mSamplerState);
	}

	HRESULT UTexture::LoadTextureFromFile(const std::wstring& TextureFile)
	{
		HRESULT result = E_FAIL;
		if (!TextureFile.empty())
		{
			result = DirectX::CreateWICTextureFromFile(Context::GetDevice(), TextureFile.c_str(),
			                                           mTextureResource.GetAddressOf(),
			                                           mSRV.GetAddressOf());
			if (FAILED(result))
				return result;

			// �ؽ�ó ���� ��������
			mSRV->GetDesc(&mSRVDesc);

			result = mTextureResource->QueryInterface(__uuidof(ID3D11Texture2D),
			                                          reinterpret_cast<void**>(mTexture.GetAddressOf()));

			mTexture->GetDesc(&mTextureDesc);


			LOG_DX_INFO("-------- Texure Loaded ----------");
			std::string texName;
			texName.assign(TextureFile.begin(), TextureFile.end());
			LOG_DX_INFO("File: {}", texName);
			LOG_DX_INFO("Width: {}", mTextureDesc.Width);
			LOG_DX_INFO("Height: {}", mTextureDesc.Height);

			AdjustTextureSize();
		}

		return result;
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
		HRESULT result = S_OK;

		result = CreateVertexBuffer();
		result = CreateIndexBuffer();
		result = LoadShaderAndInputLayout();
		result = CreateSamplerState();

		Context::GetDeviceContext()->IASetPrimitiveTopology(mPrimType);

		return result;
	}

	HRESULT UTexture::CreateVertexBuffer()
	{
		// ���� ���� (�簢���� �׸������� �⺻���� �ﰢ�� 2���� �ε����Ͽ� ����
		mVertexBufferArray = {
			{{mScale.X * (-mVertexOffset.X), mScale.Y * (mVertexOffset.Y)}, {0, 0}},
			{{mScale.X * (mVertexOffset.X), mScale.Y * (mVertexOffset.Y)}, {1, 0}},
			{{mScale.X * (mVertexOffset.X), mScale.Y * (-mVertexOffset.Y)}, {1, 1}},
			{{mScale.X * (-mVertexOffset.X), mScale.Y * (-mVertexOffset.Y)}, {0, 1}}
		};

		D3D11_BUFFER_DESC bufferDesc;
		{
			bufferDesc.ByteWidth      = std::size(mVertexBufferArray) * sizeof(FTexVertex); // ����ũ��
			bufferDesc.Usage          = D3D11_USAGE_DEFAULT;                      // ������ �б�/���� ��� ����
			bufferDesc.BindFlags      = D3D11_BIND_VERTEX_BUFFER;                 // ���������ο� ���ε��� ���
			bufferDesc.CPUAccessFlags = 0;                                        // ������ ���ۿ� CPU�� �����ϴ� ���� (DX ���ɿ� �ſ� �߿�)
			bufferDesc.MiscFlags      = 0;                                        // �߰����� �ɼ� �÷���
		}

		D3D11_SUBRESOURCE_DATA InitData;
		{
			InitData.pSysMem = mVertexBufferArray.data(); // �ʱ�ȭ ������ ������ (���� �迭�� �ּҸ� �Ѱ��ش�)
			// InitData.SysMemPitch (�ؽ�ó ���ҽ��� ������ ũ��)
			// InitData.SysMemSlicePitch (3���� �ؽ�ó�� ���� ����)
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
		 *  ���� ������ �����͸� ��ȯ�ϴ� ���� ����
		 *	�޽� ����ȭ �� �ε� �۾� �� ���� ����, �ڷ� ���� ������ �����ϴ� ������ ���۷� ���
		 *	���̴� ������ API���ڷν� ��ü�ڵ�, �����޽��� ��ȯ
		 *	GetBufferPointer	: ������ ������
		 *	GetBufferSize		: ������ ũ��
		 */
		ComPtr<ID3DBlob> vertexShaderBuf;
		ComPtr<ID3DBlob> pixelShaderBuf = nullptr;

		mVertexShader = UDXHelper::LoadVertexShaderFile(Context::GetDevice(), L"sample_vert.vsh", &vertexShaderBuf);
		mPixelShader  = UDXHelper::LoadPixelShaderFile(Context::GetDevice(), L"sample_frag.psh");

		if (!mVertexShader || !mPixelShader)
		{
			LOG_DX_ERROR("Failed to load, compile ShaderFile or ��������(��μ����Ͻÿ�)?");
			return E_FAIL;
		}

		constexpr D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{
				"POSITION",                  // ���̴� �Է� ������ �� ��ҿ� ����� �ǹ�ü�� 
				0,                           // �ǹ̻� �ε���
				DXGI_FORMAT_R32G32_FLOAT,    // ������ ���� (float2)
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
			}
		};

		result = Context::GetDevice()->CreateInputLayout(
			layout,
			2,
			vertexShaderBuf->GetBufferPointer(),
			vertexShaderBuf->GetBufferSize(),
			mVertexLayout.GetAddressOf());

		vertexShaderBuf.Reset();
		pixelShaderBuf.Reset();

		return result;
	}

	HRESULT UTexture::CreateSamplerState()
	{
		/**
		 * �ؽ�ó ����
		 *	1. �ؽ�ó ���͸�
		 *		Point(����� �ؼ���) Linear(����) Anisotropic(��絵)
		 *	2. ��ǥ Warping
		 *		Wrap (�ݺ�) Clamp(0-1) Mirror(�ݺ�, ������) Border(���� ��� �ÿ� ��� ��)
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

		return Context::GetDevice()->CreateBuffer(&bufferDesc, nullptr, &mConstantBuffer);
	}

	void UTexture::SetWorldLocation(const FVector2f& InPos)
	{
		if (InPos == mWorldLocation)
			return;

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
