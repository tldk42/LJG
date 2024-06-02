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
		  mPrimType() {}

	Vertex::~Vertex() {}

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
		// D3D11_MAPPED_SUBRESOURCE mappedResource;

		// Context::GetDeviceContext()->Map(mConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	}

	void Vertex::Render()
	{
		Context::GetDeviceContext()->VSSetShader(mVertexShader, nullptr, 0);
		Context::GetDeviceContext()->PSSetShader(mPixelShader, nullptr, 0);
		Context::GetDeviceContext()->GSSetShader(nullptr, nullptr, 0);

		// TODO: Set Geometry shader
		Context::GetDeviceContext()->IASetInputLayout(mVertexLayout);

		constexpr UINT stride = 12;
		constexpr UINT offset = 0;

		Context::GetDeviceContext()->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
		Context::GetDeviceContext()->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
		Context::GetDeviceContext()->VSSetConstantBuffers(0, 1, &mConstantBuffer);
		Context::GetDeviceContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
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

		Context::GetDeviceContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		return result;
	}

	HRESULT Vertex::LoadShaderAndInputLayout()
	{
		HRESULT result = S_OK;

		DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
		shaderFlags |= D3DCOMPILE_DEBUG;
#endif
		ID3DBlob* vertexShaderBuf;
		ID3DBlob* pixelShaderBuf = nullptr;

		mVertexShader = UDXHelper::LoadVertexFile(Context::GetDevice(), L"sample_vert.vsh", &vertexShaderBuf);
		mPixelShader  = UDXHelper::LoadPixelShaderFile(Context::GetDevice(), L"sample_frag.psh");

		if (!mVertexShader || !mPixelShader)
		{
			return E_FAIL;
		}

		const D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		result = Context::GetDevice()->CreateInputLayout(layout,
		                                                 1,
		                                                 vertexShaderBuf->GetBufferPointer(),
		                                                 vertexShaderBuf->GetBufferSize(),
		                                                 &mVertexLayout);

		ReleaseCOM(vertexShaderBuf);
		ReleaseCOM(pixelShaderBuf);

		return result;
	}

	HRESULT Vertex::CreateVertexBuffer()
	{
		HRESULT result = S_OK;

		const SimpleVertex vertices[] =
		{
			-0.5f, 0.5f,
			0.5f, 0.5f,
			0.5f, -0.5f,
			-0.5f, -0.5f
		};

		constexpr UINT numVertices = std::size(vertices);

		D3D11_BUFFER_DESC bd;
		{
			bd.Usage          = D3D11_USAGE_DEFAULT;
			bd.ByteWidth      = numVertices * sizeof(SimpleVertex);
			bd.BindFlags      = D3D11_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = 0;
			bd.MiscFlags      = 0;
		}

		D3D11_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = vertices;
		result           = Context::GetDevice()->CreateBuffer(&bd, &InitData, &mVertexBuffer);
		return result;
	}

	HRESULT Vertex::CreateIndexBuffer()
	{
		HRESULT result = S_OK;

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
		result             = Context::GetDevice()->CreateBuffer(&initData, &ibInitData, &mIndexBuffer);
		return result;
	}

	HRESULT Vertex::CreateConstantBuffer()
	{
		HRESULT result = S_OK;

		D3D11_BUFFER_DESC bufferDesc;
		{
			bufferDesc.ByteWidth      = 32;
			bufferDesc.Usage          = D3D11_USAGE_DYNAMIC;
			bufferDesc.BindFlags      = D3D11_BIND_CONSTANT_BUFFER;
			bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			bufferDesc.MiscFlags      = 0;
		}

		result = Context::GetDevice()->CreateBuffer(&bufferDesc, nullptr, &mConstantBuffer);
		return result;
	}
}
