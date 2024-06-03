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
		// ���� ����
		const FVector2f vertices[] =
		{
			{-0.5f, 0.5f},
			{0.5f, 0.5f},
			{0.5f, -0.5f},
			{-0.5f, -0.5f}
		};

		D3D11_BUFFER_DESC bufferDesc;
		{
			bufferDesc.ByteWidth      = std::size(vertices) * sizeof(FVector2f); // ����ũ��
			bufferDesc.Usage          = D3D11_USAGE_DEFAULT;                     // ������ �б�/���� ��� ����
			bufferDesc.BindFlags      = D3D11_BIND_VERTEX_BUFFER;                // ���������ο� ���ε��� ���
			bufferDesc.CPUAccessFlags = 0;                                       // ������ ���ۿ� CPU�� �����ϴ� ���� (DX ���ɿ� �ſ� �߿�)
			bufferDesc.MiscFlags      = 0;                                       // �߰����� �ɼ� �÷���
		}

		D3D11_SUBRESOURCE_DATA InitData;
		{
			InitData.pSysMem = vertices; // �ʱ�ȭ ������ ������ (���� �迭�� �ּҸ� �Ѱ��ش�)
			// InitData.SysMemPitch (�ؽ�ó ���ҽ��� ������ ũ��)
			// InitData.SysMemSlicePitch (3���� �ؽ�ó�� ���� ����)
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
		 *  ���� ������ �����͸� ��ȯ�ϴ� ���� ����
		 *	�޽� ����ȭ �� �ε� �۾� �� ���� ����, �ڷ� ���� ������ �����ϴ� ������ ���۷� ���
		 *	���̴� ������ API���ڷν� ��ü�ڵ�, �����޽��� ��ȯ
		 *	GetBufferPointer	: ������ ������
		 *	GetBufferSize		: ������ ũ��
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
				"POSITION",                  // ���̴� �Է� ������ �� ��ҿ� ����� �ǹ�ü�� 
				0,                           // �ǹ̻� �ε���
				DXGI_FORMAT_R32G32_FLOAT,    // ������ ���� (float2)
				0,                           // �Է� ����� �ĺ�����
				0,                           // ��� ���� ������ 
				D3D11_INPUT_PER_VERTEX_DATA, // ���� �Է� ���� �Է� ������ Ŭ����
				0                            // ���� ���ۿ��� ������ �Ǵ� �ν��Ͻ��� �� (D3D11_INPUT_PER_VERTEX_DATA -> 0)
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
