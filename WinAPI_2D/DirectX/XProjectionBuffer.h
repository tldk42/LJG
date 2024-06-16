#pragma once
#include "XConstantBuffer.h"

namespace LJG
{
#pragma region Data
	struct FViewProjectionBuffer
	{
		XMMATRIX ViewProjection;
	};
#pragma endregion

	class XProjectionBuffer : public XConstantBuffer
	{
	public:
		XProjectionBuffer();
		~XProjectionBuffer() override = default;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

		inline void SetProjectionMatrix(const Matrix& InMatrix) { mProjectionMatrix = XMMatrixTranspose(InMatrix); }

	private:
		HRESULT CreateConstantBuffer() override;

	private:
		Matrix mProjectionMatrix = XMMatrixIdentity();
	};
}
