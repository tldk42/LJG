#pragma once
#include "XConstantBuffer.h"

namespace LJG
{
	class XWorldBuffer : public XConstantBuffer
	{
	public:
		XWorldBuffer()           = default;
		~XWorldBuffer() override = default;

	public:
#pragma region Core Interface
		void Initialize() override;
		void Update(float DeltaTime) override;
		void Render() override;
		void Release() override;
#pragma endregion

	public:
		void SetWorldMatrix(const Matrix& InMatrix) { mWorldMatrix = XMMatrixTranspose(InMatrix); }

	private:
		HRESULT CreateConstantBuffer() override;

	private:
		Matrix mWorldMatrix = XMMatrixIdentity();
	};
}
