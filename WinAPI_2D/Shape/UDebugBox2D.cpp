#include "UDebugBox2D.h"

#include "../Context.h"

namespace LJG
{
	UDebugBox2D::UDebugBox2D() = default;

	void UDebugBox2D::Initialize()
	{
		UDebugShape2D::Initialize();
	}

	void UDebugBox2D::Update(float DeltaTime)
	{
		UDebugShape2D::Update(DeltaTime);
	}

	void UDebugBox2D::Render()
	{
		UDebugShape2D::Render();

		Context::GetDeviceContext()->DrawIndexed(8, 0, 0);
	}

	void UDebugBox2D::Release()
	{
		UDebugShape2D::Release();
	}

	void UDebugBox2D::SetColor(const FLinearColor& InColor)
	{
		mDrawColor = InColor;

		for (auto& vertex : mVertexBufferArray)
		{
			vertex.Color = mDrawColor;
		}

		SetShaderParams();
	}

	void UDebugBox2D::CreateVertexArray()
	{
		UDebugShape2D::CreateVertexArray();
	}

	void UDebugBox2D::CreateIndexArray()
	{
		UDebugShape2D::CreateIndexArray();
	}
}
