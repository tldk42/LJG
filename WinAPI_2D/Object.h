#pragma once
#include <d3d11.h>

#include "CommonInclude.h"


struct FVertexBuffer
{
	std::vector<FVector2D> Vertices;
};

namespace LJG
{
	class Object : public ICoreEntity
	{
	public:
#pragma region Core Interface
		void Initialize() override;
		void Update() override;
		void Render() override;
		void Release() override;
#pragma endregion

		void CreateVertexBuffer();
		bool CreateInputLayout();
		bool LoadShader();

	public:
		// TODO: Remove this
		// For Test
		std::vector<FVector2D> SamplePoints;

	protected:
		// 그래픽카드 메모리에 할당된 버퍼
		ID3D11Buffer* mVertexBuffer;

		ID3D11VertexShader* mVertexShader;
		ID3D11PixelShader*  mPixelShader;

		ID3D11InputLayout* mInputLayout;
	};
}
