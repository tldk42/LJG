#include "Object.h"

#include "Context.h"
#include "d3dcompiler.h"
#include "EngineHelper.h"


namespace LJG
{
	void Object::Initialize()
	{
	}

	void Object::Update()
	{
	}

	void Object::Render()
	{
		const UINT strides = sizeof(FVector2D);
		const UINT offsets = 0;

		Context::GetDeviceContext()->IASetVertexBuffers(0, 1, &mVertexBuffer, &strides, &offsets);

		Context::GetDeviceContext()->Draw(SamplePoints.size(), 0);
	}

	void Object::Release()
	{
		if (mVertexBuffer)
		{
			ReleaseCOM(mVertexBuffer);
			ReleaseCOM(mVertexShader);
			ReleaseCOM(mVertexShader);
		}
	}

	void Object::CreateVertexBuffer()
	{
		assert(!SamplePoints.empty());


		// Set buffer size
		D3D11_BUFFER_DESC bufferDesc;
		// Set buffer resource
		D3D11_SUBRESOURCE_DATA resourceData;

		{
			ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));
			bufferDesc.ByteWidth           = sizeof(FVertexBuffer) * SamplePoints.size();
			bufferDesc.BindFlags           = D3D11_BIND_VERTEX_BUFFER;
			bufferDesc.StructureByteStride = 3;
		}

		{
			ZeroMemory(&resourceData, sizeof(D3D11_SUBRESOURCE_DATA));
			resourceData.pSysMem = &SamplePoints.at(0);
		}

		if (FAILED(Context::Get()->GetDevice()->CreateBuffer(&bufferDesc, &resourceData, &mVertexBuffer)))
		{
			EngineHelper::ShowErrorMessageBox(Window::GetWindow()->GetHandle(), false);
		}
	}

	bool Object::CreateInputLayout()
	{
		D3D11_INPUT_ELEMENT_DESC inputDesc;
		// Context::GetContext()->GetDevice()->CreateInputLayout(&inputDesc, 1, , 0, &mInputLayout);

		return false;
	}

	bool Object::LoadShader()
	{
		ID3D10Blob* errorMessage;
		ID3D10Blob* vertexShaderBuffer;

		D3DCompileFromFile(L"sample.vs", 0, 0, "ColorVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
		                   &vertexShaderBuffer,
		                   &errorMessage);

		Context::GetDevice()->CreateVertexShader();
		Context::GetDevice()->CreatePixelShader();


		Context::GetDeviceContext()->VSSetShader(mVertexShader, NULL, 0);
		Context::GetDeviceContext()->PSSetShader(mPixelShader, NULL, 0);

		return false;
	}
}
